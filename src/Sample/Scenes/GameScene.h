#pragma once

#include "../../GameEngine/Scene.h"

class GameScene final: public Scene 
{
private:

public:
    GameScene(GameEngine& engine);

    void Init() override;
    void Update(float delta) override;
};