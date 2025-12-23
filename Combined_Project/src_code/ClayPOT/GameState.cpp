#include "stdafx.h"
#include "GameState.h";
#include <random>


void GameState::initDeferedRender()
{
	this->renderTexture = new sf::RenderTexture({ this->state_Data->gfx->resolution.size.x,
		this->state_Data->gfx->resolution.size.x });

	this->renderSprite = new sf::Sprite(this->renderTexture->getTexture());

	this->renderSprite->setTextureRect(sf::IntRect({ 0,0 },
		{ static_cast<int>(this->state_Data->gfx->resolution.size.x),
		static_cast<int>(this->state_Data->gfx->resolution.size.y) }));

	
}

void GameState::initView()
{

	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->state_Data->gfx->resolution.size.x),
			static_cast<float>(this->state_Data->gfx->resolution.size.y)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->state_Data->gfx->resolution.size.x / 2),
			static_cast<float>(this->state_Data->gfx->resolution.size.y / 2
		)
	));

}


void GameState::initKeyBinds()
{

	std::ifstream ifs("Config/GameState_keybinds.ini");
	if (ifs.is_open()) {

		std::string key;
		std::string key2;

		while (ifs >> key >> key2) {

			keybinds[key] = this->state_Data->supportedKeys->at(key2);

		}

		ifs.close();
	}
	
}

void GameState::initTextures()
{
	std::cout << "Setting Texture!\n";
	if (!this->textures["PLAYER_IDLE"].loadFromFile("Resources/Animations/p1.png"))
		throw"ERROR::CAN'T LOAD::Resources/Animations/p1.png";
	if (!this->textures["SCORPIO"].loadFromFile("Resources/Animations/scorpian.png"))
		throw"ERROR::CAN'T LOAD::Resources/Animations/scorpian.png";
	if (!this->textures["BIRD"].loadFromFile("Resources/Animations/bird.png"))
		throw"ERROR::CAN'T LOAD::Resources/Animations/bird.png";

}

void GameState::initPlayers()
{
	std::cout << "Sending Texture!\n";
	float x_pos = 2;
	float y_pos = 14;
	float width = 2.0f;
	float height = 2.0f;
	this->player = new Player(x_pos, y_pos, width, height, this->textures["PLAYER_IDLE"]);

}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this);
	
}

void GameState::initGrid()
{
	this->grid = {
		{1, 1, 1, 1, 1},
		{1, -1, -1, 1, 1},
		{1, 1, 2, 2, 1} // roads=1, grass=2
	};
}

void GameState::initAIManager()
{
	this->aiManager = std::make_unique<AIManager>(5, 3, grid);
	this->aiManager->initTasks();
}

void GameState::initAIPlayer()
{
	this->enemy.push_back(new AIPlayer(2, 12, 1.f, 1.f, this->textures["BIRD"], 
		this->aiManager.get(), this->tileMap->getGraph(), this->tileMap->maxSize.x, this->player));
	
}

void GameState::initFonts()
{

	if (!this->font.openFromFile("Resources/Fonts/FeDPsc2.ttf")) {
		throw("ERROR MAIN MENUSTATE :: CAN'T LAOD FONT FROM :: Resources/Fonts/FeDPsc2.ttf");
	}

}

void GameState::initPauseMenu()
{

	this->pauseMenu = new PauseMenu(*this->state_Data->window, this->font, 30);
	this->pauseMenu->addButtons("RESUME", this->p2pX(960), this->p2pY(300), "Resume", this->characterSize(45));
	this->pauseMenu->addButtons("OPTION", this->p2pX(960), this->p2pY(450), "Options", this->characterSize(45));
	this->pauseMenu->addButtons("SETTING", this->p2pX(960), this->p2pY(600), "Setting", this->characterSize(45));
	this->pauseMenu->addButtons("QUIT", this->p2pX(960), this->p2pY(950), "Quit", this->characterSize(30));


}

void GameState::initTileMap()
{

	this->tileMap = new TileMap("Resources/Map/map");
	this->map = this->tileMap->getMap();
	this->tileMap->initializeGraphNodes();

}

void GameState::initShader()
{

	if (!core_Shader.loadFromFile("ver_shader.vert", "frag_shader.frag"))
		std::cerr << "Failed to load shaders";
	else {
		core_Shader.setUniform("texture0", sf::Shader::CurrentTexture);
	}
	
}

GameState::GameState(StateData* state_Data) : State(state_Data)
{
	this->initDeferedRender();
	this->initKeyBinds();
	this->initTextures();
	this->initPlayers();
	this->initPlayerGUI();
	this->initGrid();
	this->initAIManager();
	this->initFonts();
	this->initPauseMenu();
	this->initTileMap();
	this->initAIPlayer();
	this->initView();
	this->initShader();
	this->state_Data->window->setMouseCursorVisible(false);
	
}

GameState::~GameState()
{

	delete player;
	delete pauseMenu;
	delete this->tileMap;
	delete this->playerGUI;
	for (auto& it : this->enemy) {
		delete it;
	}

}

void GameState::updateInput(const float& dt)
{
	if(!this->pause){

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
			this->player->move(dt, -1.0f, 0.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
			this->player->move(dt, 1.0f, 0.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
			this->player->move(dt, 0.0f, -1.0f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
			this->player->move(dt, 0.0f, 1.0f);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			this->player->isAttacking(true);
		}

		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close")))){
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close")))) {
		
		}
		std::cout << "Paused!\n";
		if (this->pause)
			this->state_Data->window->setMouseCursorVisible(false);
		else
			this->state_Data->window->setMouseCursorVisible(true);
		this->pauseState();
	}

}



void GameState::updateButtons()
{

	if (this->pauseMenu->isButtonsPressed("QUIT")) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			std::cout << "Resuming Game State";
		this->endState();
		SoundLibrary::playMusic("BackGroundMusic");
	}
	if (this->pauseMenu->isButtonsPressed("RESUME")) {
		while(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			std::cout << "Resuming Game State";
		this->state_Data->window->setMouseCursorVisible(false);
		this->unPauseState();
	}

}

void GameState::updateView()
{

	this->view.setCenter({
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWin.x) - static_cast<float>(this->state_Data->gfx->resolution.size.x / 2)) / 10.f),
		std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWin.y) - static_cast<float>(this->state_Data->gfx->resolution.size.y / 2)) / 10.f)
		});


	if (this->tileMap->worldSize.x >= this->view.getSize().x) {
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f) {
			this->view.setCenter({ this->view.getSize().x / 2.f, this->view.getCenter().y });
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->worldSize.x) {
			this->view.setCenter({ (this->tileMap->worldSize.x) - (this->view.getSize().x / 2.f), this->view.getCenter().y });
		}
	}
	

	if (this->tileMap->worldSize.y >= this->view.getSize().x) {
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0) {
			this->view.setCenter({ this->view.getCenter().x , this->view.getSize().y / 2.f });
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->worldSize.y) {
			this->view.setCenter({ this->view.getCenter().x, this->tileMap->worldSize.y - this->view.getSize().y / 2.f });
		}
	}
	
	
	

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->state_Data->gridSize.x);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->state_Data->gridSize.y);

}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->update(dt, this->player);
}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}



void GameState::updateAIPlayer(const float& dt)
{
	for (auto& it : this->enemy)
		it->update(dt, this->mousePosView);
}

void GameState::update(const float& dt)
{

	this->updateMousePositions(&this->view);
	if(!this->pause){
		this->updateView();
		this->updateInput(dt);
		this->player->update(dt, this->mousePosView);
		this->updateAIPlayer(dt);
		this->updatePlayerGUI(dt);
		this->updateTileMap(dt);
	}
	else {
		this->updateInput(dt);
		this->pauseMenu->update(this->mousePosWin);
		this->updateButtons();
	}
}

void GameState::renderGrid(sf::RenderTarget& target)
{

	std::multimap<float, Renderable> grid;

	// insert player
	grid.insert({ this->player->getPosition().y + this->player->getGloabalBounds().size.y - 2, Renderable(this->player) });

	int fromX = (this->player->getPosition().x / this->state_Data->gridSize.x) - 1;
	int fromY = (this->player->getPosition().y / this->state_Data->gridSize.x) - 1;
	int toX = (this->player->getPosition().x / this->state_Data->gridSize.y) + 3;
	int toY = (this->player->getPosition().y / this->state_Data->gridSize.y) + 2;

	if (fromX < 0) {
		fromX = 0;
	}
	else if (fromX >= this->tileMap->maxSize.x) {
		fromX = this->tileMap->maxSize.x;
	}
	if (fromY < 0) {
		fromY = 0;
	}
	else if (fromY >= this->tileMap->maxSize.y) {
		fromY = this->tileMap->maxSize.y;
	}

	if (toX < 0) {
		toX = 0;
	}
	else if (toX >= this->tileMap->maxSize.x) {
		toX = this->tileMap->maxSize.x;
	}
	if (toY < 0) {
		toY = 0;
	}
	else if (toY >= this->tileMap->maxSize.y) {
		toY = this->tileMap->maxSize.y;
	}

	for (size_t x = fromX; x < toX; ++x) {
		for (size_t y = fromY; y < toY; ++y) {
			if (!map[x][y][0].empty() && map[x][y][0].back()->getType() == TileTypes::FRONT) {
				Tile* t = map[x][y][0].back();
				grid.insert({ map[x][y][this->tileMap->layer].back()->getPosition().y + map[x][y][this->tileMap->layer].back()->getGlobalBounds().size.y, Renderable(t) });
			}
		}

	}

	
	
	for (auto& [y, obj] : grid) {
		obj.render(target, &this->core_Shader);
	}

}

void GameState::render(sf::RenderTarget& target)
{
	
	//Map Rendering
	this->tileMap->render(target, this->viewGridPosition,
		this->player);
	this->renderGrid(target);
	for (auto& it : this->enemy) {
		it->render(target, &this->core_Shader);
	}
	this->tileMap->renderDeferredTiles(target);

	//Player HP || MiniMaps and stuff
	target.setView(this->state_Data->window->getDefaultView());
	this->playerGUI->render(target);

	//Pause Menu
	if (this->pause) {
		target.setView(this->state_Data->window->getDefaultView());
		this->pauseMenu->render(target);
	}

	

}
