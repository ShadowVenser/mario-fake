#include "MoveSystem.h"

void MoveSystem::OnUpdate(float t) {

    for (auto& id: _moveStorage.Entities())
    {
        if (!world.IsEntityAlive(id))
            continue;
        auto& move = _moveStorage[id];
        auto& pos = _posStorage[id];
        
        move.xSpeed = (move.maxSpeed<move.xSpeed)? move.maxSpeed : move.xSpeed;
        move.xSpeed = (move.xSpeed<-move.maxSpeed)? -move.maxSpeed : move.xSpeed;
        move.ySpeed = (move.maxSpeed<move.ySpeed)? move.maxSpeed : move.ySpeed;
        move.ySpeed = (move.ySpeed<-move.maxSpeed)? -move.maxSpeed : move.ySpeed;

        pos.pos.x += move.xSpeed * t;
        pos.pos.y += move.ySpeed * t;
    }
}