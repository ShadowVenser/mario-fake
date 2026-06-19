#include "ButtonStateSystem.h"
#include <stdexcept>

inline bool isInside(float x, float y, float bx, float by, float ex, float ey)
{
    return std::abs(ex - x) < bx / 2.f && (y - ey) < by && ey < y;
}

void ButtonStateSystem::OnUpdate(float)
{
    for (auto bId: _buttonsStorage.Entities())
    {
        auto& btn = _buttonsStorage.Get(bId);
        auto& aState = _AStateComponent.Get(bId);
        const auto& [bx, by] = _collidersStorage.Get(bId);
        const auto& [x, y] = _posStorage.Get(bId).pos;

        bool isChanged = aState.currentState != aState.nextState;

        aState.currentState = aState.nextState;
        aState.nextState = AnimationNode::None;

        switch (aState.currentState) 
        {
            case AnimationNode::Idle:
            {
                if (isChanged) 
                {
                    aState.isCycled = true;
                    aState.isFinal = false;
                }
                aState.nextState = AnimationNode::Idle;

                if (_moveAction->Type() == ActionType::Moved)
                {
                    if (isInside(x, y, bx, by, _moveAction->Vector().x, _moveAction->Vector().y))
                    {
                        aState.nextState = AnimationNode::Choosed;
                    }
                }
                break;
            }
            case AnimationNode::Choosed:
            {   
                if (isChanged) 
                {
                    aState.isCycled = true;
                    aState.isFinal = false;
                }
                aState.nextState = AnimationNode::Choosed;

                if (_moveAction->Type() == ActionType::Moved)
                {
                    if (!isInside(x, y, bx, by, _moveAction->Vector().x, _moveAction->Vector().y))
                    {
                        aState.nextState = AnimationNode::Idle;
                    }
                }

                if (_click->Type() == ActionType::Start)
                {
                    if (isInside(x, y, bx, by, _click->Vector().x, _click->Vector().y))
                    {
                        aState.nextState = AnimationNode::Activated;
                    }
                }

                break;
            }
            case AnimationNode::Activated:
            {
                if (isChanged) 
                {
                    aState.isCycled = false;
                    aState.isFinal = false;
                    aState.timer = 0;
                    aState.currentFrame = 0;
                }

                aState.nextState = AnimationNode::Activated;


                if (aState.isFinal)
                {
                    aState.nextState = AnimationNode::Idle;
                    btn.OnClick();
                }

                break;
            }
            default:
                throw std::runtime_error("Unknown state!!!");
        }
    }
}