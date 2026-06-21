#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/BoxColliderComponent.h"
#include "../Components/PositionComponent.h"

class ShowCollidersSystem final : public ISystem {
private:
    ComponentStorage<BoxColliderComponent>& _bboxStorage;
    ComponentStorage<PositionComponent>& _posStorage;
    GameEngine& _engine;
    bool _isShown = true;
    int tileSize;

public:
    ShowCollidersSystem(World &world, GameEngine& engine): 
        ISystem(world),
        _bboxStorage(world.GetStorage<BoxColliderComponent>()),
        _posStorage(world.GetStorage<PositionComponent>()),
        _engine(engine)
    {
        tileSize = _engine.Cfg().cfg["Scenes"]["Game"]["Grid"]["TileSize"].get<int>();
    }

    void OnInit() override {
    }

    void OnUpdate(float) override;
};
