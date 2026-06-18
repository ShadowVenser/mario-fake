#include "Animation.h"
#include <utility>

#include "../GameEngineConfiguration.h"


Animation::Animation
(
    const sf::Texture& texture, 
    const size_t frameCount, 
    const size_t frameDuration, 
    const sf::Vector2i& offset = {0, 0}
):
    _texture(texture), 
    _frameCount(frameCount), 
    _frameDuration(static_cast<float>(frameDuration) / static_cast<float>(GameEngineConfiguration::framerate)), 
    _size(texture.getSize()),
    _offset(offset)
{ }

Animation::Animation(const Animation& other):
    _texture(other._texture), 
    _frameCount(other._frameCount), 
    _frameDuration(other._frameDuration), 
    _size(other._size)
{ }

Animation::Animation(Animation&& other):
    _texture(std::move(other._texture)),
    _frameCount(other._frameCount),
    _frameDuration(other._frameDuration),
    _size(std::move(other._size))
{ 
    _frameCount = 0;
    _frameDuration = 0.f;
}