#include "TitleText.h"
#include <iostream>
#include "BaseRunner.h"

TitleText::TitleText() : AGameObject("TitleTextObject")
{
}

TitleText::~TitleText()
{
	delete this->text->getFont();
	delete this->text;
	AGameObject::~AGameObject();
}

void TitleText::initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	this->text = new sf::Text();
	this->text->setFont(*font);
	this->text->setPosition((BaseRunner::WINDOW_WIDTH / 2) - 550, (BaseRunner::WINDOW_HEIGHT / 2) + 80);
	this->text->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->text->setOutlineThickness(5.0f);
	this->text->setCharacterSize(50);
	this->text->setString("PARCM AUDITION OFFLINE");
}

void TitleText::processInput(sf::Event event)
{
}

void TitleText::update(sf::Time deltaTime)
{
}

void TitleText::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if (this->text != nullptr)
		targetWindow->draw(*this->text);
}