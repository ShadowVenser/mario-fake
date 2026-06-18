#ifndef GAMEENGINECONF_H
#define GAMEENGINECONF_H

#include "nlohmann/json.hpp"

#include <fstream>
#include <string_view>
#include <cstdint>

// ToDo: Ваш аналог конфига, который читается из файла
class GameEngineConfiguration
{
    using json = nlohmann::json;
public:
    static constexpr unsigned int Width = 832;
    static constexpr unsigned int Height = 576;

    static constexpr uint16_t framerate = 60;

    static constexpr std::string_view AssetsFile = "assets/AssetConfig.json";
    static constexpr std::string_view ConfigFile = "config.json";

    json cfg;

    GameEngineConfiguration()
    {
        std::ifstream f(std::string{ConfigFile.cbegin(), ConfigFile.cend()});
        if (f.is_open())
            cfg = json::parse(f);
    }
};

#endif //GAMEENGINECONF_H
