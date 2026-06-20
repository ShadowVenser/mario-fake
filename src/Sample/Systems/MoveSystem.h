#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../../GameEngine/Input/InputManager.h"

#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"

class MoveSystem final : public ISystem {
    //using InputMap = std::unordered_map<std::string, std::shared_ptr<InputAction>>;
private:
    ComponentStorage<MovementComponent>& _moveStorage;
    ComponentStorage<PositionComponent>& _posStorage;
    // GameEngine& _engine;
    // InputMap& _inputMap;

public:
    MoveSystem(World &world)://, GameEngine& engine, InputMap& inputMap): 
        ISystem(world),
        _moveStorage(world.GetStorage<MovementComponent>()),
        _posStorage(world.GetStorage<PositionComponent>())
        // _engine(engine),
        // _inputMap(inputMap)
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
