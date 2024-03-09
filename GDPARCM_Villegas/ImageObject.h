#pragma once
#include "AGameObject.h"

class ImageObject : public AGameObject
{
public:
	ImageObject(String objectName, String texName, bool isFill);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void setup(float xPos, float yPos, float xScale, float yScale);

private:
	sf::Vector2u textureSize;
	String textureName;
	bool isFillImage = false;
};

