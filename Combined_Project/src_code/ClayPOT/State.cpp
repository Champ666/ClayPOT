#include "stdafx.h"
#include "State.h"


bool State::SettingStateupdated = false;
bool State::MainMenuStateUpdated = false;

//Constructors Destructors
State::State(StateData* state_Data)
{

	this->state_Data = state_Data;
	this->quit = false;
	this->pause = false;
	SettingStateupdated = false;
	MainMenuStateUpdated= false;
	
}

State::~State()
{

}

const bool& State::getQuit() const
{
	return this->quit;
}




//Fucntions:

void State::endState()
{

	this->quit = true;

}

const float State::p2pX(float size)
{
	size = size / 1920;
	return std::floor(static_cast<float>(this->state_Data->gfx->resolution.size.x * size));
}

const float State::p2pY(float size)
{
	size = size / 1080;
	return std::floor(static_cast<float>(this->state_Data->gfx->resolution.size.y * size));
}

const unsigned State::characterSize(unsigned size)
{
	float percent = (static_cast<float>(size) / 1080.f);
	return std::floor(static_cast<unsigned>(this->state_Data->gfx->resolution.size.y * percent));
}

void State::pauseState()
{

	this->pause = !this->pause;

}

void State::unPauseState()
{

	this->pause = false;

}

void State::handleEvent(const sf::Event& event)
{

}

void State::updateMousePositions(sf::View* view)
{

	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWin = sf::Mouse::getPosition(*this->state_Data->window);

	if(view)
		this->state_Data->window->setView(*view);

	this->mousePosView = this->state_Data->window->mapPixelToCoords(sf::Mouse::getPosition(*this->state_Data->window));
	this->mousePosGrid = sf::Vector2i({ static_cast<int>(mousePosView.x) / 
		                                static_cast<int>(this->state_Data->gridSize.x),
		                                static_cast<int>(mousePosView.y) /
		                                static_cast<int>(this->state_Data->gridSize.y)
		                             });
	

}