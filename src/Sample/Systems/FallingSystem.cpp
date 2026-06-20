#include "FallingSystem.h"

void FallingSystem::OnUpdate(float t) {

    for (auto& id: _gravStorage.Entities())
    {
        if (!world.IsEntityAlive(id))
            continue;
        auto& move = _moveStorage[id];
        auto grav = _gravStorage[id].g;
        
        move.ySpeed += grav * t;
    }
}