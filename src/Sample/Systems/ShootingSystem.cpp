#include "ShootingSystem.h"
#include <memory>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include "../Components/AnimatorComponent.h"

void ShootingSystem::OnUpdate(float t) {

    if (_playerStorage.Count() == 0) return;


    MovementComponent* move;
    PositionComponent* plPos;
    BoxColliderComponent* plColl;
    PlayerComponent* player;

    for (auto& id: _playerStorage.Entities())
    {
        if (!world.IsEntityAlive(id))
            continue;
        move = &_moveStorage[id];
        plPos = &_posStorage[id];
        plColl = &_collStorage[id];
        player = &_playerStorage[id];
        break;
    }
    
    if (move->xSpeed>0.f){
        _playerDir = 1.f;
    } else if (move->xSpeed<0.f){  // если 0, ничего не меняем; по умолчанию вправо
        _playerDir = -1.f;
    }

    if (_bulletCurrentCooldown <= 0.f)
    {
        player->events |=  PlayerComponent::CAN_SHOOT;
    }
    else 
    {
        player->events &= ~PlayerComponent::CAN_SHOOT;
    }

    _bulletCurrentCooldown -= t;
    // if (_inputMap["Shoot"]->Type()==ActionType::Start && _bulletCurrentCooldown <= 0.f) {
    if (player->events & PlayerComponent::SHOOT_EVENT) {
        _bulletCurrentCooldown = _bulletCooldown;
        
        auto bullet = world.CreateEntity();
        
        _bulletStorage.Add(bullet, {});
        
        auto sp = std::make_shared<sf::Sprite>(_animation.GetTexture());
        sp->setTextureRect(
            {_animation.Offset(), _animation.Size()}
        );
        sp->setOrigin({_animation.Size().x / 2.f, _animation.Size().y / 2.f});

        _aState.isReflected = _playerDir < 0;
        _ASStorage.Add(bullet, _aState);

        _spriteStorage.Add(bullet, {.sprite = sp});
        
        auto aniMap = std::make_shared<AnimatorComponent::AMap>();
        aniMap->insert({AnimationNode::Idle, &_animation});
        _AnimatorsStorage.Add(bullet, {aniMap});
        
        _collStorage.Add(
            bullet, 
            _box
        );
        
        _posStorage.Add(
            bullet, 
            {{
                (plPos->pos.x+_playerDir*(plColl->w + static_cast<float>(_box.w))/2.f), 
                (plPos->pos.y+_bulletHeight)
            }}
        );
        _moveStorage.Add(bullet, {_bulletSpeedX*_playerDir, _bulletSpeedY});

        player->events &= ~PlayerComponent::SHOOT_EVENT;
        player->events &= ~PlayerComponent::CAN_SHOOT;
    }
}