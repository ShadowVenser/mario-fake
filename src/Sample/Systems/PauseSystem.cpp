#include "PauseSystem.h"
#include <memory>
#include "SFML/Graphics/Color.hpp"

sf::Color stoc(const std::string& str)
{
    return sf::Color {static_cast<unsigned int>(std::stoul(str.substr(1), nullptr, 16))};
}

void PauseSystem::OnInit()
{
    const auto& wSize = _engine.Window().getSize();

    json pauseConfig = _engine.Cfg().cfg["Scenes"]["Game"]["Pause"];
    

    _screenFilter = std::make_shared<sf::RectangleShape>(sf::Vector2f{wSize});
    
    auto color = pauseConfig.value("Color", "#FFFFFFFF");
    _screenFilter->setOrigin({
        wSize.x / 2.f, wSize.y / 2.f
    });
    _screenFilter->setFillColor(stoc(color));

    json textConfig = pauseConfig["Text"];

    _pauseText = std::make_shared<sf::Text>(
        *_engine.Assets().GetFont(textConfig["Font"].get<std::string>()),
        textConfig["Text"].get<std::string>(),
        textConfig["Size"].get<unsigned int>()
    );

    _pauseText->setOrigin(
        _pauseText->getLocalBounds().getCenter()
    );

    color = textConfig.value("color", "#FFFFFFFF");
    _pauseText->setFillColor(stoc(color));
}

void PauseSystem::OnUpdate(float)
{
    if (_onPause)
    {
        const auto& offset = _engine.Window().getView().getCenter();

        _screenFilter->setPosition(offset);
        _pauseText->setPosition(offset);

        _engine.Window().draw(*_screenFilter);
        _engine.Window().draw(*_pauseText);
    }
}