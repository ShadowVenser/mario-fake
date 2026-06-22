#include "DrawSystem.h"
#include "SFML/Graphics/Text.hpp"

void DrawSystem::OnUpdate(float)
{
    auto& camera =  
        _cameraStorage.Count() > 0 ? 
        _cameraStorage.All()[0] : 
        CameraComponent{CameraType::Default, nullptr};

    switch (camera.type) 
    {
        case CameraType::FollowX:
            _engine.Window().setView(*camera.view);
            break;
        default:
            _engine.Window().setView(_engine.Window().getDefaultView());
    }

    if (_isShown)
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
}