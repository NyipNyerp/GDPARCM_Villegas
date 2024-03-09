#pragma once
#include "AGameObject.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "ScoreText.h"
#include <SFML/Audio.hpp>

class AuditionGame : public AGameObject {
public:
    AuditionGame();
    ~AuditionGame();
    void initialize() override;
    void processInput(sf::Event event) override;
    void update(sf::Time deltaTime) override;

    void clearSequenceArrowObjects();
    void clearPlayerInputArrows();

    bool enabled = true;

    sf::Music* loadingMusic = new sf::Music();

private:
    void advanceToNextLevel();
    void generateMoveSequence();

    void displayMoveSequence();
    void displayPlayerInput();

    void checkPlayerInput();
    int getArrowKeyCode(sf::Keyboard::Key key);

    void debugDisplayContainers();

    std::vector<int> moveSequence;
    std::vector<int> playerInputs;
    int maxMoves = 16;
    int currentLevel = 0;
    int score = 0;

    ScoreText* scoreText;

};