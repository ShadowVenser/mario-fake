#include "RespawnSystem.h"

#include "../Scenes/GameScene.h"

void RespawnSystem::OnUpdate(float) {

    bool died = _playerStorage.Count() == 0;

    if (!died){
        for (auto& id: _playerStorage.Entities())
        {
            if (!world.IsEntityAlive(id))
                continue;
            if (_killMeStorage.Has(id))
                died = true;
            break;
        }
    }
    if(died){
        _engine.LoadScene<GameScene>(_engine);
    }
}