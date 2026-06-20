#pragma once

#include "../../GameEngine/GameEngine.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/GravityComponent.h"

class FallingSystem final : public ISystem {
private:
    ComponentStorage<MovementComponent>& _moveStorage;
    ComponentStorage<PositionComponent>& _posStorage;
    ComponentStorage<GravityComponent>& _gravStorage;

public:
    FallingSystem(World &world)://, GameEngine& engine, InputMap& inputMap): 
        ISystem(world),
        _moveStorage(world.GetStorage<MovementComponent>()),
        _posStorage(world.GetStorage<PositionComponent>()),
        _gravStorage(world.GetStorage<GravityComponent>())
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
