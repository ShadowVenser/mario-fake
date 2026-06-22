#include "MenuScene.h"
#include <memory>


#include "../Systems/MenuInitSystem.h"

#include "../Systems/AnimationSystem.h"
#include "../Systems/ButtonStateSystem.h"
#include "../Systems/DrawSystem.h"
#include "../Systems/KillerSystem.h"
#include "SFML/Window/Mouse.hpp"

MenuScene::MenuScene(GameEngine& engine): Scene(engine)
{ }

void MenuScene::Init()
{
    RegisterAction(MouseMove::Move, "Move");
    RegisterAction(sf::Mouse::Button::Left, "Click");

    systemsManager.AddInitializer(std::make_shared<MenuInitSystem>(world, gameEngine));

    systemsManager.AddSystem(std::make_shared<ButtonStateSystem>(world, actionMap));
    systemsManager.AddSystem(std::make_shared<AnimationSystem>(world));
    systemsManager.AddSystem(std::make_shared<DrawSystem>(world, gameEngine, _visible));
    systemsManager.AddSystem(std::make_shared<KillerSystem>(world));

    systemsManager.Initialize();
}

void MenuScene::Update(float dt)
{
    systemsManager.Update(dt);
}