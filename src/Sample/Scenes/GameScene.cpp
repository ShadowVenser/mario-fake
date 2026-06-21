#include "GameScene.h"
#include <memory>


#include "../Systems/GameInitSystem.h"
#include "../Systems/ShowGridSystem.h"
#include "../Systems/MoveInputSystem.h"
#include "../Systems/FallingSystem.h"
#include "../Systems/ColliderSystem.h"
#include "../Systems/MoveSystem.h"
#include "../Systems/ShootingSystem.h"
#include "../Systems/BulletDeleteSystem.h"
#include "../Systems/FinishSystem.h"
#include "../Systems/OutOfBoundsSystem.h"
#include "../Systems/RespawnSystem.h"
#include "../Systems/AdditionalControlSystem.h"
#include "../Systems/CameraFollowXSystem.h"
#include "../Systems/PauseSystem.h"

#include "../Systems/DrawSystem.h"
#include "../Systems/KillerSystem.h"

GameScene::GameScene(GameEngine& engine): 
    Scene(engine), 
    basicSystemManager(systemsManager), 
    pausableSystemManager(world), 
    graphicsSystemManager(world),
    _onPause(false)
{
    RegisterAction(sf::Keyboard::Key::W, "Jump");           //MoveInputSystem
    RegisterAction(sf::Keyboard::Key::A, "Left");           //MoveInputSystem
    RegisterAction(sf::Keyboard::Key::D, "Right");          //MoveInputSystem
    RegisterAction(sf::Keyboard::Key::Space, "Shoot");      //ShootingSystem
    RegisterAction(sf::Keyboard::Key::Escape, "Menu");      //AdditionalControlSystem
    RegisterAction(sf::Keyboard::Key::P, "Pause");          //AdditionalControlSystem, пока нереализованная заглушка
    

    auto& gameCfg = engine.Cfg().cfg["Scenes"]["Game"];
    float tileSize = static_cast<float>(gameCfg["Grid"]["TileSize"].get<unsigned int>());
    float bulletSpeedX = gameCfg["Entities"]["Bullet"]["MovementComponent"]["XSpeed"].get<float>() * tileSize;
    float bulletSpeedY = gameCfg["Entities"]["Bullet"]["MovementComponent"]["YSpeed"].get<float>() * tileSize;
    auto bulletSprite = std::make_shared<sf::Sprite>(*engine.Assets().GetTexture(gameCfg["Entities"]["Bullet"]["Texture"].get<std::string>()));   
    float heightOffset = static_cast<float>(gameCfg["Entities"]["Bullet"]["SpawnHeightOffset"].get<int>());
    float cooldown = gameCfg["Entities"]["Bullet"]["Cooldown"].get<float>();
    // ваще говоря у системы есть инициализатор, и по-хорошему это туда запихать, но я уже сделал так
    float cameraSpeedCoef = gameCfg["Camera"]["SpeedCoef"].get<float>();
    float cameraSlowdownCoef = gameCfg["Camera"]["SlowDownCoef"].get<float>();
    float pauseCd = gameCfg["Pause"].value("Cooldown", 0.3f);

    basicSystemManager.AddInitializer(std::make_shared<GameInitSystem>(world, engine));

    basicSystemManager.AddSystem(std::make_shared<AdditionalControlSystem>(world, engine, actionMap, _onPause, pauseCd)); // ничего не требует и дропает сцену

    pausableSystemManager.AddSystem(std::make_shared<ShootingSystem>(world, actionMap, bulletSpeedX, bulletSpeedY, bulletSprite, heightOffset, cooldown));

    pausableSystemManager.AddSystem(std::make_shared<MoveInputSystem>(world, actionMap));
    pausableSystemManager.AddSystem(std::make_shared<CameraFollowXSystem>(world, cameraSpeedCoef, cameraSlowdownCoef));  
    pausableSystemManager.AddSystem(std::make_shared<FallingSystem>(world));                     // после пользовательского ввода
    pausableSystemManager.AddSystem(std::make_shared<ColliderSystem>(world, tileSize));             // строго до MoveSystem и после ввода всех передвижений
    pausableSystemManager.AddSystem(std::make_shared<MoveSystem>(world));

    pausableSystemManager.AddSystem(std::make_shared<FinishSystem>(world, engine));          // после коллайдера
    pausableSystemManager.AddSystem(std::make_shared<BulletDeleteSystem>(world));          // после коллайдера

    pausableSystemManager.AddSystem(std::make_shared<OutOfBoundsSystem>(world, static_cast<float>(engine.Window().getSize().y))); 
    pausableSystemManager.AddSystem(std::make_shared<RespawnSystem>(world, engine));    // прямо перед killerSystem
    pausableSystemManager.AddSystem(std::make_shared<KillerSystem>(world));

    graphicsSystemManager.AddSystem(std::make_shared<DrawSystem>(world, engine));
    graphicsSystemManager.AddSystem(std::make_shared<ShowGridSystem>(world, engine));  
    
    graphicsSystemManager.AddSystem(std::make_shared<PauseSystem>(world, engine, _onPause));   
}

void GameScene::Init()
{   

    systemsManager.Initialize();
    pausableSystemManager.Initialize();
    graphicsSystemManager.Initialize();
}

void GameScene::Update(float dt)
{
    systemsManager.Update(dt);
    if (!_onPause)
    {
        pausableSystemManager.Update(dt);
    }
    graphicsSystemManager.Update(dt);
}