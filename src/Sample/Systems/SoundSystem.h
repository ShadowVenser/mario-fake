#pragma once
#include <memory>
#include "../../Ecs/Systems/ISystem.h"

#include "../../Ecs/Components/ComponentStorage.hpp"
#include <SFML/Audio.hpp>

#include "../Components/SoundEventComponent.h"

class SoundSystem final : public ISystem {
    ComponentStorage<SoundEventComponent>& _eventStorage;
    const std::unordered_map<std::string, sf::SoundBuffer>& _sounds;
    std::unordered_set<std::shared_ptr<sf::Sound>> _activeSounds = {};
    sf::Music& _music;

public:
    SoundSystem(World &world, const std::unordered_map<std::string, sf::SoundBuffer>& sounds, sf::Music& music)
        : ISystem(world),
            _eventStorage(world.GetStorage<SoundEventComponent>()),
            _sounds(sounds),
            _music(music)
    {
        _music.setLooping(true);
        _music.play();
    }

    void OnInit() override;

    void OnUpdate(float) override;
};
