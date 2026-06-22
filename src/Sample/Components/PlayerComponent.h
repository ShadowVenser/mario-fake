#pragma once

#include <cstdint>

struct PlayerComponent
{
    static const uint8_t JUMP_EVENT = 0b0000'0001;
    static const uint8_t SHOOT_EVENT = 0b0000'0010;
    static const uint8_t CAN_SHOOT = 0b0000'0100;
    static const uint8_t CAN_JUMP = 0b0000'1000;
    static const uint8_t CAN_MOVE = 0b0001'0000;

    int score = 0;
    float time = 0.0f;

    uint8_t events = 0b0001'1100;
};