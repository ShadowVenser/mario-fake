#pragma once

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/BulletComponent.h"
#include "../Components/FinishComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/CollisionEventComponent.h"
#include "../Components/KillMeComponent.h"

class ColliderSystem final : public ISystem {
    //using InputMap = std::unordered_map<std::string, std::shared_ptr<InputAction>>;
private:
    ComponentStorage<MovementComponent>& _moveStorage;
    ComponentStorage<PositionComponent>& _posStorage;
    ComponentStorage<BoxColliderComponent>& _colliderStorage;
    ComponentStorage<BulletComponent>& _bulletStorage;
    ComponentStorage<FinishComponent>& _finishStorage;
    ComponentStorage<PlayerComponent>& _playerStorage;
    ComponentStorage<CollisionEventComponent>& _collisionStorage;
    ComponentStorage<KillMeComponent>& _killMeStorage;
    float _gridSize;
    // GameEngine& _engine;
    // InputMap& _inputMap;

public:
    ColliderSystem(World &world, float gridsize)://, GameEngine& engine, InputMap& inputMap): 
        ISystem(world),
        _moveStorage(world.GetStorage<MovementComponent>()),
        _posStorage(world.GetStorage<PositionComponent>()),
        _colliderStorage(world.GetStorage<BoxColliderComponent>()),
        _bulletStorage(world.GetStorage<BulletComponent>()),
        _finishStorage(world.GetStorage<FinishComponent>()),
        _playerStorage(world.GetStorage<PlayerComponent>()),
        _collisionStorage(world.GetStorage<CollisionEventComponent>()),
        _killMeStorage(world.GetStorage<KillMeComponent>()),
        _gridSize(gridsize)
        // _engine(engine),
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
