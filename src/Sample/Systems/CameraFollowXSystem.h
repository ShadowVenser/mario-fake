#pragma once

#include "../../GameEngine/GameEngine.h"
#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/PlayerComponent.h"
#include "../Components/CameraComponent.h"

class CameraFollowXSystem final : public ISystem {
private:
    ComponentStorage<MovementComponent>& _moveStorage;
    ComponentStorage<PositionComponent>& _posStorage;
    ComponentStorage<PlayerComponent>& _playerStorage;
    ComponentStorage<CameraComponent>& _cameraStorage;
    float _cameraV = 0.f;
    float _velocityCoef;
    float _slowDownCoef;

public:
    CameraFollowXSystem(World &world, float cameraSpeedCoef, float slowDownCoef):
        ISystem(world),
        _moveStorage(world.GetStorage<MovementComponent>()),
        _posStorage(world.GetStorage<PositionComponent>()),
        _playerStorage(world.GetStorage<PlayerComponent>()),
        _cameraStorage(world.GetStorage<CameraComponent>()),
        _velocityCoef(cameraSpeedCoef),
        _slowDownCoef(slowDownCoef)
    { }

    void OnInit() override { }

    void OnUpdate(float) override;
};
