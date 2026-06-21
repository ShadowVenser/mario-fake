#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <string>
#include <unordered_map>

#include "SFML/Graphics/Font.hpp"

#include "Animation.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Audio.hpp>

class AssetManager {
    std::unordered_map<std::string, sf::Texture> _textures;

    std::unordered_map<std::string, Animation> _animations;
    
    std::unordered_map<std::string, sf::Font> _fonts;
    
    std::unordered_map<std::string, sf::SoundBuffer> _sounds;
    
    std::unordered_map<std::string, sf::Music> _music;

    sf::SoundBuffer emptySoundBuffer = {};

public:

    bool LoadFromFile(const std::string& path);

    bool AddTexture(const std::string& name, const std::string& path);
    bool AddAnimation
    (
        const std::string& name, 
        const std::string& textureName, 
        size_t frameCount, 
        size_t frameDuration, 
        const sf::Vector2i& size,
        const sf::Vector2i& offset, 
        const std::string& path
    );
    bool AddFont(const std::string& name, const std::string& path);

    bool AddSound(const std::string& name, const std::string& path);
    bool AddMusic(const std::string& name, const std::string& path);


    const sf::Texture* GetTexture(const std::string& name) const;
    const Animation* GetAnimation(const std::string& name) const;
    const sf::Font* GetFont(const std::string& name) const;
    const sf::Sound GetSound(const std::string& name) const;
    const sf::Music* GetMusic(const std::string& name) const;

    const std::unordered_map<std::string, sf::Texture>& GetTextures() const { return _textures; }
    const std::unordered_map<std::string, Animation>& GetAnimations() const { return _animations; }
    const std::unordered_map<std::string, sf::SoundBuffer>& GetSounds() const { return _sounds; }
};

#endif //ASSETMANAGER_H
