#include "GameScene.h"
#include <memory>


#include "../Systems/GameInitSystem.h"
#include "../Systems/ShowGridSystem.h"
#include "../Systems/MoveInputSystem.h"
#include "../Systems/FallingSystem.h"
#include "../Systems/ColliderSystem.h"
#include "../Systems/MoveSystem.h"
#include "../Systems/ShootingSystem.h"

#include "../Systems/DrawSystem.h"
#include "../Systems/KillerSystem.h"

GameScene::GameScene(GameEngine& engine): Scene(engine)
{
    auto& gameCfg = engine.Cfg().cfg["Scenes"]["Game"];
    float tileSize = static_cast<float>(gameCfg["Grid"]["TileSize"].get<unsigned int>());
    float bulletSpeedX = gameCfg["Entities"]["Bullet"]["MovementComponent"]["XSpeed"].get<float>() * tileSize;
    float bulletSpeedY = gameCfg["Entities"]["Bullet"]["MovementComponent"]["YSpeed"].get<float>() * tileSize;
    auto bulletSprite = std::make_shared<sf::Sprite>(*engine.Assets().GetTexture(gameCfg["Entities"]["Bullet"]["Texture"].get<std::string>()));   
    float heightOffset = static_cast<float>(gameCfg["Entities"]["Bullet"]["SpawnHeightOffset"].get<int>());
    float cooldown = gameCfg["Entities"]["Bullet"]["Cooldown"].get<float>();
    // ваще говоря у системы есть инициализатор, и по-хорошему это туда запихать, но я уже сделал так
    
    systemsManager.AddInitializer(std::make_shared<GameInitSystem>(world, engine));

    systemsManager.AddSystem(std::make_shared<ShootingSystem>(world, actionMap, bulletSpeedX, bulletSpeedY, bulletSprite, heightOffset, cooldown));
    systemsManager.AddSystem(std::make_shared<MoveInputSystem>(world, engine, actionMap));
    systemsManager.AddSystem(std::make_shared<FallingSystem>(world));     // после пользовательского ввода
    systemsManager.AddSystem(std::make_shared<ColliderSystem>(world, tileSize));             // строго до MoveSystem и после ввода всех передвижений
    systemsManager.AddSystem(std::make_shared<MoveSystem>(world));

    systemsManager.AddSystem(std::make_shared<DrawSystem>(world, engine));
    systemsManager.AddSystem(std::make_shared<ShowGridSystem>(world, engine));       // должна быть после draw, чтобы рисовать поверх
    systemsManager.AddSystem(std::make_shared<KillerSystem>(world));
}

void GameScene::Init()
{   
    RegisterAction(sf::Keyboard::Key::W, "Jump");
    RegisterAction(sf::Keyboard::Key::A, "Left");
    RegisterAction(sf::Keyboard::Key::D, "Right");
    RegisterAction(sf::Keyboard::Key::Space, "Shoot");
    systemsManager.Initialize();
}

void GameScene::Update(float dt)
{
    systemsManager.Update(dt);
}