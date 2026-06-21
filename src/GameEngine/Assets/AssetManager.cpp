#include "AssetManager.h"
#include "SFML/Graphics/Font.hpp"
#include "nlohmann/json.hpp"

#include "SFML/System/Vector2.hpp"
#include <cstddef>
#include <fstream>

#define NONE_PATH "None path"

bool AssetManager::LoadFromFile(const std::string &path)
{
    using json = nlohmann::json;
    using namespace nlohmann::literals;

    std::ifstream acFile(path);
    if (!acFile.is_open())
        return false;

    json aInfo = json::parse(acFile); 

    if (aInfo.contains("Textures"))
    {
        for (const auto& textureInfo: aInfo["Textures"])
        {
            AddTexture
            (
                textureInfo.at("name").get<std::string>(),
                textureInfo.at("path").get<std::string>()
            );
        }
    }

    if (aInfo.contains("Animations"))
    {
        for (const auto& animationInfo: aInfo["Animations"])
        {
            AddAnimation
            (
                animationInfo.at("name").get<std::string>(),
                animationInfo.at("textureName").get<std::string>(),
                animationInfo.at("frameCount").get<size_t>(),
                animationInfo.at("frameDuration").get<size_t>(),
                {
                    animationInfo.value("/size/x"_json_pointer, 0),
                    animationInfo.value("/size/y"_json_pointer, 0)
                },
                {
                    animationInfo.value("/offset/x"_json_pointer, 0),
                    animationInfo.value("/offset/y"_json_pointer, 0)
                },
                animationInfo.value("path", NONE_PATH)
            );
        }
    }

    if (aInfo.contains("Fonts"))
    {
        for (const auto& fontInfo: aInfo["Fonts"])
        {
            AddFont
            (
                fontInfo.at("name").get<std::string>(),
                fontInfo.at("path").get<std::string>()
            );
        }
    }

    
    if (aInfo.contains("SoundEffects"))
    {
        for (const auto& SoundInfo: aInfo["SoundEffects"])
        {
            AddSound
            (
                SoundInfo.at("name").get<std::string>(),
                SoundInfo.at("path").get<std::string>()
            );
        }
    }

    if (aInfo.contains("Music"))
    {
        for (const auto& MusicInfo: aInfo["SoundEffects"])
        {
            AddSound
            (
                MusicInfo.at("name").get<std::string>(),
                MusicInfo.at("path").get<std::string>()
            );
        }
    }

    return true;
}


bool AssetManager::AddTexture
(
    const std::string &name, 
    const std::string &path
)
{
    if (auto it = _textures.find(name); it != _textures.end())
    {
        return false;
    }

    _textures.insert({
        name, sf::Texture(path)
    });

    return true;
}

bool AssetManager::AddAnimation
(
    const std::string &name, 
    const std::string &textureName, 
    const size_t frameCount,
    const size_t frameDuration,
    const sf::Vector2i& size, 
    const sf::Vector2i& offset = {0, 0},
    const std::string& path = NONE_PATH
)
{
    if (auto nameTest = _animations.find(name); nameTest != _animations.end())
        return false;

    auto it = _textures.find(textureName);
    if (it == _textures.end())
    {
        if (path == NONE_PATH)
        {
            return false;
        }
        else if (!AddTexture(textureName, path))
        {
            return false;
        }
        else 
        {
            it = _textures.find(textureName);
        }
    }

    _animations.insert({
        name, 
        {
            it->second,
            frameCount,
            frameDuration,
            size,
            offset
        }
    });

    return true;
}

bool AssetManager::AddFont
(
    const std::string &name, 
    const std::string &path
)
{
    if (auto it = _fonts.find(name); it != _fonts.end())
        return false;

    _fonts.insert
    ({
        name,
        sf::Font(path)
    });

    return true;
}


bool AssetManager::AddSound
(
    const std::string &name, 
    const std::string &path
)
{
    if (auto it = _sounds.find(name); it != _sounds.end())
    {
        return false;
    }
    _sounds.insert({name, sf::SoundBuffer(path)});

    return true;
}

bool AssetManager::AddMusic
(
    const std::string &name, 
    const std::string &path
)
{
    if (auto it = _music.find(name); it != _music.end())
    {
        return false;
    }
    
    _music.insert({name, sf::Music(path)});

    return true;
}

const sf::Texture* AssetManager::GetTexture(const std::string &name) const
{
    if (auto it = _textures.find(name); it != _textures.end())
        return &it->second;
    return nullptr;
}

const Animation* AssetManager::GetAnimation(const std::string &name) const
{
    if (auto it = _animations.find(name); it != _animations.end())
        return &it->second;
    return nullptr;
}

const sf::Font* AssetManager::GetFont(const std::string &name) const
{
    if (auto it = _fonts.find(name); it != _fonts.end())
        return &it->second;
    return nullptr;
}

const sf::Sound AssetManager::GetSound(const std::string &name) const
{
    if (auto it = _sounds.find(name); it != _sounds.end())
        return sf::Sound(it->second);
    return sf::Sound(emptySoundBuffer);
}

const sf::Music* AssetManager::GetMusic(const std::string &name) const
{
    if (auto it = _music.find(name); it != _music.end())
        return &it->second;
    return nullptr;
}




