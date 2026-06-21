#pragma once

#include "SFML/Graphics.hpp"


#include "../../Ecs/Systems/ISystem.h"

#include "../../GameEngine/Input/InputAction.h"

#include "../Components/PlayerComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"

class ShootingSystem final : public ISystem {
    using InputMap = std::unordered_map<std::string, std::shared_ptr<InputAction>>;
private:
    ComponentStorage<PlayerComponent>& _playerStorage;
    ComponentStorage<PositionComponent>& _posStorage;
    ComponentStorage<MovementComponent>& _moveStorage;
    ComponentStorage<BulletComponent>& _bulletStorage;
    ComponentStorage<SpriteComponent>& _spriteStorage;
    ComponentStorage<BoxColliderComponent>& _collStorage;
    InputMap& _inputMap;
    float _playerDir = 1.f;
    float _bulletHeight;
    float _bulletCurrentCooldown = 0.f;
    float _bulletCooldown;
    float _bulletSpeedX;
    float _bulletSpeedY;
    std::shared_ptr<sf::Sprite> _bulletSprite;

public:
    ShootingSystem(World &world, InputMap& inputMap, float bulletSpeedX, float bulletSpeedY, std::shared_ptr<sf::Sprite>& bulletSprite, float heightOffset, float cooldown): 
        ISystem(world),
        _playerStorage(world.GetStorage<PlayerComponent>()),
        _posStorage(world.GetStorage<PositionComponent>()),
        _moveStorage(world.GetStorage<MovementComponent>()),
        _bulletStorage(world.GetStorage<BulletComponent>()),
        _spriteStorage(world.GetStorage<SpriteComponent>()),
        _collStorage(world.GetStorage<BoxColliderComponent>()),
        _inputMap(inputMap),
        _bulletHeight(heightOffset),
        _bulletCooldown(cooldown),
        _bulletSpeedX(bulletSpeedX),
        _bulletSpeedY(bulletSpeedY),
        _bulletSprite(bulletSprite)
    {
        auto size = _bulletSprite->getTexture().getSize();
        _bulletSprite->setOrigin({static_cast<float>(size.x)/2.f, static_cast<float>(size.y)/2.f});
    }

    void OnInit() override { }

    void OnUpdate(float) override;
};
