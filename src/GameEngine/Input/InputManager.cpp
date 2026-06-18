#include "InputManager.h"

#include <imgui-SFML.h>
#include <iostream>

#include "../GameEngine.h"
#include "InputAction.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "imgui.h"

void InputManager::RegisterInput(const size_t scene,
    const sf::Keyboard::Key key, std::shared_ptr<InputAction> action)
{
    _actionKeyMaps[scene][key] = action;
}

void InputManager::RegisterInput(const size_t scene,
    const sf::Mouse::Button btn, std::shared_ptr<InputAction> action)
{
    _actionMouseBtnMaps[scene][btn] = action;
}

void InputManager::RegisterInput(const size_t scene,
    const sf::Mouse::Wheel wheel, std::shared_ptr<InputAction> action)
{
    _actionMouseWheelMaps[scene][wheel] = action;
}

void InputManager::RegisterInput(const size_t scene, const MouseMove mv,
    std::shared_ptr<InputAction> action)
{
    _actionMouseMoveMaps[scene][mv] = action;
}



void InputManager::ProcessInput(const size_t scene)
{
    _releaseActions(_actionKeyMaps[scene]);
    _releaseActions(_actionMouseBtnMaps[scene]);
    _releaseActions(_actionMouseMoveMaps[scene]);
    _releaseActions(_actionMouseWheelMaps[scene]);

    for (auto& pair: _actionKeyMaps[scene])
    {
        if (sf::Keyboard::isKeyPressed(pair.first) || pair.second->Type() == ActionType::Start)
        {
            pair.second->Type() = ActionType::Pressed;
        }
    }

    for (auto& pair: _actionMouseBtnMaps[scene])
    {
        if (sf::Mouse::isButtonPressed(pair.first) || pair.second->Type() == ActionType::Start)
        {
            pair.second->Type() = ActionType::Pressed;
            pair.second->Vector() = sf::Mouse::getPosition();
        }
    }

    SpecialInput spec {-1, {-1, -1}};

    while (const std::optional event = _window.pollEvent()) 
    {
        if (event.has_value())
            ImGui::SFML::ProcessEvent(_window, event.value());

        if (event->is<sf::Event::Closed>())
        {
            _gameEngine.Quit();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            _processEvent(_actionKeyMaps[scene], keyPressed, ActionType::Start);
        }
        else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            _processEvent(_actionKeyMaps[scene], keyReleased, ActionType::End);
        }
        else if (const auto* mouseBtnPressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            _processEvent(_actionMouseBtnMaps[scene], mouseBtnPressed, ActionType::Start, &spec);
        }
        else if (const auto* mouseBtnReleased = event->getIf<sf::Event::MouseButtonReleased>())
        {
            _processEvent(_actionMouseBtnMaps[scene], mouseBtnReleased, ActionType::End, &spec);
        }
        else if (const auto* mouseWheelEvent = event->getIf<sf::Event::MouseWheelScrolled>())
        {
            _processEvent(_actionMouseWheelMaps[scene], mouseWheelEvent, ActionType::Moved, &spec);
        }
        else if (const auto* mouseMovedEvent = event->getIf<sf::Event::MouseMoved>())
        {
            _processEvent(_actionMouseMoveMaps[scene], mouseMovedEvent, ActionType::Moved, &spec);
        }
    }

}

InputManager::InputManager(sf::RenderWindow& window, GameEngine& engine):
    _window(window), _gameEngine(engine)
{ }