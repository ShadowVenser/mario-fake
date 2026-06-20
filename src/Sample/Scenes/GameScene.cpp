#include "GameScene.h"
#include <memory>


#include "../Systems/GameInitSystem.h"
#include "../Systems/ShowGridSystem.h"
#include "../Systems/MoveInputSystem.h"
#include "../Systems/MoveSystem.h"

#include "../Systems/DrawSystem.h"
#include "../Systems/KillerSystem.h"

GameScene::GameScene(GameEngine& engine): Scene(engine)
{
    systemsManager.AddInitializer(std::make_shared<GameInitSystem>(world, engine));

    systemsManager.AddSystem(std::make_shared<MoveInputSystem>(world, engine, actionMap));
    systemsManager.AddSystem(std::make_shared<MoveSystem>(world));//, engine, actionMap));

    systemsManager.AddSystem(std::make_shared<DrawSystem>(world, engine));
    systemsManager.AddSystem(std::make_shared<ShowGridSystem>(world, engine));       // должна быть после draw, чтобы рисовать поверх
    systemsManager.AddSystem(std::make_shared<KillerSystem>(world));
}

void GameScene::Init()
{   
    RegisterAction(sf::Keyboard::Key::W, "Jump");
    RegisterAction(sf::Keyboard::Key::A, "Left");
    RegisterAction(sf::Keyboard::Key::D, "Right");
    systemsManager.Initialize();
}

void GameScene::Update(float dt)
{
    systemsManager.Update(dt);
}