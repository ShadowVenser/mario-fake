#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PlayerComponent.h"
#include "../Components/CollisionEventComponent.h"
#include "../Components/FinishComponent.h"

class FinishSystem final : public ISystem {
    using InputMap = std::unordered_map<std::string, std::shared_ptr<InputAction>>;
private:
    ComponentStorage<CollisionEventComponent>& _collisionStorage;
    ComponentStorage<PlayerComponent>& _playerStorage;
    ComponentStorage<FinishComponent>& _finishStorage;
    GameEngine& _engine;

public:
    FinishSystem(World &world, GameEngine& engine): 
        ISystem(world),
        _collisionStorage(world.GetStorage<CollisionEventComponent>()),
        _playerStorage(world.GetStorage<PlayerComponent>()),
        _finishStorage(world.GetStorage<FinishComponent>()),
        _engine(engine)
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
