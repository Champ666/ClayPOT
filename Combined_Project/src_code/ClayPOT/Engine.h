#pragma once
#include "MainMenuState.h"
#include "SoundLibrary.h"

class SoundLibrary;

class Engine
{
private:
	//Variables:

	//Windows Related Stuff
	sf::RenderWindow* window;
	GraphicsSettings gfx;
	sf::Clock clock;
	float dt;
	sf::Vector2f gridSize;

	

	//Engine Managment
	std::stack<State*> states;
	std::map<std::string, sf::Keyboard::Key> supportedKeys;
	StateData* state_Data;
	

	//Initializers:
	void initSoundLibrary();
	void initVar();
	void initGFX();
	void initKeys();
	void initWin();
	void initStateData();
	void initStates();
	


	//Important functions:
	void updateSFMLEvents();
	void updateDt();
	void endEngine();
	void update();
	void render();

public:


	//Game Loop:
	void run();


	//Cons / Des:
	Engine();
	~Engine();

};

