#include "sfxCollisionSystem.h"

void sfxCollisionSystem::OnUpdate(float) {

    for (auto& ids: _collisionStorage.All())
    {
        if (!_finishStorage.Has(ids.id2)){
            int e = world.CreateEntity();
            _soundStorage.Add(e, {_boomSound});
            _killMeStorage.Add(e, {});
        }
    }
}