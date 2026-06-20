#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../../GameEngine/Input/InputManager.h"

#include "../Components/PlayerComponent.h"
#include "../Components/MovementComponent.h"

class MoveInputSystem final : public ISystem {
    using InputMap = std::unordered_map<std::string, std::shared_ptr<InputAction>>;
private:
    ComponentStorage<MovementComponent>& _moveStorage;
    ComponentStorage<PlayerComponent>& _playerStorage;
    GameEngine& _engine;
    InputMap& _inputMap;

public:
    MoveInputSystem(World &world, GameEngine& engine, InputMap& inputMap): 
        ISystem(world),
        _moveStorage(world.GetStorage<MovementComponent>()),
        _playerStorage(world.GetStorage<PlayerComponent>()),
        _engine(engine),
        _inputMap(inputMap)
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
