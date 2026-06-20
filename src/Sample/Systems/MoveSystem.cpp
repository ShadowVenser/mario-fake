#include "MoveSystem.h"

void MoveSystem::OnUpdate(float t) {

    for (auto& id: _moveStorage.Entities())
    {
        if (!world.IsEntityAlive(id))
            continue;
        auto& move = _moveStorage[id];
        auto& pos = _posStorage[id];
        
        pos.pos.x += move.xSpeed * t;
        pos.pos.y += move.ySpeed * t; // TODO въебать коллизии
    }
}