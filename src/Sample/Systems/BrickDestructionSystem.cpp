#include "BrickDestructionSystem.h"
#include <memory>
#include "SFML/Graphics/Sprite.hpp"

void BrickDestructionSystem::OnInit()
{ }

void BrickDestructionSystem::OnUpdate(float)
{
    for(const auto& collision: _collisionStorage.All())
    {
        if (auto e = collision.id2; _breackableStorage.Has(e) && !_animatorStorage.Has(e))
        {
            _ASStorage.Add(e, {_asTemplate});

            auto animations = std::make_shared<AnimatorComponent::AMap>();
            animations->insert({AnimationNode::Idle, _breakAnimation});
            _animatorStorage.Add(e, {animations});

            auto& sprite = _spriteStorage.Get(e);
            const auto& origin = sprite.sprite->getOrigin();
            const auto& size = sprite.sprite->getTextureRect();

            sprite.sprite = std::make_shared<sf::Sprite>(_breakAnimation->GetTexture());
            sprite.sprite->setOrigin(origin);
            sprite.sprite->setTextureRect(size);
        }
    }

    for (auto e: _breakableOnDelete->GetView())
    {
        auto& aState = _ASStorage.Get(e);
        if (aState.isFinal)
        {
            _suicideStorage.Add(e, { });
        }
    }
}