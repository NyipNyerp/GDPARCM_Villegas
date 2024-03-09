#pragma once
#include "AGameObject.h"
#include <SFML/Audio.hpp>

class VideoObject : public AGameObject
{
public:

    VideoObject(String name);
    void initialize();
    void processInput(sf::Event event);
    void update(sf::Time deltaTime);

private:
    std::string frameName = "Frame";
    sf::Music* videoAudio = new sf::Music();

    int currentFrame = 1;
    float ticksPerFrame = 100;
};