#pragma once
#include "State.h"
class SettingState : public State
{

private:

	//Variables:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, gui::DropDownList*> dropDownList;
	std::vector<sf::VideoMode> videoModes;
	sf::Text* textOptions;

	//Initializers Functions:
	void initVariables();
	void initBackground();
	void initFonts();
	void initText();
	void initButtons();
	void initDropDownList();
	void initKeyBinds();

public:

	SettingState(StateData* state_Data);
	~SettingState();


	//Funtions:
	void updateButtons();
	void updateDropDownList();
	void updatePositions();
	void update(const float& dt);
	void updateInput(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void renderDropDownList(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);



};

