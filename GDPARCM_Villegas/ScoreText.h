#pragma once
#include "AGameObject.h"

class ScoreText : public AGameObject
{
public:
	ScoreText();
	~ScoreText();
	void initialize() override;
	void processInput(sf::Event event) override;
	void update(sf::Time deltaTime) override;
	void draw(sf::RenderWindow* targetWindow) override;

	void updateScore(int score);

private:
	sf::Text* text;
};

