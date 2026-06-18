#include <SFML/Graphics.hpp>
#include <memory>
#include "GameEngine/GameEngine.h"
#include "GameEngine/GameEngineConfiguration.h"
#include "Sample/Scenes/MenuScene.h"

int main() {
    // Пример использования
    setlocale(LC_ALL, "");

    // GameEngineConfiguration cfg;

    GameEngine engine(GameEngineConfiguration{});

    engine.ChangeScene<MenuScene>(engine);

    engine.Run();

    return 0;
}