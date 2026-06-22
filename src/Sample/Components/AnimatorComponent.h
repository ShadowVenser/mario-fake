#pragma once 

#include <memory>
#include <unordered_map>

#include "AnimationStateComponent.h"
#include "../../GameEngine/Assets/Animation.h"

struct AnimatorComponent
{
    using AMap = std::unordered_map<AnimationNode, const Animation*>;
    std::shared_ptr<AMap> animations;
};