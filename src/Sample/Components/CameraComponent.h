#pragma once

#include <memory>
#include "SFML/Graphics/View.hpp"

enum class CameraType { Default, FollowX };

struct CameraComponent
{
    CameraType type;
    std::shared_ptr<sf::View> view;
};
