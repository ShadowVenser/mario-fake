#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/IInitializer.h"

class GameInitSystem final: public IInitializer
{
private:
    GameEngine& _engine;
public:
    GameInitSystem(World& world, GameEngine& engine): IInitializer(world), _engine(engine) {}

    void OnInit() override;
};