#include "ScoreText.h"
#include <iostream>
#include "BaseRunner.h"

ScoreText::ScoreText() : AGameObject("ScoreTextObject")
{
}

ScoreText::~ScoreText()
{
	delete this->text->getFont();
	delete this->text;
	AGameObject::~AGameObject();
}

void ScoreText::initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	this->text = new sf::Text();
	this->text->setFont(*font);
	this->text->setPosition((BaseRunner::WINDOW_WIDTH / 2) + 350, (BaseRunner::WINDOW_HEIGHT / 2) + 100);
	this->text->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->text->setOutlineThickness(2.5f);
	this->text->setCharacterSize(35);

	updateScore(0);
}

void ScoreText::processInput(sf::Event event)
{
}

void ScoreText::update(sf::Time deltaTime)
{
}

void ScoreText::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if (this->text != nullptr)
		targetWindow->draw(*this->text);
}

void ScoreText::updateScore(int score)
{
	this->text->setString("Score: " + std::to_string(score));
}
