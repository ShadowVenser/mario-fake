#pragma once

#include "SFML/System/Vector2.hpp"

struct MovementComponent
{
    float xSpeed = 0.f;        //текущая скорость; если потребуется скорость безотносительно направления, просто вычисли; и да, нахер ваши вектора, так удобнее
    float ySpeed = 0.f;
};
