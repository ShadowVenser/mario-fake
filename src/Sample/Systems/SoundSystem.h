#pragma once
#include <memory>
#include "../../Ecs/Systems/ISystem.h"

#include "../../Ecs/Components/ComponentStorage.hpp"

#include "../../GameEngine/Assets/AssetManager.h"
#include "../Components/SoundEventComponent.h"

class SoundSystem final : public ISystem {
    ComponentStorage<SoundEventComponent>& _eventStorage;
    std::unordered_set<std::shared_ptr<sf::Sound>> _activeSounds = {};
    std::shared_ptr<sf::Music> _music;
    const AssetManager& _assets;

public:
    SoundSystem(World &world, const AssetManager& assets, std::string music)
        : ISystem(world),
            _eventStorage(world.GetStorage<SoundEventComponent>()),
            _assets(assets)
    {
        if (assets.GetMusic(music) != 0){
            _music = std::make_shared<sf::Music>(*assets.GetMusic(music));
            _music->setLooping(true);
            _music->play();
        }
    }

    void OnInit() override {}

    void OnUpdate(float) override;
};
