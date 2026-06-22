#pragma once

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/FinishComponent.h"
#include "../Components/CollisionEventComponent.h"
#include "../Components/SoundEventComponent.h"
#include "../Components/KillMeComponent.h"

class sfxCollisionSystem final : public ISystem {
private:
    ComponentStorage<FinishComponent>& _finishStorage;
    ComponentStorage<CollisionEventComponent>& _collisionStorage;
    ComponentStorage<SoundEventComponent>& _soundStorage;
    ComponentStorage<KillMeComponent>& _killMeStorage;
    std::string _boomSound;

public:
    sfxCollisionSystem(World &world, std::string boomsound)://, GameEngine& engine, InputMap& inputMap): 
        ISystem(world),
        _finishStorage(world.GetStorage<FinishComponent>()),
        _collisionStorage(world.GetStorage<CollisionEventComponent>()),
        _soundStorage(world.GetStorage<SoundEventComponent>()),        
        _killMeStorage(world.GetStorage<KillMeComponent>()),
        _boomSound(boomsound)
        // _engine(engine),
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
