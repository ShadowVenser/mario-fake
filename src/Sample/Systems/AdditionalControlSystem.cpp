#include "AdditionalControlSystem.h"

#include "../Scenes/MenuScene.h"

void AdditionalControlSystem::OnUpdate(float dt) {

    if (_inputMap["Menu"]->Type()==ActionType::Start) 
    {
        _engine.LoadScene<MenuScene>(_engine);               // сменить ChangeScene на LoadScene, если прям нужно кинуть игрока в начало после возвращения
    }
    if (!_onCooldown)
    {
        if (_inputMap["Pause"]->Type()==ActionType::Start) 
        {
            _onPause = !_onPause;
            _onCooldown = true;
            timer = 0.f;
        }
    }
    else
    {
        timer += dt;
        if (_pauseCooldown < timer)
        {
            _onCooldown = false;
        }
    }
}