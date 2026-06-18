#pragma once

#include <functional>

struct ButtonComponent
{
    std::function<void()> OnClick;
};

