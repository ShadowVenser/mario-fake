#ifndef INPUTACTION_H
#define INPUTACTION_H

#include <SFML/System.hpp>
#include <string>

enum class ActionType { None, Start, End, Pressed, Moved };

class InputAction
{
    std::string _name = "None";
    ActionType _type = ActionType::None;

    // _value and _vector are only meaningful for event types that use them;
    // otherwise they may contain indeterminate data.

    float _value = -1.f;
    sf::Vector2i _vector = {-1, -1};

public:
    InputAction() = default;
    InputAction(const std::string& name) : _name(name) {}

    const std::string& Name() const { return _name; }
    ActionType& Type() { return _type; }
    float& Value() { return _value; }
    sf::Vector2i& Vector() { return _vector; }
};

#endif //INPUTACTION_H
