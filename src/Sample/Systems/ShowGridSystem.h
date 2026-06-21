#pragma once

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "../Components/PositionComponent.h"
#include "../Components/TextComponent.h"

class ShowGridSystem final : public ISystem {
private:
    GameEngine& _engine;
    bool _isShown = false;
    std::string _font = "";
    unsigned int _textSize = 10;
    int size1d;

    void DrawLine(const sf::Vector2f &p1, const sf::Vector2f &p2);

public:
    ShowGridSystem(World &world, GameEngine& engine): 
        ISystem(world),
        _engine(engine)
    {
        _font = _engine.Cfg().cfg["Scenes"]["Game"]["Grid"]["Text"]["Font"].get<std::string>(); 
        _textSize = _engine.Cfg().cfg["Scenes"]["Game"]["Grid"]["Text"]["Size"].get<unsigned int>();
        size1d = _engine.Cfg().cfg["Scenes"]["Game"]["Grid"]["TileSize"].get<int>();
    }

    void OnInit() override {
    }

    void OnUpdate(float) override;
};
