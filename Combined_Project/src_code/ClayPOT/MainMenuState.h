#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "SettingState.h"
#include "GraphicsSettings.h"
#include "SoundLibrary.h"


class MainMenuState : public State
{
private:
	//Variables:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	std::map<std::string, gui::Button*> buttons;

	//Audio
	

	//Initializers Functions:
	void initVariables();
	void initBackground();
	void initFonts();
	void initButtons();
	void initKeyBinds();

public:

	MainMenuState(StateData* state_Data);
	~MainMenuState();

	//Funtions:
	void updateButtons();
	void updatePosition();
	void update(const float& dt);
	void updateInput(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
	

};

