#include "MenuScene.h"
#include <memory>


#include "../Systems/MenuInitSystem.h"

#include "../Systems/DrawSystem.h"
#include "../Systems/KillerSystem.h"

MenuScene::MenuScene(GameEngine& engine): Scene(engine)
{
    systemsManager.AddInitializer(std::make_shared<MenuInitSystem>(world, engine));

    systemsManager.AddSystem(std::make_shared<DrawSystem>(world, engine));
    systemsManager.AddSystem(std::make_shared<KillerSystem>(world));
}

void MenuScene::Init()
{
    systemsManager.Initialize();
}

void MenuScene::Update(float dt)
{
    systemsManager.Update(dt);
}