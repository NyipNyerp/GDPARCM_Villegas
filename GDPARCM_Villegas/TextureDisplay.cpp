#include "TextureDisplay.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "IconObject.h"
#include "IETThread.h"
#include "FadeScreen.h"

TextureDisplay::TextureDisplay() : AGameObject("TextureDisplay")
{
}

void TextureDisplay::initialize()
{

}

void TextureDisplay::processInput(sf::Event event)
{

}

void TextureDisplay::update(sf::Time deltaTime)
{
	this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();

	//<code here for spawning icon object periodically>

	if (this->streamingType == StreamingType::BATCH_LOAD && !this->startedStreaming && this->ticks > this->STREAMING_LOAD_DELAY)
	{
		this->startedStreaming = true;
		this->ticks = 0;
		TextureManager::getInstance()->loadStreamingAssets();
	}
	else if (this->streamingType == StreamingType::SINGLE_STREAM && this->ticks > STREAMING_LOAD_DELAY)
	{
		this->ticks = 0;
		TextureManager::getInstance()->loadSingleStreamAsset(this->numDisplayed, this);
		this->numDisplayed++;
		
		//std::cout << "loaded tex: " << TextureManager::getInstance()->getNumLoadedStreamTextures() << std::endl;
		//this->spawnObject();
		//TextureManager::getInstance()->loadSingleStreamAsset(this->counter);
		//this->counter++;
	}
}

void TextureDisplay::onFinishedExecution()
{
	//this->spawnObject();
	//std::cout << "Loaded Frames: " << TextureManager::getInstance()->getNumLoadedStreamTextures() << " / " << TextureManager::getInstance()->getStreamingAssetCount() << std::endl;
	updateMusicProgressBar();

	if (TextureManager::getInstance()->getNumLoadedStreamTextures() == TextureManager::getInstance()->getStreamingAssetCount())
	{
		std::cout << "Total assets: " << TextureManager::getInstance()->getNumLoadedStreamTextures() << std::endl;
		std::cout << "ALL FRAMES LOADED" << std::endl;

		FadeScreen* transition = new FadeScreen();
		GameObjectManager::getInstance()->addObject(transition);
	}
}

void TextureDisplay::spawnObject()
{
	this->guard.lock();

	String objectName = "Icon_" + to_string(this->iconList.size());
	IconObject* iconObj = new IconObject(objectName, this->iconList.size());
	this->iconList.push_back(iconObj);

	//set position
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;
	iconObj->setPosition(0, 0);

	//std::cout << "Set position: " << x << " " << y << std::endl;

	/*this->columnGrid++;	
	if (this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}*/

	GameObjectManager::getInstance()->addObject(iconObj);

	this->guard.unlock();
}

void TextureDisplay::updateMusicProgressBar()
{
	float progress = (static_cast<float>(TextureManager::getInstance()->getNumLoadedStreamTextures()) / static_cast<float>(TextureManager::getInstance()->getStreamingAssetCount())) * 100;
	//std::cout << "Progress: " << progress << "%" << std::endl;
}
