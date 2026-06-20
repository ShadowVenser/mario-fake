#include "MoveInputSystem.h"

void MoveInputSystem::OnUpdate(float) {

    if (_playerStorage.Count() == 0) return;


    MovementComponent* move;
    BaseSpeedComponent* baseSpeed;

    for (auto& id: _playerStorage.Entities())
    {
        if (!world.IsEntityAlive(id))
            continue;
        move = &_moveStorage[id];
        baseSpeed = &_baseSpeedStorage[id];
        break;
    }

    float xDir = 0.f;
    float yDir = 0.f;
    bool onGround = move->ySpeed == 0.f; // тупо + так не работают рампы, но а нам не пофиг ли?

    if (_inputMap["Jump"]->Type()==ActionType::Start) {
        yDir += onGround? -1.f : 0.f;
    }
    if (_inputMap["Left"]->Type()==ActionType::Pressed) {
        xDir -= 1.f;
    }
    if (_inputMap["Right"]->Type()==ActionType::Pressed) {
        xDir += 1.f;
    }

    
    // домножение на gridsize вшито в базовые скорости в gameInit

    move->xSpeed = baseSpeed->moveSpeed * xDir;
    move->ySpeed = baseSpeed->jumpInitial * yDir;      // -, потому что на самом деле вверх = в минус
}