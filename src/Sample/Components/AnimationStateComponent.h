#pragma once 

#include <cstddef>

enum class AnimationNode 
{ 
    Idle, Pressed, Choosed, Activated, None,
    JumpGU, JumpAU, JumpAS, JumpAD, JumpGD, 
    Shoot, DeadAS, DeadAD, DeadGD, Move
};

struct AnimationStateComponent
{
    AnimationNode currentState;
    AnimationNode nextState;

    bool isCycled;

    size_t currentFrame;
    float timer;

    bool isFinal = false;
    bool isReflected = false;
};