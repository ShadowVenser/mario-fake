#pragma once 

enum class AnimationGraph { Button };
enum class AnimationNode { Idle, Pressed, Choosed };

struct AnimationStateComponent
{
    AnimationGraph graph;
    
    AnimationNode currentState;
    AnimationNode nextState;

    int currentFrame;
    float timer;
};