#pragma once

#include "Player.h"
#include "State.h"

class State;
class gui::ProgressBar;
class Player;

class PlayerGUI
{
private:
	//Main Stuff:
	Player* player;
	sf::Font font;

	//Level Box Stuff:
	sf::RectangleShape levelBox;
	sf::Text* levelText;
	std::string currentLevel;
	bool is;

	//EXP Bar Stuff:
	gui::ProgressBar* expBar;

	//HP Bar Stuff:
	gui::ProgressBar* hpBar;


	

	//Initializers:
	void initFont();
	void initLevelBox(State*);
	void initHpBar(State*);
	void initEXPBar(State*);
	


public:

	PlayerGUI(Player* player, State*);
	~PlayerGUI();


	void updateHPBar();
	void updateEXPBar();
	void updateLevel();
	void updateProgressBar();
	void update(const float& dt);


	void renderHPBar(sf::RenderTarget& target);
	void renderEXPBar(sf::RenderTarget& target);
	void renderLevelBox(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

};

