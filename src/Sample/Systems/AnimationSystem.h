#pragma once

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/AnimationStateComponent.h"
#include "../Components/AnimatorComponent.h"
#include "../Components/SpriteComponent.h"

class AnimationSystem final: public ISystem
{
private:
    ComponentStorage<AnimationStateComponent>& _AStateStorage;
    ComponentStorage<AnimatorComponent>& _animationsStorage;
    ComponentStorage<SpriteComponent>& _spritesStorage;
public:
    AnimationSystem(World& world):
        ISystem(world),
        _AStateStorage(world.GetStorage<AnimationStateComponent>()),
        _animationsStorage(world.GetStorage<AnimatorComponent>()),
        _spritesStorage(world.GetStorage<SpriteComponent>())
    {}

    void OnInit() override {}
    void OnUpdate(float dt) override;
};