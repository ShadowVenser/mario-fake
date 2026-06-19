#ifndef ANIMATION_H
#define ANIMATION_H

#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

class Animation {
    const sf::Texture& _texture;

    size_t _frameCount;

    // here frame duration in dT
    float _frameDuration;

    sf::Vector2i _size;
    sf::Vector2i _offset;

public:
    // here frame duration in game frames
    Animation
    (
        const sf::Texture& texture, 
        const size_t frameCount, 
        const size_t frameDuration,
        const sf::Vector2i& size,  
        const sf::Vector2i& offset
    );

    Animation(const Animation& other);

    Animation(Animation&& other);

    const sf::Texture& GetTexture() const { return _texture; }
    size_t FrameCount() const { return _frameCount; }
    float FrameDuration() const { return _frameDuration; }
    const sf::Vector2i& Size() const { return _size; }
    const sf::Vector2i& Offset() const { return _offset; }
};

#endif //ANIMATION_H
