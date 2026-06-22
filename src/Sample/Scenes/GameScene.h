#pragma once

#include "../../GameEngine/Scene.h"

class GameScene final: public Scene 
{
private:
    SystemsManager& basicSystemManager;

    SystemsManager pausableSystemManager;
    SystemsManager graphicsSystemManager;

    bool _onPause;
    bool _isDrawShown = true;
    bool _isGridShown = false;
    bool _isBoxShown = false;

public:
    GameScene(GameEngine& engine);

    void Init() override;
    void Update(float delta) override;
};