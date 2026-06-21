#include "ShowGridSystem.h"
#include "SFML/Graphics/Text.hpp"


#include <cmath>

// Функция для отрисовки линии. Можно сделать приватным методов в системе отрисовки
void ShowGridSystem::DrawLine(const sf::Vector2f &p1, const sf::Vector2f &p2) {
    sf::Vertex line[] = {
        sf::Vertex(p1),
        sf::Vertex(p2)
    };

    _engine.Window().draw(line, 2, sf::PrimitiveType::Lines);
}   

void ShowGridSystem::OnUpdate(float)
{
    if (!_isShown) return;

    sf::Text gridText (*_engine.Assets().GetFont(_font));    
    gridText.setCharacterSize(_textSize);
   
    float gridSize = static_cast<float>(size1d);
    float leftX = float(_engine.Window().getView().getCenter().x) - _engine.Window().getSize().x / 2.0f;
    float rightX = leftX + _engine.Window().getSize().x + gridSize;
    float nextGridX = leftX - float((int) leftX % size1d);

    for (float x = nextGridX; x < rightX; x += gridSize)
    {
        DrawLine({x, 0}, {x, float(_engine.Window().getSize().y)});
    }

    for (float y = 0; y < _engine.Window().getSize().y; y += gridSize)
    {
        DrawLine({leftX, _engine.Window().getSize().y - y}, {rightX, _engine.Window().getSize().y - y});

        for (float x = nextGridX - 1.f; x < rightX; x += gridSize)
        {
            std::string xCell = std::to_string((int)std::ceil(x / gridSize));
            std::string yCell = std::to_string((int)std::ceil(y / gridSize));
            gridText.setString("(" + xCell + "," + yCell + ")");
            gridText.setPosition({x + 3, _engine.Window().getSize().y - y - gridSize + 2});
            _engine.Window().draw(gridText);
        }
    }


}