#include "VideoObject.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"

VideoObject::VideoObject(String name) : AGameObject(name)
{
}

void VideoObject::initialize()
{
    std::cout << "Declared as " << this->getName() << "\n";

    if (!this->videoAudio->openFromFile("C:\\Users\\Derick\\source\\repos\\GDPARCM_Villegas\\Media\\Audio\\DownWithTheBlackParade.mp3"))
        std::cout << "Audio file not found!";
    else
    {
        this->videoAudio->setLoop(false);
        this->videoAudio->setVolume(50);
        this->videoAudio->play();
    }

    this->currentFrame = 1;

    //assign texture
    this->sprite = new sf::Sprite();
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(this->frameName + std::to_string(this->currentFrame));
    this->sprite->setTexture(*texture);
    this->setScale(1.5f, 1.5f);
}

void VideoObject::processInput(sf::Event event)
{
}

void VideoObject::update(sf::Time deltaTime)
{
    if (this->videoAudio->getStatus() == sf::SoundSource::Playing)
    {
        float frameTime = ticksPerFrame * (currentFrame - 1); // Time at which the current frame should have been shown
        float timeDiff = this->videoAudio->getPlayingOffset().asMilliseconds() - frameTime;

        if (timeDiff >= 0 && timeDiff >= ticksPerFrame)
        {
            this->currentFrame++;
            sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(this->frameName + std::to_string(this->currentFrame));
            this->sprite->setTexture(*texture);
        }
    }
    else
    {
        initialize();
    }
}