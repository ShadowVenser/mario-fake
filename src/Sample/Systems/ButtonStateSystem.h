#pragma once

#include <memory>
#include <unordered_map>

#include "../../Ecs/Systems/ISystem.h"

#include "../../GameEngine/Input/InputAction.h"

#include "../Components/AnimationStateComponent.h"
#include "../Components/ButtonComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/PositionComponent.h"

class ButtonStateSystem final: public ISystem
{
private:
    std::shared_ptr<InputAction> _moveAction;
    std::shared_ptr<InputAction> _click;

    ComponentStorage<AnimationStateComponent>& _AStateComponent;
    ComponentStorage<ButtonComponent>& _buttonsStorage;
    ComponentStorage<BoxColliderComponent>& _collidersStorage;
    ComponentStorage<PositionComponent>& _posStorage;

public:
    ButtonStateSystem(World& world, std::unordered_map<std::string, std::shared_ptr<InputAction>>& actions): 
        ISystem(world),
        _moveAction(actions["Move"]),
        _click(actions["Click"]),
        
        _AStateComponent(world.GetStorage<AnimationStateComponent>()),
        _buttonsStorage(world.GetStorage<ButtonComponent>()),
        _collidersStorage(world.GetStorage<BoxColliderComponent>()),
        _posStorage(world.GetStorage<PositionComponent>())
    {}

    void OnInit() override {}
    void OnUpdate(float dt) override;
};