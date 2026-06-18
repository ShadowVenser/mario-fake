#include "DrawSystem.h"
#include "SFML/Graphics/Text.hpp"

void DrawSystem::OnUpdate(float)
{
    for (auto& id: _spritesStorage.Entities())
    {
        if (!world.IsEntityAlive(id))
            continue;
        auto sprite = _spritesStorage.Get(id).sprite;
        sprite->setPosition(_posStorage.Get(id).pos);
        _engine.Window().draw(*sprite);
    }

    for (auto& id: _textsStorage.Entities())
    {
        if (!world.IsEntityAlive(id))
            continue;
        auto& textProps = _textsStorage.Get(id);
        sf::Text txt {
            *_engine.Assets().GetFont(textProps.fontName),
            textProps.text,
            textProps.size
        };
        txt.setOrigin({0.5f * txt.getLocalBounds().size.x, 0.5f * txt.getLocalBounds().size.y});
        txt.setPosition(_posStorage.Get(id).pos);
        _engine.Window().draw(txt);
    }
}