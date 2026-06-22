#include "RinStatesSystem.h"

#include <memory>
#include <stdexcept>

#include "../Components/AnimatorComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BaseSpeedComponent.h"

#include "SFML/Graphics/Sprite.hpp"

void RinStatesSystems::OnInit()
{
    int pId = -1;
    for (auto allP: _playersStorage.Entities()){
        if (!world.IsEntityAlive(allP))
            continue;
        pId = allP;
    }

    if (pId < 0) throw std::runtime_error("Can't find player");

    _ASStorage.Add(pId, {
        AnimationNode::None,
        AnimationNode::Idle,
        true,
        0,
        0.f, 
        false
    });
    
    auto& animationsStorage = world.GetStorage<AnimatorComponent>();
    std::shared_ptr<AnimatorComponent::AMap> animations = std::make_shared<AnimatorComponent::AMap>();

    animationsStorage.Add(pId, {animations});

    animations->insert({
        AnimationNode::Idle,
        &_animations.at(_playerAConfig["Idle"].get<std::string>())
    });

    animations->insert({
        AnimationNode::Move,
        &_animations.at(_playerAConfig["Move"].get<std::string>())
    });

    animations->insert({
        AnimationNode::JumpGU,
        &_animations.at(_playerAConfig["JumpGU"].get<std::string>())
    });

    animations->insert({
        AnimationNode::JumpAU,
        &_animations.at(_playerAConfig["JumpAU"].get<std::string>())
    });

    animations->insert({
        AnimationNode::JumpGD,
        &_animations.at(_playerAConfig["JumpGD"].get<std::string>())
    });

    animations->insert({
        AnimationNode::JumpAS,
        &_animations.at(_playerAConfig["JumpAS"].get<std::string>())
    });

    animations->insert({
        AnimationNode::JumpAD,
        &_animations.at(_playerAConfig["JumpAD"].get<std::string>())
    });

    animations->insert({
        AnimationNode::Shoot,
        &_animations.at(_playerAConfig["Shoot"].get<std::string>())
    });

    const auto& idle = *animations->at(AnimationNode::Idle);
    std::shared_ptr<sf::Sprite> sprite = std::make_shared<sf::Sprite>(idle.GetTexture());

    auto& spritesStorage = world.GetStorage<SpriteComponent>();
    spritesStorage.Add(pId, {sprite});
    sprite->setTextureRect({
        idle.Offset(), idle.Size()
    });
    sprite->setOrigin({
        idle.Size().x * 0.5f,
        idle.Size().y - 32.f
    });
}

void RinStatesSystems::OnUpdate(float)
{
    int pId = -1;
    for (auto allP: _playersStorage.Entities()){
        if (!world.IsEntityAlive(allP))
            continue;
        pId = allP;
    }

    if (pId < 0) throw std::runtime_error("Can't find player");

    static const float basicY = world.GetStorage<BaseSpeedComponent>()[pId].jumpInitial;

    auto& aState = _ASStorage[pId];
    auto& move = _moveComponent[pId];
    auto& player = _playersStorage[pId];


    bool isChanged = false;
    if (aState.currentState != aState.nextState) {
        isChanged = true;
        aState.currentState =  aState.nextState;
        aState.currentFrame = 0;
        aState.timer = 0.f;
        aState.isFinal = false;
    }
    
    aState.nextState = AnimationNode::None;
    // aState.isReflected = move.xSpeed < 0;
    if (aState.isReflected && _rightAction.Type() == ActionType::Start) aState.isReflected = false;
    if (!aState.isReflected && _leftAction.Type() == ActionType::Start) aState.isReflected = true;

    switch (aState.currentState) {
        case AnimationNode::Idle:
        {
            if (isChanged)
            {
                aState.isCycled = true;
            }
            if ((player.events & PlayerComponent::CAN_SHOOT) && _shootAcion.Type() == ActionType::Start)
            {
                aState.nextState = AnimationNode::Shoot;
                player.events |= PlayerComponent::SHOOT_EVENT;
                player.events &= ~PlayerComponent::CAN_MOVE;
                player.events &= ~PlayerComponent::CAN_SHOOT;
            }
            else if ((player.events & PlayerComponent::CAN_JUMP) && _jumpAction.Type() == ActionType::Start)
            {
                aState.nextState = AnimationNode::JumpGU;
                player.events &= ~PlayerComponent::CAN_JUMP;
                player.events |= PlayerComponent::JUMP_EVENT;
            }
            else if (move.xSpeed != 0)
            {
                aState.nextState = AnimationNode::Move;
            }
            else 
            {
                aState.nextState = AnimationNode::Idle;
            }
            break;
        }
        case AnimationNode::Move:
        {
            if (isChanged)
            {
                aState.isCycled = true;
            }
            if ((player.events & PlayerComponent::CAN_SHOOT) && _shootAcion.Type() == ActionType::Start)
            {
                aState.nextState = AnimationNode::Shoot;
                player.events |= PlayerComponent::SHOOT_EVENT;
                player.events &= ~PlayerComponent::CAN_MOVE;
                player.events &= ~PlayerComponent::CAN_SHOOT;
            }
            else if ((player.events & PlayerComponent::CAN_JUMP) && _jumpAction.Type() == ActionType::Start)
            {
                aState.nextState = AnimationNode::JumpGU;
                player.events &= ~PlayerComponent::CAN_JUMP;
                player.events |= PlayerComponent::JUMP_EVENT;
            }
            else if (move.xSpeed == 0)
            {
                aState.nextState = AnimationNode::Idle;
            }
            else 
            {
                aState.nextState = AnimationNode::Move;
            }
            break;
        }
        case AnimationNode::JumpGU:
        {
            if (isChanged)
            {
                aState.isCycled = false;
            }
            if (aState.isFinal)
            {
                aState.nextState = AnimationNode::JumpAU;
            }
            else 
            {
                aState.nextState = aState.currentState;
            }
            break;
        }
        case AnimationNode::JumpAU:
        {
            if (isChanged)
            {
                aState.isCycled = false;
            }
            if (std::abs(move.ySpeed) < basicY * 0.25f)
            {
                aState.nextState = AnimationNode::JumpAS;
            }
            else 
            {
                aState.nextState = aState.currentState;
            }
            break;
        }
        case AnimationNode::JumpAS:
        {
            if (isChanged)
            {
                aState.isCycled = false;
            }
            if (aState.isFinal)
            {
                aState.nextState = AnimationNode::JumpAD;
            }
            else 
            {
                aState.nextState = aState.currentState;
            }
            break;
        }
        case AnimationNode::JumpAD:
        {
            if (isChanged)
            {
                aState.isCycled = false;
            }
            if (move.ySpeed == 0.f)
            {
                aState.nextState = AnimationNode::JumpGD;
            }
            else 
            {
                aState.nextState = aState.currentState;
            }
            break;
        }
        case AnimationNode::JumpGD:
        {
            if (isChanged)
            {
                aState.isCycled = false;
            }
            if (aState.isFinal)
            {
                player.events |= PlayerComponent::CAN_JUMP;
                if (move.xSpeed != 0) aState.nextState = AnimationNode::Move;
                else aState.nextState = AnimationNode::Idle;
            }
            else 
            {
                aState.nextState = aState.currentState;
            }
            break;
        }
        case AnimationNode::Shoot:
        {
            if (isChanged)
            {
                aState.isCycled = false;
            }
            if (aState.isFinal)
            {
                player.events |= PlayerComponent::CAN_MOVE;
                bool la = _leftAction.Type() == ActionType::Pressed;
                bool ra = _rightAction.Type() == ActionType::Pressed;
                if (la ^ ra) 
                    aState.nextState = AnimationNode::Move;
                else 
                    aState.nextState = AnimationNode::Idle;
            }
            else 
            {
                aState.nextState = aState.currentState;
            }
            break;
        }
        default:
            throw std::runtime_error("Unknown Rin State!!!");
    }
}