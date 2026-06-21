#include "ShowCollidersSystem.h"
#include "SFML/Graphics/Text.hpp"


#include <cmath>

void ShowCollidersSystem::OnUpdate(float)
{
    if (!_isShown) return;
    for (auto e : _bboxStorage.Entities()){
        auto& bbox = _bboxStorage.Get(e);
        auto& transform = _posStorage.Get(e);
        sf::RectangleShape rect;


        
        float offsetX = static_cast<float>((bbox.w>tileSize)? tileSize : bbox.w) / 2.f;
        float offsetY = static_cast<float>(bbox.h * 2 - ((bbox.h>tileSize)? tileSize : bbox.h)) / 2.f;

        rect.setSize(sf::Vector2f(bbox.w - 1.f, bbox.h - 1.f));
        rect.setOrigin(sf::Vector2f(offsetX, offsetY));
        rect.setPosition({transform.pos.x, transform.pos.y});
        rect.setFillColor(sf::Color(0, 0, 0, 0));
        rect.setOutlineColor(sf::Color::Green);
        rect.setOutlineThickness(1);
        _engine.Window().draw(rect);
    }

}