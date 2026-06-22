#pragma once

#include "../../Ecs/Systems/ISystem.h"
#include "../../Ecs/Filter/FilterBuilder.h"

#include "../../GameEngine/GameEngine.h"

#include "../Components/AnimationStateComponent.h"
#include "../Components/AnimatorComponent.h"
#include "../Components/BreakableComponent.h"
#include "../Components/CollisionEventComponent.h"
#include "../Components/KillMeComponent.h"
#include "../Components/SpriteComponent.h"


class BrickDestructionSystem final: public ISystem
{
private:
    ComponentStorage<AnimationStateComponent>& _ASStorage;
    ComponentStorage<AnimatorComponent>& _animatorStorage;
    ComponentStorage<BreakableComponent>& _breackableStorage;
    ComponentStorage<CollisionEventComponent>& _collisionStorage;
    ComponentStorage<KillMeComponent>& _suicideStorage;
    ComponentStorage<SpriteComponent>& _spriteStorage;

    std::shared_ptr<Filter> _breakableOnDelete;

    const AnimationStateComponent _asTemplate;
    const Animation* const _breakAnimation;

public:
    BrickDestructionSystem(World& world, GameEngine& engine):
        ISystem(world),
        _ASStorage(world.GetStorage<AnimationStateComponent>()),
        _animatorStorage(world.GetStorage<AnimatorComponent>()),
        _breackableStorage(world.GetStorage<BreakableComponent>()),
        _collisionStorage(world.GetStorage<CollisionEventComponent>()),
        _suicideStorage(world.GetStorage<KillMeComponent>()),
        _spriteStorage(world.GetStorage<SpriteComponent>()),
        _asTemplate({
            AnimationNode::Idle,
            AnimationNode::None,
            false,
            0,
            0.f,
            false
        }),
        _breakAnimation(
            engine.Assets().GetAnimation(
                engine.Cfg().cfg["Scenes"]["Game"]["Entities"]["Brick"]["Idle"].get<std::string>()
            )
        )
    { 
        FilterBuilder builder{world};
        _breakableOnDelete = builder
            .With<BreakableComponent>()
            .With<AnimationStateComponent>()
            .OptimisedBy<BreakableComponent>()
            .Build();
    }

    void OnInit() override;
    void OnUpdate(float dt) override;
};