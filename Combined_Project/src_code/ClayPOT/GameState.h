#pragma once
#include "State.h"
#include"PauseMenu.h"
#include"TileMap.h"
#include"PlayerGUI.h"
#include "Renderable.h"
#include "Tile.h"
#include"Sword.h"
#include "Bow.h"
#include "AIPlayer.h"
#include "AIManager.h"
#include "SoundLibrary.h"

class PauseMenu;
class Player;
class PlayerGUI;
class TileMap;
class sf::Font;
class sf::RenderTexture;
class Renderable;
class sf::View;
class Tile;
class Sword;
class Bow;
class AIPlayer;
class AIManager;

class GameState : public State
{

private:
	sf::View view;
	sf::Vector2i viewGridPosition;
	sf::RenderTexture* renderTexture;
	sf::Sprite* renderSprite;



	Player* player;
	PlayerGUI* playerGUI;
	sf::Font font;
	PauseMenu* pauseMenu;
	TileMap* tileMap;
	std::vector<std::vector<int>> grid;


	//Test Enemy Delete after testing:
	std::vector<AIPlayer* > enemy;
	std::unique_ptr<AIManager> aiManager;

	//Shaders:
	sf::Shader core_Shader;

	//Important var for later:
	std::vector< std::vector < std::vector < std::vector < Tile* > > > > map;

	//Functions:
	void initDeferedRender();
	void initView();
	void initKeyBinds();
	void initTextures();
	void initPlayers();
	void initPlayerGUI();
	void initGrid();
	void initAIManager();
	void initAIPlayer();
	void initFonts();
	void initPauseMenu();
	void initTileMap();
	void initShader();

public:

	GameState(StateData* state_Data);
	~GameState();
	
	void updateButtons();
	void updateView();
	void updateTileMap(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updateAIPlayer(const float& dt);
	void update(const float& dt);
	void updateInput(const float& dt);
	void renderGrid(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);

};

