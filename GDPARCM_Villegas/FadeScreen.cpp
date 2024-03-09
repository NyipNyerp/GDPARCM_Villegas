#include "FadeScreen.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "VideoObject.h"
#include "FPSCounter.h"
#include "AuditionGame.h"

FadeScreen::FadeScreen() : AGameObject("FadeScreenObject")
{
}

void FadeScreen::initialize() 
{
    std::cout << "Declared as " << this->getName() << "\n";

    //assign texture
    this->sprite = new sf::Sprite();
    sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Fade", 0);
    this->sprite->setTexture(*texture);
    //make BG height x k to emulate repeating BG.

    this->sprite->setColor(sf::Color(0, 0, 0, 255));

    fading = true;

    this->auditionGame = dynamic_cast<AuditionGame*>(GameObjectManager::getInstance()->findObjectByName("AuditionGameObject"));
    this->auditionGame->enabled = false;
    initialVolume = this->auditionGame->loadingMusic->getVolume();
}

void FadeScreen::processInput(sf::Event event) 
{
}

void FadeScreen::update(sf::Time deltaTime) 
{
    if (fading)
    {
        this->fadeTicks += deltaTime.asMilliseconds();
        float alpha = this->fadeTicks / this->fadeDuration;
        this->sprite->setColor(sf::Color(0, 0, 0, static_cast<int>(alpha * 255)));

        float volume = this->auditionGame->loadingMusic->getVolume() - (deltaTime.asMilliseconds() / fadeDuration) * initialVolume;
        volume = std::max(volume, 0.0f);
        this->auditionGame->loadingMusic->setVolume(volume);

        //float remainingTime = this->fadeDuration - this->fadeTicks;
        //std::cout << "Remaining Time: " << remainingTime << " ms" << std::endl;

        if (this->fadeTicks >= this->fadeDuration)
        {
            fading = false;
            this->fadeTicks = 0;

            this->auditionGame->~AuditionGame();
            GameObjectManager::getInstance()->deleteObjectByName("AuditionGameObject");
            GameObjectManager::getInstance()->deleteObjectByName("BGObject");
            GameObjectManager::getInstance()->deleteObjectByName("ProgressBarObject");
            GameObjectManager::getInstance()->deleteObjectByName("ProgressFillObject");
            GameObjectManager::getInstance()->deleteObjectByName("moveSequenceContainerObject");
            GameObjectManager::getInstance()->deleteObjectByName("playerInputContainerObject");
            GameObjectManager::getInstance()->deleteObjectByName("FPSCounter");

            VideoObject* videoObject = new VideoObject("Video_BlackParade");
            GameObjectManager::getInstance()->addObject(videoObject);

            FPSCounter* fpsCounter = new FPSCounter();
            GameObjectManager::getInstance()->addObject(fpsCounter);
        }
    }
}
