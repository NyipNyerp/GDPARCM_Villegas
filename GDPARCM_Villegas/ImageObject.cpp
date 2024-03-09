#include "ImageObject.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"

ImageObject::ImageObject(String objectName, String texName, bool isFill) : AGameObject(objectName)
{
	this->textureName = texName;
	this->isFillImage = isFill;
}

void ImageObject::initialize()
{
	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(this->textureName, 0);
	this->sprite->setTexture(*texture);

	this->textureSize = this->sprite->getTexture()->getSize();

	sf::IntRect intRect = sf::IntRect(0, 0, this->textureSize.x, this->textureSize.y);
	if (this->isFillImage)
		intRect = sf::IntRect(0, 0, 0, this->textureSize.y);

	this->sprite->setTextureRect(intRect);

}

void ImageObject::processInput(sf::Event event)
{
}

void ImageObject::update(sf::Time deltaTime)
{
	if (this->isFillImage)
	{
		float progress = (static_cast<float>(TextureManager::getInstance()->getNumLoadedStreamTextures()) / static_cast<float>(TextureManager::getInstance()->getStreamingAssetCount())) * 100;
		int progressBarWidth = static_cast<int>((progress / 100) * this->textureSize.x);
		this->sprite->setTextureRect(sf::IntRect(0, 0, progressBarWidth, this->textureSize.y));
	}
}

void ImageObject::setup(float xPos, float yPos, float xScale, float yScale)
{
	this->setPosition(xPos, yPos);
	this->setScale(xScale, yScale);
}
