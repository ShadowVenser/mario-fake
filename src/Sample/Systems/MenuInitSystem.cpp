#include "MenuInitSystem.h"
#include <memory>

#include "../Components/CameraComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TextComponent.h"

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

void MenuInitSystem::OnInit()
{
    _engine.Window().setTitle("MAIN MENU");
    
    auto& spritesStorage = world.GetStorage<SpriteComponent>();
    auto& posStorage = world.GetStorage<PositionComponent>();
    auto& textsStorage = world.GetStorage<TextComponent>();
    auto& camerasStorage = world.GetStorage<CameraComponent>();

    // ----- CAMEA INIT -----
    _engine.Window().setView(_engine.Window().getDefaultView());
    
    auto camera = world.CreateEntity();
    camerasStorage.Add(camera, {.type=CameraType::Default, .view=nullptr});

    // ----- BG INIT -----

    const auto bg = world.CreateEntity();

    auto bgSpritePtr = std::make_shared<sf::Sprite>(*_engine.Assets().GetTexture(
        _engine.Cfg().cfg["Scenes"]["Menu"]["BG"].get<std::string>()
    ));

    spritesStorage.Add(bg, {.sprite = bgSpritePtr});

    auto& bgSprite = *bgSpritePtr;

    float scale {std::max(
        static_cast<float>(_engine.Window().getSize().x) / bgSprite.getTexture().getSize().x, 
        static_cast<float>(_engine.Window().getSize().y) / bgSprite.getTexture().getSize().y
    )};
    
    bgSprite.setScale({scale, scale});

    sf::FloatRect bounds = bgSprite.getGlobalBounds();

    posStorage.Add(
        bg,
        {{
            (static_cast<float>(_engine.Window().getSize().x) - bounds.size.x) / 2.f,
            (static_cast<float>(_engine.Window().getSize().y) - bounds.size.y) / 2.f
        }}
    );

    bgSprite.setColor({160, 160, 160, 255});
    
    // ----- TITLE INIT -----

    auto title = world.CreateEntity();

    // auto& titleFont = _engine.Assets().GetFont();

    textsStorage.Add(
        title, 
        {
            _engine.Cfg().cfg["Scenes"]["Menu"]["Title"]["Text"].get<std::string>(),
            _engine.Cfg().cfg["Scenes"]["Menu"]["Title"]["Font"].get<std::string>(),
            _engine.Cfg().cfg["Scenes"]["Menu"]["Title"]["Size"].get<unsigned int>(),
        }
    );

    sf::Vector2f centredPos = 
    {
        _engine.Cfg().cfg["Scenes"]["Menu"]["Title"]["Position"]["x"].get<float>() * _engine.Window().getSize().x,
        _engine.Cfg().cfg["Scenes"]["Menu"]["Title"]["Position"]["y"].get<float>() * _engine.Window().getSize().y   
    };

    posStorage.Add(
        title,
        { centredPos }
    );
}