#include "stdafx.h"
#include "MainMenuState.h"

void MainMenuState::initVariables()
{
}



void MainMenuState::initBackground()
{

	this->background.setSize(static_cast<sf::Vector2f>(this->state_Data->window->getSize()));
	if (!this->backgroundTexture.loadFromFile("Resources/Background/bg1.png"))
		throw "ERROR::COULD'NT LOAD FROM::Resources/Background/bg2.jpeg";

	this->background.setTexture(&this->backgroundTexture);

}

void MainMenuState::initFonts()
{

	if (!font.openFromFile("Resources/Fonts/CinzelDecorative-Bold.ttf")) {
		throw("ERROR MAIN MENUSTATE :: CAN'T LAOD FONT FROM :: Resources/Fonts/CinzelDecorative-Bold.ttf");
	}

}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button(this->p2pX(960), this->p2pY(400), this->p2pX(250), this->p2pY(70), &this->font, "New Game", this->characterSize(45),
		sf::Color(58, 47, 35, 0), sf::Color(200, 140, 80, 0), sf::Color(44, 30, 18, 0),
		sf::Color(255, 214, 138, 255), sf::Color(200, 140, 80, 255), sf::Color(255, 202, 120, 255));

	this->buttons["SETTINGS"] = new gui::Button(this->p2pX(960), this->p2pY(550), this->p2pX(250), this->p2pY(70), &this->font, "Settings", this->characterSize(45),
		sf::Color(58, 47, 35, 0), sf::Color(200, 140, 80, 0), sf::Color(44, 30, 18, 0),
		sf::Color(255, 214, 138, 255), sf::Color(200, 140, 80, 255), sf::Color(255, 202, 120, 255));

	this->buttons["EXIT_STATE"] = new gui::Button(this->p2pX(960), this->p2pY(900), this->p2pX(100), this->p2pY(60), &this->font, "Quit", this->characterSize(35),
		sf::Color(58, 47, 35, 0), sf::Color(200, 140, 80, 0), sf::Color(44, 30, 18, 0),
		sf::Color(255, 214, 138, 255), sf::Color(200, 140, 80, 255), sf::Color(255, 202, 120, 255));


}

void MainMenuState::initKeyBinds()
{

	std::ifstream ifs("Config/MainMenuState_keybinds.ini");
	if (ifs.is_open()) {

		std::string key;
		std::string key2;

		while (ifs >> key >> key2) {

			keybinds[key] = this->state_Data->supportedKeys->at(key2);

		}

		ifs.close();
	}

}

MainMenuState::MainMenuState(StateData* state_Data) : State(state_Data)
{

	this->initVariables();
	this->initBackground();
	this->initKeyBinds();
	this->initFonts();
	this->initButtons();
	SoundLibrary::playMusic("BackGroundMusic");
}

MainMenuState::~MainMenuState()
{

	for (auto& it : buttons) {

		delete it.second;

	}

}

void MainMenuState::updateInput(const float& dt)
{

	//This will make menu close from escape
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close")))){
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close")))) {
			std::cout << "Ending MainMenu State\n";
		}
		this->endState();
	}*/
	
}

void MainMenuState::updateButtons()
{

	for (auto& it : buttons)
		it.second->update(this->mousePosWin);


	if (this->buttons["GAME_STATE"]->isPressed()) {
		this->state_Data->states->push(new GameState(this->state_Data));
		SoundLibrary::stopMusic("BackGroundMusic");
	}
	
	if (this->buttons["SETTINGS"]->isPressed()) {
		this->state_Data->states->push(new SettingState(this->state_Data));
	}
	if (this->buttons["EXIT_STATE"]->isPressed()) {
		this->endState();
		std::cout << "Ending MainMenu State\n";
	}

}

void MainMenuState::updatePosition()
{
	this->background.setSize(static_cast<sf::Vector2f>(this->state_Data->window->getSize()));
	this->buttons["GAME_STATE"]->updatePositions(this->p2pX(960), this->p2pY(400), this->p2pX(250), this->p2pY(70), this->characterSize(45));
	this->buttons["SETTINGS"]->updatePositions(this->p2pX(960), this->p2pY(700), this->p2pX(250), this->p2pY(70), this->characterSize(45));
	this->buttons["EXIT_STATE"]->updatePositions(this->p2pX(960), this->p2pY(900), this->p2pX(200), this->p2pY(60), this->characterSize(35));
	State::MainMenuStateUpdated = false;
}

void MainMenuState::update(const float& dt)
{
	
	this->state_Data->window->setView(this->state_Data->window->getDefaultView());
	this->updateInput(dt);
	if (State::MainMenuStateUpdated)
		this->updatePosition();
	this->updateMousePositions();
	this->updateButtons();

}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{

	for (auto& it : buttons)
		it.second->render(target);

}

void MainMenuState::render(sf::RenderTarget& target)
{

	target.draw(this->background);
	this->renderButtons(target);

}
