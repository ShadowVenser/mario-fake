#include "ShootingSystem.h"
#include <memory>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

void ShootingSystem::OnUpdate(float t) {

    if (_playerStorage.Count() == 0) return;


    MovementComponent* move;
    PositionComponent* plPos;
    BoxColliderComponent* plColl;

    for (auto& id: _playerStorage.Entities())
    {
        if (!world.IsEntityAlive(id))
            continue;
        move = &_moveStorage[id];
        plPos = &_posStorage[id];
        plColl = &_collStorage[id];
        break;
    }
    
    if (move->xSpeed>0.f){
        _playerDir = 1.f;
    } else if (move->xSpeed<0.f){  // если 0, ничего не меняем; по умолчанию вправо
        _playerDir = -1.f;
    }


    _bulletCurrentCooldown -= t;
    if (_inputMap["Shoot"]->Type()==ActionType::Start && _bulletCurrentCooldown <= 0.f) {
        _bulletCurrentCooldown = _bulletCooldown;
        auto bullet = world.CreateEntity();
        _bulletStorage.Add(bullet, {});
        _spriteStorage.Add(bullet, {.sprite = _bulletSprite});
        auto size = _bulletSprite->getTexture().getSize();
        _collStorage.Add(
            bullet, 
            {
                .w = static_cast<float>(size.x), 
                .h = static_cast<float>(size.y)
            });
        _posStorage.Add(
            bullet, 
            {{
                (plPos->pos.x+_playerDir*(plColl->w + static_cast<float>(size.x))/2.f), 
                (plPos->pos.y+_bulletHeight)
            }}
        );
        _moveStorage.Add(bullet, {_bulletSpeedX*_playerDir, _bulletSpeedY});
    }
}