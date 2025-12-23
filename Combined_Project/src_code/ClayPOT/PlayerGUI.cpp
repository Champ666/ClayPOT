#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	if (!this->font.openFromFile("Resources/Fonts/Roboto-Regular.ttf")) {
		std::cout << "\nPLAYERGUI::ERROR IN LOaDING FILE FROM Resources/Fonts/Roboto-Regular.ttf\n";
	}
}

void PlayerGUI::initLevelBox(State* state)
{
	this->levelText = new sf::Text(this->font);
	this->levelBox.setSize(sf::Vector2f({ state->p2pX(55.f), state->p2pY(55.f) }));
	this->levelBox.setFillColor(sf::Color(255, 255, 255, 20));
	this->levelBox.setPosition({ state->p2pX(415.f), state->p2pX(960.f) });

	this->levelText->setString("0");
	this->levelText->setPosition({ this->levelBox.getPosition().x + 24 , this->levelBox.getPosition().y + 10 });
	this->levelText->setCharacterSize(state->characterSize(40));
	this->levelText->setOrigin({ this->levelText->getGlobalBounds().size.x / 2 ,this->levelText->getGlobalBounds().size.x / 2 });

	this->is = true;
}

void PlayerGUI::initHpBar(State* state)
{

	this->hpBar = new gui::ProgressBar(480.f, 985.f, 960.f, 30.f, sf::Color(200, 0, 0, 200), state->state_Data->gfx->resolution);
	
}

void PlayerGUI::initEXPBar(State* state)
{

	this->expBar = new gui::ProgressBar(480.f, 960.f, 400.f, 20.f, sf::Color(0, 0, 250, 200), state->state_Data->gfx->resolution);
	
}


PlayerGUI::PlayerGUI(Player* player, State* state)
{
	this->player = player;
	this->initFont();
	this->initHpBar(state);
	this->initEXPBar(state);
	this->initLevelBox(state);

}

PlayerGUI::~PlayerGUI()
{
	delete this->levelText;
	delete this->expBar;
	delete this->hpBar;
}

void PlayerGUI::updateHPBar()
{
	
	this->hpBar->update(this->player->getAttributeComponent()->hp, this->player->getAttributeComponent()->hpMax);
	
}

void PlayerGUI::updateEXPBar()
{

	this->expBar->update(this->player->getAttributeComponent()->exp, this->player->getAttributeComponent()->expNext);
	
}


void PlayerGUI::updateLevel()
{
	if (this->player->getAttributeComponent()->level < 10 || !this->is) {
		this->currentLevel = std::to_string(this->player->getAttributeComponent()->level);
		this->levelText->setString(this->currentLevel);
	}
	else {
		if (is) {
			is = false;
			this->levelText->setPosition({ this->levelBox.getPosition().x + 13 , this->levelBox.getPosition().y + 10 });
		}
	}
}


void PlayerGUI::update(const float& dt)
{
	this->updateHPBar();
	this->updateEXPBar();
	this->updateLevel();
}


void PlayerGUI::renderLevelBox(sf::RenderTarget& target)
{
	target.draw(*this->levelText);
	target.draw(this->levelBox);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->hpBar->render(target);
	this->expBar->render(target);
	this->renderLevelBox(target);
}
