#ifndef GAMEENGINECONF_H
#define GAMEENGINECONF_H

#include <string>
#include <cstdint>

// ToDo: Ваш аналог конфига, который читается из файла
class GameEngineConfiguration
{
public:
    static constexpr unsigned int Width = 1280;
    static constexpr unsigned int Height = 768;

    static constexpr uint16_t framerate = 60;

    static constexpr std::string AssetsPath = "Assets/";
    static constexpr std::string AssetsFile = "assets.json";
};

#endif //GAMEENGINECONF_H
