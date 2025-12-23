#include "stdafx.h"
#include "Engine.h"


void Engine::initSoundLibrary()
{
	SoundLibrary::loadSound("Whistle", "Resources/Audio/whistle.wav");
	SoundLibrary::loadSound("BTN_HOVER", "Resources/Audio/hover.wav");
	SoundLibrary::loadSound("BTN_ACTIVE", "Resources/Audio/click.wav");
	SoundLibrary::loadMusic("BackGroundMusic", "Resources/Audio/ac-2.ogg");
	SoundLibrary::loadSound("Footsteps", "Resources/Audio/footsteps.wav");
}


//Initializers:
void Engine::initVar()
{

	this->window = nullptr;
	this->dt = 0.0f;
	this->gridSize.x = 64.f;
	this->gridSize.y = 64.f;

}
 
void Engine::initGFX()
{

	gfx.loadFromFile("Config/graphics.ini");

}

void Engine::initWin()
{

	if(this->gfx.fullScreen)
		window = new sf::RenderWindow
		(this->gfx.resolution,
			this->gfx.title,
			sf::State::Fullscreen, 
			this->gfx.contextSettings);

	else
		window = new sf::RenderWindow
		(this->gfx.resolution,
			this->gfx.title,
			sf::Style::Titlebar
			| sf::Style::Close,
			sf::State::Windowed,
			this->gfx.contextSettings);


	window->setFramerateLimit(this->gfx.frameLimit);
	window->setVerticalSyncEnabled(this->gfx.verticleSync);

}

void Engine::initStateData()
{

	this->state_Data = new StateData(this->window, &this->supportedKeys, &this->states,
		&this->gfx, this->gridSize);
	
}

void Engine::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");
	if (ifs.is_open()) {

		std::string key;
		int value;

		while (ifs >> key >> value) {

			supportedKeys[key] = static_cast<sf::Keyboard::Key>(value);

		}
		
		ifs.close();
	}
}

void Engine::initStates()
{

	this->states.push(new EditorState(this->state_Data));
	

}



//Constructor Destructor:
Engine::Engine()
{
	initVar();
	initGFX();
	initKeys();
	initWin();
	initStateData();
	initStates();
	initSoundLibrary();
	clock.restart();
}

Engine::~Engine()
{

	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}

	delete window;
	delete this->state_Data;

}





//Updates:
void Engine::updateSFMLEvents()
{
	
	while (std::optional event = window->pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window->close();
			return;
		}
		if (!states.empty()) {
			states.top()->handleEvent(*event);
		}
	}

}

void Engine::updateDt()
{

	dt = clock.restart().asSeconds();
	
}

void Engine::endEngine()
{

	std::cout << "\nDEBUG::Ending Engine!";

}

void Engine::update()
{

	//Update Events:
	updateSFMLEvents();
	updateDt();


	//Update States:
	if (!states.empty()){
	
		if (this->window->hasFocus()) {
			states.top()->update(this->dt);

			if (this->states.top()->getQuit()) {
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}


		}
	}
	else {

		this->endEngine();
		this->window->close();

	}
}



//Rendering
void Engine::render()
{

	window->clear();
	//Rendering will goes here!

	if (!states.empty())
		states.top()->render(*this->window);

	window->display();

}

void Engine::run()
{
	
	while (window->isOpen()) {

		update();
		render();

	}

}

