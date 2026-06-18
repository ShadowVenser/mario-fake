#pragma once

#include <memory>
#include "SFML/Graphics/Sprite.hpp"

struct SpriteComponent
{
    std::shared_ptr<sf::Sprite> sprite;
};