#include "CameraFollowXSystem.h"

void CameraFollowXSystem::OnUpdate(float t) {
    if (_playerStorage.Count()==0 || _cameraStorage.Count()==0)
        return;
    if (_cameraStorage.All()[0].type != CameraType::FollowX)
        return;

    for (auto& plId: _playerStorage.Entities())
    {
        if (!world.IsEntityAlive(plId))
            continue;

        float targetPosX = _posStorage[plId].pos.x + _moveStorage[plId].xSpeed;

        auto& cameraView = *_cameraStorage.All()[0].view;        
        float cameraPosX = cameraView.getCenter().x;
        _cameraV *= _slowDownCoef;
        _cameraV += (targetPosX-cameraPosX)*t*_velocityCoef;
        cameraView.move({_cameraV*t, 0.f});

        break;
    }
}