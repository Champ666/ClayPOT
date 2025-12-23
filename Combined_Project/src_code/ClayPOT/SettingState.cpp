#include "stdafx.h"
#include "SettingState.h"

void SettingState::initVariables()
{

	this->videoModes = sf::VideoMode::getFullscreenModes();

}

void SettingState::initBackground()
{

	this->background.setSize(static_cast<sf::Vector2f>(this->state_Data->window->getSize()));
	if (!this->backgroundTexture.loadFromFile("Resources/Background/bg1.png"))
		throw "ERROR::COULD'NT LOAD FROM::Resources/Background/bg2.jpeg";

	this->background.setTexture(&this->backgroundTexture);

}

void SettingState::initFonts()
{

	if (!font.openFromFile("Resources/Fonts/CinzelDecorative-Bold.ttf")) {
		throw("ERROR MAIN MENUSTATE :: CAN'T LAOD FONT FROM :: Resources/Fonts/CinzelDecorative-Bold.ttf");
	}

}

void SettingState::initText()
{

	this->textOptions = new sf::Text(this->font);
	this->textOptions->setFont(this->font);
	this->textOptions->setCharacterSize(this->characterSize(30));
	this->textOptions->setFillColor(sf::Color(sf::Color(255, 214, 138, 1.0 * 255)));
	this->textOptions->setPosition({ this->p2pX(600), this->p2pY(350)});
	this->textOptions->setString("Resolution\n\n\nFullscreen\n\n\nVSync\n\n\nAntialiasing");

}

void SettingState::initButtons()
{

	this->buttons["EXIT_STATE"] = new gui::Button(this->p2pX(1250), this->p2pY(930), this->p2pX(200), this->p2pY(60), &this->font, "Quit", this->characterSize(35),
		sf::Color(58, 47, 35, 0), sf::Color(160, 96, 48, 0), sf::Color(44, 30, 18, 0),
		sf::Color(255, 214, 138, 1.0 * 255), sf::Color(255, 240, 190, 1.0 * 255), sf::Color(255, 202, 120, 1.0 * 255)
	);

	this->buttons["APPLY"] = new gui::Button(this->p2pX(1090), this->p2pY(930), this->p2pX(200), this->p2pY(60), &this->font, "Apply", this->characterSize(35),
		sf::Color(58, 47, 35, 0), sf::Color(160, 96, 48, 0), sf::Color(44, 30, 18, 0),
		sf::Color(255, 214, 138, 1.0 * 255), sf::Color(255, 240, 190, 1.0 * 255), sf::Color(255, 202, 120, 1.0 * 255)
	);

}

void SettingState::initDropDownList()
{
	
	std::vector<std::string> list;
	for (size_t i = 0; i < 16; i++) {
		list.push_back(std::to_string(videoModes[i].size.x) + ' ' + 'x' + ' ' + std::to_string(videoModes[i].size.y));
	}
	

	std::cout << "\nSETTINGS::RESOLUTION INDEX::" << this->state_Data->gfx->resolutionIndex;
	this->dropDownList["Resolution"] = new gui::DropDownList(this->p2pX(1150.0), this->p2pY(370.0), this->p2pX(300.0),
		this->p2pY(40.0), this->font, list.data(), list.size(), this->state_Data->gfx->resolutionIndex);


	std::string fullscreen[] = { "Of","On" };
	unsigned screenVal = static_cast<unsigned>(this->state_Data->gfx->fullScreen);
	this->dropDownList["FullScreen"] = new gui::DropDownList(this->p2pX(1150.0), this->p2pY(485.0), this->p2pX(150.0),
		this->p2pY(30.0), this->font, fullscreen, 2, screenVal);
	std::cout << "\nSETTINGS::FULLSCREEN::" << screenVal;

	unsigned vsync = static_cast<unsigned>(this->state_Data->gfx->verticleSync);
	this->dropDownList["Vsync"] = new gui::DropDownList(this->p2pX(1150.0), this->p2pY(605.0), this->p2pX(150.0),
		this->p2pY(30.0), this->font, fullscreen, 2, vsync);

	std::string anitianialisingLevel[] = { "Off","2x","4x", "8x" };
	unsigned antVal;
	if(this->state_Data->gfx->contextSettings.antiAliasingLevel != 8)
		antVal = static_cast<unsigned>((this->state_Data->gfx->contextSettings.antiAliasingLevel / 2 ));
	else
		antVal = 3;
	this->dropDownList["AntiAnialising"] = new gui::DropDownList(this->p2pX(1150.0), this->p2pY(725.0),
		this->p2pX(150.0), this->p2pY(30.0), this->font, anitianialisingLevel, 4, antVal);
}

void SettingState::initKeyBinds()
{

	std::ifstream ifs("Config/SettingState_keybinds.ini");
	if (ifs.is_open()) {

		std::string key;
		std::string key2;

		while (ifs >> key >> key2) {

			keybinds[key] = this->state_Data->supportedKeys->at(key2);

		}

		ifs.close();
	}

}

SettingState::SettingState(StateData* state_Data) : State(state_Data)
{

	this->initVariables();
	this->initBackground();
	this->initKeyBinds();
	this->initFonts();
	this->initText();
	this->initButtons();
	this->initDropDownList();

}

SettingState::~SettingState()
{

	for (auto& it : buttons) {

		delete it.second;

	}
	for (auto& it : dropDownList) {

		delete it.second;

	}

	delete this->textOptions;
}

void SettingState::updateInput(const float& dt)
{

	//This will make menu close from escape
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close")))){
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close")))) {
			std::cout << "Ending MainMenu State\n";
		}
		this->endState();
	}
	
}

void SettingState::updateButtons()
{

	for (auto& it : buttons)
		it.second->update(this->mousePosWin);

	if (this->buttons["EXIT_STATE"]->isPressed()) {
		while(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
			std::cout << "Ending MainMenu State\n";
		}
		this->endState();
	}
	if (this->buttons["APPLY"]->isPressed()) {
		if (gui::DropDownList::getChange()) {
			while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				std::cout << "Applying\n";
			}
			gui::DropDownList::setChange(false);
			this->state_Data->gfx->resolution = this->videoModes[this->dropDownList["Resolution"]->getActiveId()];
			std::cout << "\n\n\n\n\nFULLSCREEN::"<< this->dropDownList["FullScreen"]->getActiveId()<<"\n\n\n\n";
			if (this->dropDownList["FullScreen"]->getActiveId() == 1) {
				this->state_Data->gfx->resolutionIndex = this->dropDownList["Resolution"]->getActiveId();
				this->state_Data->gfx->verticleSync = this->dropDownList["Vsync"]->getActiveId();
				if (this->dropDownList["AntiAnialising"]->getActiveId() != 3)
					this->state_Data->gfx->contextSettings.antiAliasingLevel = this->dropDownList["AntiAnialising"]->getActiveId() * 2;
				else
					this->state_Data->gfx->contextSettings.antiAliasingLevel = 8;
				this->state_Data->gfx->fullScreen = true;
				this->state_Data->window->setVerticalSyncEnabled(this->state_Data->gfx->verticleSync);
				this->state_Data->window->create(this->state_Data->gfx->resolution, 
				this->state_Data->gfx->title, sf::State::Fullscreen, this->state_Data->gfx->contextSettings);
			}
			else {
				std::cout << "\n\n\n\n\nInside\n\n\n\n";
				this->state_Data->gfx->resolutionIndex = this->dropDownList["Resolution"]->getActiveId();
				this->state_Data->gfx->verticleSync = this->dropDownList["Vsync"]->getActiveId();
				if (this->dropDownList["AntiAnialising"]->getActiveId() != 3)
					this->state_Data->gfx->contextSettings.antiAliasingLevel = this->dropDownList["AntiAnialising"]->getActiveId() * 2;
				else
					this->state_Data->gfx->contextSettings.antiAliasingLevel = 8;
				this->state_Data->gfx->contextSettings.antiAliasingLevel = this->dropDownList["AntiAnialising"]->getActiveId() * 2;
				this->state_Data->gfx->fullScreen = false;
				this->state_Data->window->setVerticalSyncEnabled(this->state_Data->gfx->verticleSync); this->state_Data->window->create(this->state_Data->gfx->resolution,
				this->state_Data->gfx->title, sf::State::Windowed, this->state_Data->gfx->contextSettings);
			}
			
			std::cout << "Out\n";
			State::SettingStateupdated = true;
			State::MainMenuStateUpdated = true;
		}
	}

}

void SettingState::updateDropDownList()
{

	for (auto& it : dropDownList) {

		it.second->update(this->mousePosWin);

	}

}

void SettingState::updatePositions()
{

	std::cout << "Inside";
	this->background.setSize(static_cast<sf::Vector2f>(this->state_Data->window->getSize()));
	this->textOptions->setCharacterSize(this->characterSize(30));
	this->textOptions->setPosition({ this->p2pX(600), this->p2pY(350) });
	this->buttons["EXIT_STATE"]->updatePositions(this->p2pX(1250), this->p2pY(930), this->p2pX(200), this->p2pY(60),this->characterSize(35));
	this->buttons["APPLY"]->updatePositions(this->p2pX(1090), this->p2pY(930), this->p2pX(200), this->p2pY(60), this->characterSize(35));
    this->dropDownList["Resolution"]->updatePositions(this->p2pX(1150.0), this->p2pY(370.0), this->p2pX(300.0), this->p2pY(40.0), this->characterSize(30));
	this->dropDownList["FullScreen"]->updatePositions(this->p2pX(1150.0), this->p2pY(485.0), this->p2pX(150.0), this->p2pY(30.0), this->characterSize(30));
	this->dropDownList["Vsync"]->updatePositions(this->p2pX(1150.0), this->p2pY(605.0), this->p2pX(150.0), this->p2pY(30.0), this->characterSize(30));
	this->dropDownList["AntiAnialising"]->updatePositions(this->p2pX(1150.0), this->p2pY(725.0), this->p2pX(150.0), this->p2pY(30.0), this->characterSize(30));


	State::SettingStateupdated = false;

}

void SettingState::update(const float& dt)
{

	this->updateInput(dt);
	this->updateMousePositions();
	this->updateButtons();
	if (State::SettingStateupdated)
		this->updatePositions();
	this->updateDropDownList();

}

void SettingState::renderButtons(sf::RenderTarget& target)
{

	for (auto& it : buttons) {
		if (it.first == "APPLY") {
			if (gui::DropDownList::getChange()) {
				it.second->render(target);
			}
		}
		else it.second->render(target);
	}
}

void SettingState::renderDropDownList(sf::RenderTarget& target)
{

	for (auto& it : dropDownList) {

		it.second->render(target);

	}

}

void SettingState::render(sf::RenderTarget& target)
{

	target.draw(this->background);
	this->renderButtons(target);
	target.draw(*this->textOptions);
	this->renderDropDownList(target);

}
