#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/CameraComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TextComponent.h"

class DrawSystem final : public ISystem {
private:
    ComponentStorage<CameraComponent>& _cameraStorage;
    ComponentStorage<PositionComponent>& _posStorage;
    ComponentStorage<SpriteComponent>& _spritesStorage;
    ComponentStorage<TextComponent>& _textsStorage;
    GameEngine& _engine;

public:
    DrawSystem(World &world, GameEngine& engine): 
        ISystem(world),
        _cameraStorage(world.GetStorage<CameraComponent>()),
        _posStorage(world.GetStorage<PositionComponent>()),
        _spritesStorage(world.GetStorage<SpriteComponent>()),
        _textsStorage(world.GetStorage<TextComponent>()),
        _engine(engine)
    {}

    void OnInit() override { }

    void OnUpdate(float) override;
};
