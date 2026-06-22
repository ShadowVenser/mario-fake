#pragma once

#include "../../Ecs/Systems/ISystem.h"

#include "../../GameEngine/GameEngine.h"
#include "../../GameEngine/Input/InputAction.h"

#include "../Components/PlayerComponent.h"
#include "../Components/AnimationStateComponent.h"
#include "../Components/MovementComponent.h"
#include "nlohmann/json.hpp"

class RinStatesSystems final: public ISystem
{
private:
    using InputMap = std::unordered_map<std::string, std::shared_ptr<InputAction>>;
    using AnimationsMap = std::unordered_map<std::string, Animation>;
    using json = nlohmann::json;

    json _playerAConfig;
    const AnimationsMap& _animations; 

    ComponentStorage<PlayerComponent>& _playersStorage;
    ComponentStorage<AnimationStateComponent>& _ASStorage;
    ComponentStorage<MovementComponent>& _moveComponent;

    InputAction& _shootAcion;
    InputAction& _jumpAction;
    InputAction& _leftAction;
    InputAction& _rightAction;

public:
    RinStatesSystems(World& world, GameEngine& engine, InputMap& inActions):
        ISystem(world),
        _playerAConfig(
            engine.Cfg().cfg["Scenes"]["Game"]["Entities"]["Player"]["Animations"]
        ),
        _animations(engine.Assets().GetAnimations()),
        _playersStorage(world.GetStorage<PlayerComponent>()),
        _ASStorage(world.GetStorage<AnimationStateComponent>()),
        _moveComponent(world.GetStorage<MovementComponent>()),
        _shootAcion(*inActions["Shoot"]),
        _jumpAction(*inActions["Jump"]),
        _leftAction(*inActions["Left"]),
        _rightAction(*inActions["Right"])
    { }

    void OnInit() override;
    void OnUpdate(float) override;
};