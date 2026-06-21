#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../../GameEngine/Input/InputManager.h"

#include "../Components/BulletComponent.h"
#include "../Components/CollisionEventComponent.h"
#include "../Components/KillMeComponent.h"
#include "../Components/PlayerComponent.h"

class BulletDeleteSystem final : public ISystem {
private:
    ComponentStorage<CollisionEventComponent>& _collisionStorage;
    ComponentStorage<BulletComponent>& _bulletStorage;
    ComponentStorage<KillMeComponent>& _killMeStorage;
    ComponentStorage<PlayerComponent>& _playerStorage;
public:
    BulletDeleteSystem(World &world): 
        ISystem(world),
        _collisionStorage(world.GetStorage<CollisionEventComponent>()),
        _bulletStorage(world.GetStorage<BulletComponent>()),
        _killMeStorage(world.GetStorage<KillMeComponent>()),
        _playerStorage(world.GetStorage<PlayerComponent>())
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
