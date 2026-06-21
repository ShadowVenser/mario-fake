#include "GameInitSystem.h"

#include "nlohmann/json.hpp"
#include <memory>
#include <map>

#include "../Components/CameraComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/BaseSpeedComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/GravityComponent.h"
#include "../Components/FinishComponent.h"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"



void GameInitSystem::OnInit()
{
    _engine.Window().setTitle("NOT MAIN MENU");

    
    auto& spritesStorage = world.GetStorage<SpriteComponent>();
    auto& playerStorage = world.GetStorage<PlayerComponent>();
    auto& baseSpeedStorage = world.GetStorage<BaseSpeedComponent>();
    auto& moveStorage = world.GetStorage<MovementComponent>();
    auto& gravityStorage = world.GetStorage<GravityComponent>();
    auto& posStorage = world.GetStorage<PositionComponent>();
    auto& colliderStorage = world.GetStorage<BoxColliderComponent>();
    auto& finishStorage = world.GetStorage<FinishComponent>();
    // auto& textsStorage = world.GetStorage<TextComponent>();
    auto& camerasStorage = world.GetStorage<CameraComponent>();


    // ----- LEVEL INIT -----
    
    std::ifstream f(std::string{_engine.Cfg().LevelFile.cbegin(), _engine.Cfg().LevelFile.cend()});
    if (f.is_open()){
        nlohmann::json lvlJson = nlohmann::json::parse(f);
        const auto& gameSceneJson = _engine.Cfg().cfg["Scenes"]["Game"];

        auto tileSize = gameSceneJson["Grid"]["TileSize"].get<unsigned int>();
        auto fTileSize = static_cast<float>(tileSize);

        std::map<std::string, std::shared_ptr<sf::Sprite>> spriteMap = {};        
        for (const auto &pair : gameSceneJson["Entities"].items()) {                     // автоматическая подгрузка спрайтов        // и тут я понял, что я долбоеб, потому что она у тебя уже есть в ассетах; с другой стороны, ты тоже долбоеб, потому что возвращаешь ссыль, а не shared_ptr
            const auto &value = pair.value();
            const auto &key = pair.key();
            if (value.contains("Texture") && !value["Texture"].is_null()){
                auto spritePtr = std::make_shared<sf::Sprite>(*_engine.Assets().GetTexture(value["Texture"].get<std::string>()));
                
                auto sptSize = spritePtr->getTexture().getSize();
                
                spritePtr->setOrigin({
                    static_cast<float>((sptSize.x>tileSize)? tileSize : sptSize.x) / 2.f, 
                    static_cast<float>(sptSize.y * 2 - ((sptSize.y>tileSize)? tileSize : sptSize.y)) / 2.f   //
                });
                spriteMap[key] = spritePtr;
            }
        }
        
        
        auto createEntity = [&](std::string name, int x, int y) {          // вынес в лямбду, потому что могу
            if (!gameSceneJson["Entities"].contains(name)) return;
            const auto& entityJson = gameSceneJson["Entities"][name];
            
            const auto newEntity = world.CreateEntity();
            
            posStorage.Add(
                newEntity,
                {{
                    static_cast<float>((x) * tileSize + tileSize / 2.f),
                    static_cast<float>(_engine.Window().getSize().y - y * tileSize - tileSize / 2.f)
                }}
            );
            if (entityJson.contains("Texture") && !entityJson["Texture"].is_null()){
                spritesStorage.Add(newEntity, {.sprite = spriteMap[name]});
            }
            if (entityJson.contains("PlayerComponent")){
                playerStorage.Add(newEntity, {});
            }
            if (entityJson.contains("BaseSpeed")){
                baseSpeedStorage.Add(
                    newEntity, 
                    {
                        .moveSpeed = entityJson["BaseSpeed"]["MoveSpeed"].get<float>() * fTileSize,
                        .jumpInitial = entityJson["BaseSpeed"]["JumpInitial"].get<float>() * fTileSize
                    }
                );
            }
            if (entityJson.contains("MovementComponent")){
                if (entityJson["MovementComponent"].contains("MaxSpeed")){
                    moveStorage.Add(newEntity, { entityJson["MovementComponent"]["MaxSpeed"].get<float>()});
                } else{
                    moveStorage.Add(newEntity, {});
                }
            }

            if (entityJson.contains("Collider")){  
                auto size = spriteMap[name]->getTexture().getSize();
                int width = size.x;
                int height = size.y;
                if (entityJson["Collider"].contains("Width")){
                    width = entityJson["Collider"]["Width"].get<unsigned int>();
                }
                if (entityJson["Collider"].contains("Height")){
                    height = entityJson["Collider"]["Height"].get<unsigned int>();
                }
                colliderStorage.Add(newEntity, {static_cast<float>(width), static_cast<float>(height)});
            }
            if (entityJson.contains("Gravity")){  
                gravityStorage.Add(newEntity, {entityJson["Gravity"].get<float>() * fTileSize});
            }
            if (entityJson.contains("Finish")){  
                finishStorage.Add(newEntity, {});
            }


            // ДОБАВЛЯТЬ НОВЫЕ КОМПОНЕНТЫ СЮДА

            
        };

        if (lvlJson.contains("BackgroundObjects")){
            for (const auto& obj : lvlJson["BackgroundObjects"]) {

                std::string objType = obj["name"].get<std::string>();
                int x = obj["x"].get<int>();
                int y = obj["y"].get<int>();

                createEntity(objType, x, y);            
            }
        }
        for (const auto& obj : lvlJson["MassObjects"]) {                  // считывание level.json

            std::string objType = obj["name"].get<std::string>();
            int x1 = obj["x1"].get<int>();
            int y1 = obj["y1"].get<int>();
            int x2 = obj["x2"].get<int>();
            int y2 = obj["y2"].get<int>();
            
            for (int i = x1; i<=x2; i++) {
                for (int j = y1; j<=y2; j++) {
                    createEntity(objType, i, j); 
                }
            }           
        }
        for (const auto& obj : lvlJson["SingleObjects"]) {

            std::string objType = obj["name"].get<std::string>();
            int x = obj["x"].get<int>();
            int y = obj["y"].get<int>();

            createEntity(objType, x, y);            
        }
        
        // ----- CAMERA INIT -----
        float windowH = static_cast<float>(_engine.Window().getSize().y);
        float windowW = static_cast<float>(_engine.Window().getSize().x);
        float x = windowW/2.f;
        if (playerStorage.Count()>0){
            x = posStorage.All()[playerStorage.Entities()[0]].pos.x;
        }
        std::shared_ptr<sf::View> followXView = std::make_shared<sf::View>(sf::View({x,windowH/2.f},{windowW, windowH}));
            
        _engine.Window().setView(*followXView);
        auto camera = world.CreateEntity();
        camerasStorage.Add(camera, {.type=CameraType::FollowX, .view=followXView}); //::FollowX
    }

    ////////////////////////////////////       писать дальше

}