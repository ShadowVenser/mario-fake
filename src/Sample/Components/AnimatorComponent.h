#pragma once 

#include <memory>
#include <unordered_map>

#include "AnimationStateComponent.h"
#include "../../GameEngine/Assets/Animation.h"

struct AnimatorComponent
{
    std::shared_ptr<std::unordered_map<AnimationNode, Animation&>> animations;
};