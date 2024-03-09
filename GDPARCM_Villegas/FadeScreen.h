#pragma once
#include "AGameObject.h"
#include "AuditionGame.h"

class FadeScreen : public AGameObject 
{
public:
    FadeScreen();
    void initialize();
    void processInput(sf::Event event);
    void update(sf::Time deltaTime);

private:
    float initialVolume; // for loadingMusic
    float fadeDuration = 3000.0f; // ms
    float fadeTicks = 0;
    bool fading = false;

    AuditionGame* auditionGame;
};