#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/SpriteComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/PositionComponent.h"

class DrawSystem final : public ISystem {
private:
    ComponentStorage<SpriteComponent>& _spritesStorage;
    ComponentStorage<TextComponent>& _textsStorage;
    ComponentStorage<PositionComponent>& _posStorage;
    GameEngine& _engine;

public:
    DrawSystem(World &world, GameEngine& engine): 
        ISystem(world),
        _spritesStorage(world.GetStorage<SpriteComponent>()),
        _textsStorage(world.GetStorage<TextComponent>()),
        _posStorage(world.GetStorage<PositionComponent>()),
        _engine(engine)
    {}

    void OnInit() override { }

    void OnUpdate(float) override;
};
