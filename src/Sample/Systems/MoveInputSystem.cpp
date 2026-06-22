#include "MoveInputSystem.h"

void MoveInputSystem::OnUpdate(float) {

    if (_playerStorage.Count() == 0) return;


    MovementComponent* move;
    BaseSpeedComponent* baseSpeed;
    PlayerComponent* player;

    for (auto& id: _playerStorage.Entities())
    {
        if (!world.IsEntityAlive(id))
            continue;
        move = &_moveStorage[id];
        baseSpeed = &_baseSpeedStorage[id];
        player = &_playerStorage[id];
        break;
    }

    float xDir = 0.f;
    float yDir = 0.f;

    // if (move->ySpeed < 1.f && move->ySpeed > -1.f)
    // {
    //     player->events |= PlayerComponent::CAN_JUMP;
    // } 
    // else 
    // {
    //     player->events &= ~PlayerComponent::CAN_JUMP;
    // }

    // if (_inputMap["Jump"]->Type()==ActionType::Start) {
    if (player->events & PlayerComponent::JUMP_EVENT) {
        yDir += -1.f;
        player->events &= ~PlayerComponent::JUMP_EVENT;
        player->events &= ~PlayerComponent::CAN_JUMP;
    }
    if (player->events & PlayerComponent::CAN_MOVE)
    {
        if (_inputMap["Left"]->Type()==ActionType::Pressed) {
            xDir -= 1.f;
        }
        if (_inputMap["Right"]->Type()==ActionType::Pressed) {
            xDir += 1.f;
        }
    }
    
    // домножение на gridsize вшито в базовые скорости в gameInit

    move->xSpeed = baseSpeed->moveSpeed * xDir;
    move->ySpeed += baseSpeed->jumpInitial * yDir;     
}