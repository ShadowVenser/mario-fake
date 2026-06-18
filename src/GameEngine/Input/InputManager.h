#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <memory>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "InputAction.h"


enum MouseMove { Move };

class GameEngine;

struct SpecialInput
{
    float val;
    sf::Vector2i vec;
};

class InputManager
{
    sf::RenderWindow& _window;
    GameEngine& _gameEngine;

    std::unordered_map<size_t, std::unordered_map<sf::Keyboard::Key, std::shared_ptr<InputAction>>> _actionKeyMaps;
    std::unordered_map<size_t, std::unordered_map<sf::Mouse::Button, std::shared_ptr<InputAction>>> _actionMouseBtnMaps;
    std::unordered_map<size_t, std::unordered_map<sf::Mouse::Wheel, std::shared_ptr<InputAction>>> _actionMouseWheelMaps;
    std::unordered_map<size_t, std::unordered_map<MouseMove, std::shared_ptr<InputAction>>> _actionMouseMoveMaps;

    template<typename T>
    void _releaseActions(std::unordered_map<T, std::shared_ptr<InputAction>>& actionMap)
    {
        for (auto& action: actionMap)
        {
            if ((action.second->Type() == ActionType::End) || (action.second->Type() == ActionType::Moved))
                action.second->Type() = ActionType::None;
        }
    }

    template<typename RightTypeEvent>
    void _eventToKey(RightTypeEvent* event, sf::Keyboard::Key* key, SpecialInput*)
    {
        *key = event->code;
    }

    template<typename RightTypeEvent>
    void _eventToKey(RightTypeEvent* event, sf::Mouse::Button* key, SpecialInput* spec = nullptr)
    {
        *key = event->button;

        if (spec != nullptr)
        {
            spec->vec = event->position;
        }
    }

    template<typename RightTypeEvent>
    void _eventToKey(RightTypeEvent* event, sf::Mouse::Wheel* key, SpecialInput* spec = nullptr)
    {
        *key = event->wheel;

        if (spec != nullptr)
        {
            spec->val = event->delta;
            spec->vec = event->position;
        }
    }

    template<typename RightTypeEvent>
    void _eventToKey(RightTypeEvent* event, MouseMove* key, SpecialInput* spec = nullptr)
    {
        *key = MouseMove::Move;

        if (spec != nullptr)
        {
            spec->vec = event->position;
        }
    }

    template<typename In, typename RightEventType>
    void _processEvent
    (
        std::unordered_map<In, std::shared_ptr<InputAction>>& actionMap,
        RightEventType* event,
        ActionType aType,
        SpecialInput* spec = nullptr
    )
    {
        In key; 
        _eventToKey(event, &key, spec);
        auto it = actionMap.find(key);
        if (it != actionMap.end())
        {
            it->second->Type() = aType;
            if (spec != nullptr)
            {
                it->second->Value() = spec->val;
                it->second->Vector() = spec->vec;
            }
        }
    }

public:
    // ToDo:
    InputManager(sf::RenderWindow& window, GameEngine& gameEngine);

    void RegisterInput(size_t scene,
        sf::Keyboard::Key key, std::shared_ptr<InputAction> action);
    void RegisterInput(size_t scene,
        sf::Mouse::Button btn, std::shared_ptr<InputAction> action);
    void RegisterInput(size_t scene,
        sf::Mouse::Wheel wheel, std::shared_ptr<InputAction> action);
    void RegisterInput(size_t scene,
        MouseMove mv, std::shared_ptr<InputAction> action);

    void ProcessInput(size_t scene);
};

#endif //INPUTMANAGER_H
