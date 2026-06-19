#include "MenuInitSystem.h"
#include <memory>
#include <unordered_map>

#include "../Components/CameraComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/AnimationStateComponent.h"
#include "../Components/AnimatorComponent.h"
#include "../Components/ButtonComponent.h"
#include "../Components/BoxColliderComponent.h"

#include "../ButtonEvents.h"

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

    // ----- BUTTONS INIT -----

    auto& aStatesStorage = world.GetStorage<AnimationStateComponent>();
    auto& aDictStorage = world.GetStorage<AnimatorComponent>();
    auto& buttonsStorage = world.GetStorage<ButtonComponent>();
    auto& collidersStorage = world.GetStorage<BoxColliderComponent>();

    auto bScale = _engine.Cfg().cfg["Scenes"]["Menu"]["Buttons"]["Scale"].get<float>();

    sf::Vector2f bCSize = {
        _engine.Cfg().cfg["Scenes"]["Menu"]["Buttons"]["CSize"]["x"].get<float>(),
        _engine.Cfg().cfg["Scenes"]["Menu"]["Buttons"]["CSize"]["y"].get<float>(),
    };
    // ----- PLAY BUTTON INIT -----

    auto bPlay = world.CreateEntity();
    
    buttonsStorage.Add(bPlay, {.OnClick = [&](){ quitButtonEvent(_engine); } });

    aStatesStorage.Add(bPlay, AnimationStateComponent{
        .currentState = AnimationNode::None,
        .nextState = AnimationNode::Idle,
        .isCycled = false,
        .currentFrame = 0,
        .timer = 0.f,
        .isFinal = false
    });

    auto playButtonAnimations = std::make_shared<std::unordered_map<AnimationNode, const Animation*>>();

    playButtonAnimations->insert( {
        AnimationNode::Idle, 
        _engine.Assets().GetAnimation(_engine.Cfg().cfg["Scenes"]["Menu"]["Buttons"]["Play"]["Idle"].get<std::string>())
    });
    playButtonAnimations->insert( {
        AnimationNode::Choosed, 
        _engine.Assets().GetAnimation(_engine.Cfg().cfg["Scenes"]["Menu"]["Buttons"]["Play"]["Choosed"].get<std::string>())
    });
    playButtonAnimations->insert( {
        AnimationNode::Activated, 
        _engine.Assets().GetAnimation(_engine.Cfg().cfg["Scenes"]["Menu"]["Buttons"]["Play"]["Pressed"].get<std::string>())
    });

    aDictStorage.Add(bPlay, AnimatorComponent{playButtonAnimations});

    auto btnPlay = std::make_shared<sf::Sprite>((*playButtonAnimations)[AnimationNode::Idle]->GetTexture());
    spritesStorage.Add(bPlay, {btnPlay});

    btnPlay->setTextureRect({
        {(*playButtonAnimations)[AnimationNode::Idle]->Offset()},
        {(*playButtonAnimations)[AnimationNode::Idle]->Size()}
    });

    btnPlay->setOrigin({
        0.5f * (*playButtonAnimations)[AnimationNode::Idle]->Size().x,
        1.0f * (*playButtonAnimations)[AnimationNode::Idle]->Size().y
    }); 

    btnPlay->setScale({bScale, bScale});

    collidersStorage.Add(bPlay, {
        .w = bCSize.x * bScale,
        .h = bCSize.y * bScale
    });

    posStorage.Add(bPlay, {
        .pos = {
            _engine.Cfg().cfg["Scenes"]["Menu"]["Buttons"]["Play"]["Position"]["x"].get<float>() * _engine.Window().getSize().x,
            _engine.Cfg().cfg["Scenes"]["Menu"]["Buttons"]["Play"]["Position"]["y"].get<float>() * _engine.Window().getSize().y,
        }
    });
}