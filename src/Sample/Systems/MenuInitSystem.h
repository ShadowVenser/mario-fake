#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/IInitializer.h"

class MenuInitSystem final: public IInitializer
{
private:
    GameEngine& _engine;
public:
    MenuInitSystem(World& world, GameEngine& engine): IInitializer(world), _engine(engine) {}

    void OnInit() override;
};