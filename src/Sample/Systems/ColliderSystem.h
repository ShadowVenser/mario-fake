#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/BoxColliderComponent.h"

class ColliderSystem final : public ISystem {
    //using InputMap = std::unordered_map<std::string, std::shared_ptr<InputAction>>;
private:
    ComponentStorage<MovementComponent>& _moveStorage;
    ComponentStorage<PositionComponent>& _posStorage;
    ComponentStorage<BoxColliderComponent>& _colliderStorage;
    float _gridSize;
    // GameEngine& _engine;
    // InputMap& _inputMap;

public:
    ColliderSystem(World &world, float gridsize)://, GameEngine& engine, InputMap& inputMap): 
        ISystem(world),
        _moveStorage(world.GetStorage<MovementComponent>()),
        _posStorage(world.GetStorage<PositionComponent>()),
        _colliderStorage(world.GetStorage<BoxColliderComponent>()),
        _gridSize(gridsize)
        // _engine(engine),
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
