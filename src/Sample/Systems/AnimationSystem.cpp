#include "AnimationSystem.h"

void AnimationSystem::OnUpdate(float dt)
{
    for (auto e: _AStateStorage.Entities())
    {
        if (world.IsEntityAlive(e))
        {
            auto& aState = _AStateStorage.Get(e);
            auto& animation = (*_animationsStorage.Get(e).animations)[aState.currentState];
            auto& sprite = _spritesStorage.Get(e);

            sprite.sprite->setTexture(animation->GetTexture());

            aState.timer += dt;
            if (aState.timer > animation->FrameDuration() && !aState.isFinal)
            {
                if (!aState.isCycled && (aState.currentFrame == (animation->FrameCount() - 1)))
                {
                    aState.isFinal = true;
                }
                else 
                {
                    aState.currentFrame = (aState.currentFrame + 1) % animation->FrameCount();
                    aState.timer -= animation->FrameDuration();
                }
            }

            sprite.sprite->setTextureRect
            (
                sf::IntRect{
                    {
                        animation->Offset().x + animation->Size().x * static_cast<int>(aState.currentFrame),
                        animation->Offset().y
                    },
                    {
                        animation->Size().x,
                        animation->Size().y
                    }
                }
            );
        }
    }
}