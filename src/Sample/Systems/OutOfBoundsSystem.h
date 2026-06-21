#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../../GameEngine/Input/InputManager.h"

#include "../Components/PlayerComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/KillMeComponent.h"

class OutOfBoundsSystem final : public ISystem {
    using InputMap = std::unordered_map<std::string, std::shared_ptr<InputAction>>;
private:
    ComponentStorage<PlayerComponent>& _playerStorage;
    ComponentStorage<PositionComponent>& _posStorage;
    ComponentStorage<KillMeComponent>& _killMeStorage;
    float _windowHeight;

public:
    OutOfBoundsSystem(World &world, float windowHeight): 
        ISystem(world),
        _playerStorage(world.GetStorage<PlayerComponent>()),
        _posStorage(world.GetStorage<PositionComponent>()),
        _killMeStorage(world.GetStorage<KillMeComponent>()),
        _windowHeight(windowHeight)
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
