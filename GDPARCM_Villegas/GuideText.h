#pragma once
#include "AGameObject.h"

class GuideText : public AGameObject
{
public:
	GuideText();
	~GuideText();
	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;

private:
	sf::Text* text;
};
