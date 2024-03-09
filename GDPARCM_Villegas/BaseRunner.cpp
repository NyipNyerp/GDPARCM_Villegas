#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"
#include "ImageObject.h"
#include "AuditionGame.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO: Barrage of Threads - VILLEGAS", sf::Style::Close) {
	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();

	//load objects
	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	ImageObject* progressBar = new ImageObject("ProgressBarObject", "BlankMusicSheet", false);
	progressBar->setup(50.0f, 50.0f, 1.0f, 1.0f);
	GameObjectManager::getInstance()->addObject(progressBar);

	ImageObject* progressFill = new ImageObject("ProgressFillObject", "ProgressNotes", true);
	progressFill->setup(350.0f, 85.0f, 1.0f, 1.0f);
	GameObjectManager::getInstance()->addObject(progressFill);

	ImageObject* moveSequenceContainer = new ImageObject("moveSequenceContainerObject", "ArrowsContainer", false);
	moveSequenceContainer->setup(390.0f, 790.0f, 1.0f, 1.2f);
	GameObjectManager::getInstance()->addObject(moveSequenceContainer);

	ImageObject* playerInputContainer = new ImageObject("playerInputContainerObject", "ArrowsContainer", false);
	playerInputContainer->setup(390.0f, 690.0f, 1.0f, 1.2f);
	GameObjectManager::getInstance()->addObject(playerInputContainer);

	AuditionGame* auditionGame = new AuditionGame();
	GameObjectManager::getInstance()->addObject(auditionGame);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);
}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			processEvents();
			//update(TIME_PER_FRAME);
			update(elapsedTime);
		}
		sf::Time sleepTime = TIME_PER_FRAME - clock.getElapsedTime();
		if (sleepTime > sf::Time::Zero) {
			sf::sleep(sleepTime);
		}

		render();
	}
}

BaseRunner* BaseRunner::getInstance()
{
	return nullptr;
}

float BaseRunner::getFPS()
{
	return this->fps;
}

void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {

		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;

		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}