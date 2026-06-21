#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../../GameEngine/Input/InputAction.h"

class AdditionalControlSystem final : public ISystem {
    using InputMap = std::unordered_map<std::string, std::shared_ptr<InputAction>>;
private:
    GameEngine& _engine;
    InputMap& _inputMap;
    bool& _onPause;
    
    const float _pauseCooldown;
    bool _onCooldown = false;
    float timer = 0.f;

public:
    AdditionalControlSystem(World &world, GameEngine& engine, InputMap& inputMap, bool& onPause, float cooldown): 
        ISystem(world),
        _engine(engine),
        _inputMap(inputMap), 
        _onPause(onPause), 
        _pauseCooldown(cooldown)
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
