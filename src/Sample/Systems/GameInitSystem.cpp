#include "GameInitSystem.h"

#include "nlohmann/json.hpp"
#include <memory>
#include <map>

#include "../Components/CameraComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/TextComponent.h"

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"



void GameInitSystem::OnInit()
{
    _engine.Window().setTitle("NOT MAIN MENU");

    
    auto& spritesStorage = world.GetStorage<SpriteComponent>();
    auto& playerStorage = world.GetStorage<PlayerComponent>();
    auto& moveStorage = world.GetStorage<MovementComponent>();
    auto& posStorage = world.GetStorage<PositionComponent>();
    // auto& textsStorage = world.GetStorage<TextComponent>();
    auto& camerasStorage = world.GetStorage<CameraComponent>();

    // ----- CAMERA INIT -----
    _engine.Window().setView(_engine.Window().getDefaultView());
    
    auto camera = world.CreateEntity();
    camerasStorage.Add(camera, {.type=CameraType::Default, .view=nullptr}); //::FollowX

    // ----- LEVEL INIT -----
    
    std::ifstream f(std::string{_engine.Cfg().LevelFile.cbegin(), _engine.Cfg().LevelFile.cend()});
    if (f.is_open()){
        nlohmann::json lvlJson = nlohmann::json::parse(f);
        const auto& gameSceneJson = _engine.Cfg().cfg["Scenes"]["Game"];

        auto tileSize = gameSceneJson["Grid"]["TileSize"].get<unsigned int>();


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
                playerStorage.Add(newEntity, {.jumpInitialSpeed = entityJson["PlayerComponent"]["JumpSpeed"].get<float>()});
            }
            if (entityJson.contains("MovementComponent")){
                moveStorage.Add(newEntity, {.baseSpeed = entityJson["MovementComponent"]["BaseSpeed"].get<float>()});
            }

            ///////////////// Системы коллайдеров нет, но вот тебе заглушка, чтобы было, с чем работать; 
            //я бы жестко поменял внутренности коллайдера сам, но это твой код, без тебя не полезу;
            // предположительно я бы въебал флаг на физику (стопает ли движение, или пуля и похуй) + оффсет от центра
            // оффсет в целом можешь динамически вычислять, спизди из этого файла на ctrl+f "setOrigin" и замени sptSize.x на w и sptSize.y на h

            // if (entityJson.contains("Collider")){  
            //     auto size = spriteMap[name]->getTexture().getSize();
            //     moveStorage.Add(newEntity, {size.x, size.y});
            // }


            // ДОБАВЛЯТЬ НОВЫЕ КОМПОНЕНТЫ СЮДА

            
        };


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

    }

    ////////////////////////////////////       писать дальше

}