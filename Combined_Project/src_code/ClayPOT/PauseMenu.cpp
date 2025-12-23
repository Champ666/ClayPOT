#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font, int textSize) : font(font)
{

	this->background.setSize({ static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) });
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize({ static_cast<float>(window.getSize().x / 4.0f), static_cast<float>(window.getSize().y - 100) });
	this->container.setOrigin({ this->container.getSize().x / 2.0f, this->container.getSize().y / 2.0f });
	this->container.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });
	this->container.setFillColor(sf::Color(20, 20, 20, 200));

	this->label = new sf::Text(font);
	this->label->setString("PAUSED");
	this->label->setCharacterSize(textSize);
	this->label->setFillColor(sf::Color(235, 235, 220));
	this->label->setOrigin({ label->getGlobalBounds().size.x / 2.0f, label->getGlobalBounds().size.x / 2.0f });
	this->label->setPosition({ window.getSize().x / 2.0f, 150 });


}

PauseMenu::~PauseMenu()
{

	for (auto& it : this->buttons) {
		delete it.second;
	}

	delete this->label;
}

void PauseMenu::addButtons(const std::string key, float x, float y, const std::string text, const int size)
{

	this->buttons[key] = new gui::Button(x, y, 250, 70, &this->font, text, size,
		sf::Color(58, 47, 35, 0.85 * 0), sf::Color(160, 96, 48, 0.9 * 0), sf::Color(44, 30, 18, 0.85 * 0),
		sf::Color(235, 235, 220, 1.0 * 255), sf::Color(180, 235, 220, 1.0 * 255), sf::Color(120, 200, 180, 1.0 * 255)
	);

}

void PauseMenu::render(sf::RenderTarget& target)
{

	target.draw(this->background);
	target.draw(this->container);
	target.draw(*this->label);
	for (auto& it : this->buttons) {
		it.second->render(target);
	}

}

const bool PauseMenu::isButtonsPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}


void PauseMenu::update(const sf::Vector2i& mousePosWin)
{

	for (auto& it : this->buttons)
		it.second->update(mousePosWin);

}
