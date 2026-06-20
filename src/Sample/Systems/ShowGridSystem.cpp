#include "ShowGridSystem.h"
#include "SFML/Graphics/Text.hpp"

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

    sf::Text gridText (*_engine.Assets().GetFont(
        _engine.Cfg().cfg["Scenes"]["Game"]["Grid"]["Text"]["Font"].get<std::string>()
    ));    
    gridText.setCharacterSize(        
        _engine.Cfg().cfg["Scenes"]["Game"]["Grid"]["Text"]["Size"].get<unsigned int>()
    );
    int size1d = _engine.Cfg().cfg["Scenes"]["Game"]["Grid"]["TileSize"].get<int>();

    const sf::Vector2i gridSize = {size1d, size1d};
    float leftX = float(_engine.Window().getView().getCenter().x) - _engine.Window().getSize().x / 2.0f;
    float rightX = leftX + _engine.Window().getSize().x + gridSize.x;
    float nextGridX = leftX - float((int) leftX % (int) gridSize.x);

    for (float x = nextGridX; x < rightX; x += float(gridSize.x))
    {
        DrawLine({x, 0}, {x, float(_engine.Window().getSize().y)});
    }

    for (float y = 0; y < _engine.Window().getSize().y; y += float(gridSize.y))
    {
        DrawLine({leftX, _engine.Window().getSize().y - y}, {rightX, _engine.Window().getSize().y - y});

        for (float x = nextGridX; x < rightX; x += float(gridSize.x))
        {
            std::string xCell = std::to_string((int) x / (int) gridSize.x);
            std::string yCell = std::to_string((int) y / (int) gridSize.y);
            gridText.setString("(" + xCell + "," + yCell + ")");
            gridText.setPosition({x + 3, _engine.Window().getSize().y - y - gridSize.y + 2});
            _engine.Window().draw(gridText);
        }
    }


}