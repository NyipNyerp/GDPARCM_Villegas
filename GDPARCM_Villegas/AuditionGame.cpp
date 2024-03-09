#include "AuditionGame.h"
#include "GameObjectManager.h"
#include "ImageObject.h"
#include <iostream>
#include "TitleText.h"
#include "GuideText.h"

AuditionGame::AuditionGame() : AGameObject("AuditionGameObject") 
{
}

AuditionGame::~AuditionGame()
{
    this->enabled = false;
    this->loadingMusic->stop();
    delete this->loadingMusic;
    GameObjectManager::getInstance()->deleteObjectByName("TitleTextObject");
    GameObjectManager::getInstance()->deleteObjectByName("GuideTextObject");
    GameObjectManager::getInstance()->deleteObjectByName("ScoreTextObject");
    clearPlayerInputArrows();
    clearSequenceArrowObjects();
}

void AuditionGame::initialize() 
{
    if (!this->loadingMusic->openFromFile("C:\\Users\\Derick\\source\\repos\\GDPARCM_Villegas\\Media\\Audio\\ThisBag.mp3"))
        std::cout << "Audio file not found!";
    else
    {
        this->loadingMusic->setLoop(true);
        this->loadingMusic->setVolume(50);
        this->loadingMusic->play();
    }

    this->enabled = true;
    TitleText* titleText = new TitleText();
    GameObjectManager::getInstance()->addObject(titleText);

    GuideText* guideText = new GuideText();
    GameObjectManager::getInstance()->addObject(guideText);

    scoreText = new ScoreText();
    GameObjectManager::getInstance()->addObject(scoreText);

    advanceToNextLevel();
}

void AuditionGame::processInput(sf::Event event) 
{
    if (this->enabled)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down ||
                event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
            {
                if (playerInputs.size() < maxMoves)
                {
                    playerInputs.push_back(getArrowKeyCode(event.key.code));
                    //std::cout << "Player Input Added: " << getArrowKeyCode(event.key.code) << std::endl;
                    displayPlayerInput();
                }
            }
            else if (event.key.code == sf::Keyboard::Space)
            {
                checkPlayerInput();
            }
        }
    }
}

void AuditionGame::update(sf::Time deltaTime) 
{
}

void AuditionGame::advanceToNextLevel()
{
    if (currentLevel < maxMoves)
    {
        currentLevel++;
        generateMoveSequence();
    }
    else
    {
        currentLevel = maxMoves;
        generateMoveSequence();
    }
}

void AuditionGame::generateMoveSequence() 
{
    moveSequence.clear();
    for (int i = 0; i < currentLevel; i++) 
    {
        moveSequence.push_back(rand() % 4);
    }
    displayMoveSequence();
}

void AuditionGame::displayMoveSequence() 
{
    clearSequenceArrowObjects();

    const float baseX = 400.0f;
    const float baseY = 700.0f;
    const float xOffset = 68.0f;

    for (size_t i = 0; i < moveSequence.size(); ++i) 
    {
        std::string arrowType;
        switch (moveSequence[i]) 
        {
            case 0: arrowType = "ArrowUp"; break;
            case 1: arrowType = "ArrowDown"; break;
            case 2: arrowType = "ArrowLeft"; break;
            case 3: arrowType = "ArrowRight"; break;
        }
        ImageObject* arrow = new ImageObject("SequenceArrowObject" + std::to_string(i), arrowType, false);
        arrow->setup(baseX + (xOffset * i), baseY, 1.0f, 1.0f);
        GameObjectManager::getInstance()->addObject(arrow);
    }
}

void AuditionGame::displayPlayerInput()
{
    clearPlayerInputArrows();

    const float baseX = 400.0f;
    const float baseY = 800.0f;
    const float xOffset = 68.0f;

    for (size_t i = 0; i < playerInputs.size(); ++i)
    {
        std::string arrowType;
        switch (playerInputs[i])
        {
            case 0: arrowType = "ArrowUp"; break;
            case 1: arrowType = "ArrowDown"; break;
            case 2: arrowType = "ArrowLeft"; break;
            case 3: arrowType = "ArrowRight"; break;
        }
        ImageObject* arrow = new ImageObject("PlayerArrowObject" + std::to_string(i), arrowType, false);
        arrow->setup(baseX + (xOffset * i), baseY, 1.0f, 1.0f);
        GameObjectManager::getInstance()->addObject(arrow);
    }
}

void AuditionGame::clearSequenceArrowObjects() 
{
    auto objects = GameObjectManager::getInstance()->getAllObjects();
    for (auto obj : objects) 
    {
        if (obj->getName().find("SequenceArrowObject") != std::string::npos) 
        {
            GameObjectManager::getInstance()->deleteObject(obj);
        }
    }
}

void AuditionGame::clearPlayerInputArrows()
{
    auto objects = GameObjectManager::getInstance()->getAllObjects();
    for (auto obj : objects)
    {
        if (obj->getName().find("PlayerArrowObject") != std::string::npos)
        {
            GameObjectManager::getInstance()->deleteObject(obj);
        }
    }
}

void AuditionGame::checkPlayerInput() 
{
    clearPlayerInputArrows();
    //debugDisplayContainers();
    
    std::cout << std::endl;
    if (playerInputs == moveSequence) 
    {
        //std::cout << "Sequence matched!" << std::endl;
        score++;
        scoreText->updateScore(score);
        playerInputs.clear();
        advanceToNextLevel();
    }
    else if (!playerInputs.empty()) 
    {
        //std::cout << "Sequence incorrect." << std::endl;
        playerInputs.clear();
    }
}


int AuditionGame::getArrowKeyCode(sf::Keyboard::Key key) 
{
    switch (key) 
    {
        case sf::Keyboard::Up: return 0;
        case sf::Keyboard::Down: return 1;
        case sf::Keyboard::Left: return 2;
        case sf::Keyboard::Right: return 3;
        default: return -1;
    }
}

void AuditionGame::debugDisplayContainers()
{
    std::cout << "Move Sequence: ";
    for (auto& move : moveSequence)
    {
        std::cout << move << " ";
    }
    std::cout << std::endl;

    std::cout << "Player Inputs: ";
    for (auto& input : playerInputs)
    {
        std::cout << input << " ";
    }
}
