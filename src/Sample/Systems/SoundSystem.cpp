#include "SoundSystem.h"


void SoundSystem::OnUpdate(float)
{
    for (auto& event : _eventStorage.All()){
        std::shared_ptr<sf::Sound> ptr = std::make_shared<sf::Sound>(*_assets.GetSound(event.soundType));
        ptr->play();
        _activeSounds.insert(ptr);
    }
    for (auto it = _activeSounds.begin(); it != _activeSounds.end(); ) {
        auto s = *it;
        if (!s || s->getStatus() == sf::SoundSource::Status::Stopped) {
            it = _activeSounds.erase(it); 
        } else {
            ++it;
        }
    }
}
