
#pragma once

#include <memory>

#include "nlohmann/json.hpp"

#include "../../GameEngine/GameEngine.h"

#include "../../Ecs/Systems/ISystem.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

class PauseSystem final : public ISystem {
private:
    using json = nlohmann::json;

    GameEngine& _engine;

    bool& _onPause;
    bool _prev = false;

    std::shared_ptr<sf::RectangleShape> _screenFilter;
    std::shared_ptr<sf::Text> _pauseText;

public:
    PauseSystem(World &world, GameEngine& engine, bool& onPause): 
        ISystem(world),
        _engine(engine),
        _onPause(onPause)
    { }

    void OnInit() override;

    void OnUpdate(float) override;
};
