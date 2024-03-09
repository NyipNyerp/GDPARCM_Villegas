#include "GuideText.h"
#include <iostream>
#include "BaseRunner.h"

GuideText::GuideText() : AGameObject("GuideTextObject")
{
}

GuideText::~GuideText()
{
	delete this->text->getFont();
	delete this->text;
	AGameObject::~AGameObject();
}

void GuideText::initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	this->text = new sf::Text();
	this->text->setFont(*font);
	this->text->setPosition((BaseRunner::WINDOW_WIDTH / 2) - 500, (BaseRunner::WINDOW_HEIGHT / 2) + 350);
	this->text->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->text->setOutlineThickness(2.0f);
	this->text->setCharacterSize(20);
	this->text->setString("Use ARROW KEYS to input moves. Press SPACEBAR to confirm input.");

}

void GuideText::processInput(sf::Event event)
{
}

void GuideText::update(sf::Time deltaTime)
{
}

void GuideText::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if (this->text != nullptr)
		targetWindow->draw(*this->text);
}
