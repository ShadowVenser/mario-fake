#pragma once

#include "../../GameEngine/Scene.h"

class MenuScene final: public Scene 
{
private:
    bool _visible = true;
public:
    MenuScene(GameEngine& engine);

    void Init() override;
    void Update(float delta) override;
};