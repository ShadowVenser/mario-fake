#include "GameEngine.h"

#include "Assets/AssetManager.h"
#include "Input/InputManager.h"
#include "SFML/Window/VideoMode.hpp"

#include <imgui-SFML.h>
#include <imgui.h>
#include <memory>
#include <stdexcept>

void GameEngine::Render()
{
    ImGui::SFML::Render(_window);
    _window.display();
}

GameEngine::GameEngine(const GameEngineConfiguration& config):
    _config(config),
    _window(
        sf::VideoMode({
            config.Width,
            config.Height
        }),
        "BASE WINDOW"
    ),
    _isRunning(false),
    _currentScene(0)
{
    _window.setFramerateLimit(config.framerate);
    _window.setVerticalSyncEnabled(true);\
    _window.setKeyRepeatEnabled(false);

    if (!ImGui::SFML::Init(_window))
        throw std::runtime_error("Failed Dear ImGui Init!!!");

    auto assetCfgPath = std::string{config.AssetsFile};

    _assetManager.LoadFromFile(assetCfgPath);
    _inputManager = std::make_shared<InputManager>(_window, *this);
}

void GameEngine::Initialize()
{
    _isRunning = true;
}

void GameEngine::Run()
{
    Initialize();

    while (_isRunning)
    {
        _window.clear();

        auto dt = _deltaClock.restart();
        ImGui::SFML::Update(_window, dt);

        _inputManager->ProcessInput(_currentScene);

        auto scene = CurrentScene();
        scene->Update(dt.asSeconds());

        Render();
    }
}

void GameEngine::Quit()
{
    _isRunning = false;
}
