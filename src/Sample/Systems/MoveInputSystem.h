#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../../GameEngine/Input/InputManager.h"

#include "../Components/PlayerComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/BaseSpeedComponent.h"

class MoveInputSystem final : public ISystem {
    using InputMap = std::unordered_map<std::string, std::shared_ptr<InputAction>>;
private:
    ComponentStorage<MovementComponent>& _moveStorage;
    ComponentStorage<PlayerComponent>& _playerStorage;
    ComponentStorage<BaseSpeedComponent>& _baseSpeedStorage;
    GameEngine& _engine;
    InputMap& _inputMap;

public:
    MoveInputSystem(World &world, GameEngine& engine, InputMap& inputMap): 
        ISystem(world),
        _moveStorage(world.GetStorage<MovementComponent>()),
        _playerStorage(world.GetStorage<PlayerComponent>()),
        _baseSpeedStorage(world.GetStorage<BaseSpeedComponent>()),
        _engine(engine),
        _inputMap(inputMap)
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
