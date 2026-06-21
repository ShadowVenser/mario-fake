#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../../GameEngine/Input/InputManager.h"

#include "../Components/PlayerComponent.h"
#include "../Components/KillMeComponent.h"

class RespawnSystem final : public ISystem {
private:
    GameEngine& _engine;
    ComponentStorage<PlayerComponent>& _playerStorage;
    ComponentStorage<KillMeComponent>& _killMeStorage;

public:
    RespawnSystem(World &world, GameEngine& engine): 
        ISystem(world),
        _engine(engine),
        _playerStorage(world.GetStorage<PlayerComponent>()),
        _killMeStorage(world.GetStorage<KillMeComponent>())
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
