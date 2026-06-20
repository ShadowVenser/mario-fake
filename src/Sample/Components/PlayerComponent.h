#pragma once

struct PlayerComponent
{
    int score = 0;
    float time = 0.0f;
    float jumpInitialSpeed;   // Прыгать могут только объекты с подобием интеллекта, так что оно будет вот тут + в ии-компоненте (тебе не надо)
};