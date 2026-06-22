#pragma once

#include "SFML/Graphics.hpp"


#include "../../Ecs/Systems/ISystem.h"

#include "../../GameEngine/Input/InputAction.h"
#include "../../GameEngine/Assets/Animation.h"
#include "../../GameEngine/GameEngine.h"

#include "../Components/PlayerComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/AnimationStateComponent.h"
#include "../Components/AnimatorComponent.h"

class ShootingSystem final : public ISystem {
    using InputMap = std::unordered_map<std::string, std::shared_ptr<InputAction>>;
private:
    ComponentStorage<PlayerComponent>& _playerStorage;
    ComponentStorage<PositionComponent>& _posStorage;
    ComponentStorage<MovementComponent>& _moveStorage;
    ComponentStorage<BulletComponent>& _bulletStorage;
    ComponentStorage<SpriteComponent>& _spriteStorage;
    ComponentStorage<BoxColliderComponent>& _collStorage;
    ComponentStorage<AnimationStateComponent>& _ASStorage;
    ComponentStorage<AnimatorComponent>& _AnimatorsStorage;
    InputMap& _inputMap;
    float _playerDir = 1.f;
    float _bulletHeight;
    float _bulletCurrentCooldown = 0.f;
    float _bulletCooldown;
    float _bulletSpeedX;
    float _bulletSpeedY;

    const BoxColliderComponent _box;
    AnimationStateComponent _aState;
    const Animation& _animation;

public:
    ShootingSystem(World &world, GameEngine& engine, InputMap& inputMap, float bulletSpeedX, float bulletSpeedY, float heightOffset, float cooldown): 
        ISystem(world),
        _playerStorage(world.GetStorage<PlayerComponent>()),
        _posStorage(world.GetStorage<PositionComponent>()),
        _moveStorage(world.GetStorage<MovementComponent>()),
        _bulletStorage(world.GetStorage<BulletComponent>()),
        _spriteStorage(world.GetStorage<SpriteComponent>()),
        _collStorage(world.GetStorage<BoxColliderComponent>()),
        _ASStorage(world.GetStorage<AnimationStateComponent>()),
        _AnimatorsStorage(world.GetStorage<AnimatorComponent>()),
        _inputMap(inputMap),
        _bulletHeight(heightOffset),
        _bulletCooldown(cooldown),
        _bulletSpeedX(bulletSpeedX),
        _bulletSpeedY(bulletSpeedY),
        _box({
            .w = engine.Cfg().cfg["Scenes"]["Game"]["Entities"]["Bullet"]["Collider"]["Width"].get<float>(),
            .h = engine.Cfg().cfg["Scenes"]["Game"]["Entities"]["Bullet"]["Collider"]["Height"].get<float>()
        }),
        _aState({
            AnimationNode::Idle,
            AnimationNode::None,
            true,
            0, 0.f
        }),
        _animation(*engine.Assets().GetAnimation(engine.Cfg().cfg["Scenes"]["Game"]["Entities"]["Bullet"]["Animation"].get<std::string>()))
    {
        // auto size = _bulletSprite->getTexture().getSize();
        // _bulletSprite->setOrigin({static_cast<float>(size.x)/2.f, static_cast<float>(size.y)/2.f});
    }

    void OnInit() override { };

    void OnUpdate(float) override;
};
