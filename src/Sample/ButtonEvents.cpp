#include "ButtonEvents.h"
#include "Scenes/GameScene.h"

void quitButtonEvent(GameEngine &engine)
{
    engine.Quit();
}

void playButtonEvent(GameEngine &engine)
{
    engine.ChangeScene<GameScene>(engine);
}
