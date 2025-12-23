#pragma once

#include "Gui.h"

class PauseMenu
{

private:

	sf::Font& font;
	sf::Text* label;
	sf::RectangleShape background;
	sf::RectangleShape container;
	std::map<std::string, gui::Button*> buttons;

public:

	PauseMenu(sf::RenderWindow& window, sf::Font& font, int);
	~PauseMenu();


	void addButtons(const std::string key, float x, float y, const std::string text, const int size);
	void render(sf::RenderTarget& target);
	const bool isButtonsPressed(const std::string key);
	void update(const sf::Vector2i& mousePosWin);

};

