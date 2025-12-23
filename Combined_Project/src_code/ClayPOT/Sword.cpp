#include "stdafx.h"
#include "Sword.h"

void Sword::initSword()
{
	if (!this->weapon_Texture.loadFromFile("Resources/item/sword.png")) {
		std::cout << "\nPLAYER.CPP::FALIED TO LOAD WEAPON";
	}
	this->weapon_Sprite = new sf::Sprite(this->weapon_Texture);
	this->weapon_Sprite->setOrigin({ this->weapon_Sprite->getGlobalBounds().size.x / 2.f,this->weapon_Sprite->getGlobalBounds().size.y });
}


Sword::Sword()
{
	this->initSword();
}

Sword::~Sword()
{
	
}

void Sword::update(sf::Vector2f mousePosView, const sf::Vector2f center)
{
	this->weapon_Sprite->setPosition(center);
	float dX = mousePosView.x - this->weapon_Sprite->getPosition().x;
	float dY = mousePosView.y - this->weapon_Sprite->getPosition().y;

	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->weapon_Sprite->setRotation(sf::Angle(sf::degrees(deg + 90)));
}

void Sword::render(sf::RenderTarget& target)
{
	target.draw(*this->weapon_Sprite);
}
