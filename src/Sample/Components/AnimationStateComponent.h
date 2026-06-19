#pragma once 

#include <cstddef>

enum class AnimationNode { Idle, Pressed, Choosed, Activated, None };

struct AnimationStateComponent
{
    AnimationNode currentState;
    AnimationNode nextState;

    bool isCycled;

    size_t currentFrame;
    float timer;

    bool isFinal;

};