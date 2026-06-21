#pragma once

#include "../../GameEngine/Scene.h"

class GameScene final: public Scene 
{
private:
    SystemsManager& basicSystemManager;

    SystemsManager pausableSystemManager;
    SystemsManager graphicsSystemManager;

    bool _onPause;

public:
    GameScene(GameEngine& engine);

    void Init() override;
    void Update(float delta) override;
};