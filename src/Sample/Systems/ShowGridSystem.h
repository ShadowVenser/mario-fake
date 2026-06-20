#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/CameraComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/TextComponent.h"

class ShowGridSystem final : public ISystem {
private:
    ComponentStorage<CameraComponent>& _cameraStorage;
    GameEngine& _engine;
    bool _isShown = true;

    void DrawLine(const sf::Vector2f &p1, const sf::Vector2f &p2);

public:
    ShowGridSystem(World &world, GameEngine& engine): 
        ISystem(world),
        _cameraStorage(world.GetStorage<CameraComponent>()),
        _engine(engine)
    {}

    void OnInit() override { }

    void OnUpdate(float) override;
};
