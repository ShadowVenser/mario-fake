#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../../GameEngine/Input/InputManager.h"

class AdditionalControlSystem final : public ISystem {
    using InputMap = std::unordered_map<std::string, std::shared_ptr<InputAction>>;
private:
    GameEngine& _engine;
    InputMap& _inputMap;

public:
    AdditionalControlSystem(World &world, GameEngine& engine, InputMap& inputMap): 
        ISystem(world),
        _engine(engine),
        _inputMap(inputMap)
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
