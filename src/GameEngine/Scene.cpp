#include "Scene.h"
#include <memory>
#include "GameEngine.h"
#include "Input/InputAction.h"

Scene::Scene(GameEngine& engine): 
    gameEngine(engine),
    world(),
    systemsManager(world)
{ }

std::shared_ptr<InputAction> Scene::RegisterAction(const std::string &name)
{
    auto ptr = std::make_shared<InputAction>(name);
    actionMap[name] = ptr;

    return ptr;
}

void Scene::RegisterAction(const sf::Keyboard::Key key, const std::string& name)
{
    const auto action = RegisterAction(name);
    gameEngine.RegisterInput(key, action);
}

void Scene::RegisterAction(const sf::Mouse::Button btn, const std::string &name)
{
    const auto action = RegisterAction(name);
    gameEngine.RegisterInput(btn, action);
}

void Scene::RegisterAction(const sf::Mouse::Wheel wheel, const std::string &name)
{
    const auto action = RegisterAction(name);
    gameEngine.RegisterInput(wheel, action);
}

void Scene::RegisterAction(const MouseMove mv, const std::string &name)
{
    const auto action = RegisterAction(name);
    gameEngine.RegisterInput(mv, action);
}


