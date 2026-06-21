#include "AdditionalControlSystem.h"

#include "../Scenes/MenuScene.h"

void AdditionalControlSystem::OnUpdate(float) {

    if (_inputMap["Menu"]->Type()==ActionType::Start) {
        _engine.ChangeScene<MenuScene>(_engine);
    }
    if (_inputMap["Pause"]->Type()==ActionType::Start) {
        // можно в теории прокинуть вообще везде, ИЛИ запихать внутрь движка; первый вариант долго и в самом конце, второй вариант говно
    }
}