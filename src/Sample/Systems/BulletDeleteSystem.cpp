#include "BulletDeleteSystem.h"

void BulletDeleteSystem::OnUpdate(float) {


    for (auto& collision: _collisionStorage.All())
    {
        if (!world.IsEntityAlive(collision.id1))
            continue;
        if (_bulletStorage.Has(collision.id1) && !_playerStorage.Has(collision.id2)){
            _killMeStorage.Add(collision.id1, {});
        }
    }
}