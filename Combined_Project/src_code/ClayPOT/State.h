#pragma once
#include"Player.h"
#include"Gui.h"
#include "GraphicsSettings.h"

class Player;
class Gui;
class GraphicsSettings;
class State;

class StateData {

public:

	sf::RenderWindow* window;
	std::map<std::string, sf::Keyboard::Key>* supportedKeys;
	std::stack<State* >* states;
	GraphicsSettings* gfx;
	sf::Vector2f gridSize;


	StateData(sf::RenderWindow* window, std::map<std::string, sf::Keyboard::Key>* supportedKeys,
		std::stack<State* >* states, GraphicsSettings* gfx, sf::Vector2f gridSize
		)
	{

		this->window = window;
		this->supportedKeys = supportedKeys;
		this->states = states;
		this->gfx = gfx;
		this->gridSize = gridSize;

	}

};


class State
{

private:


public:

	StateData* state_Data;


protected:

	//Data of states:
	
	std::map<std::string, sf::Keyboard::Key> keybinds;
	bool quit;
	bool pause;
	static bool SettingStateupdated;
	static bool MainMenuStateUpdated;
	sf::Font fnt;


	//Mouse Positions:
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWin;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;


	//Resources:
	std::map<std::string, sf::Texture> textures;


	//Functions:
	virtual void initKeyBinds() = 0;
    
public:

	//Cons
	State(StateData* state_Data);
	virtual ~State();


	//Des
	const bool& getQuit() const;
	virtual void endState();
	
	//Fucntions:
	const float p2pX(float size);
	const float p2pY(float size);
	const unsigned characterSize(const unsigned size);


	void pauseState();
	void unPauseState();
	virtual void handleEvent(const sf::Event& event);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
	virtual void updateMousePositions(sf::View* view = nullptr);

};

