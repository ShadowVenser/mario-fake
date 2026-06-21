#include "OutOfBoundsSystem.h"

void OutOfBoundsSystem::OnUpdate(float) {

    if (_playerStorage.Count() == 0)
        return;

    for (auto& id: _playerStorage.Entities())
    {
        if (!world.IsEntityAlive(id))
            continue;
        auto& pos = _posStorage[id];
        if (pos.pos.y > _windowHeight*1.5f){
            _killMeStorage.Add(id, {});
        }
        break;
    }
}