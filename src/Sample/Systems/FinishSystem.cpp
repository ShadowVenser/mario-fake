#include "FinishSystem.h"

#include "../Scenes/MenuScene.h"

void FinishSystem::OnUpdate(float) {

    for (auto& collision: _collisionStorage.All())
    {
        if (!world.IsEntityAlive(collision.id1) || !world.IsEntityAlive(collision.id2))
            continue;
        if (_playerStorage.Has(collision.id1) && _finishStorage.Has(collision.id2)){
            _engine.ChangeScene<MenuScene>(_engine);
        }
    }
}