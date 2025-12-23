#include "stdafx.h"
#include "HitboxComponent.h"



HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, int width, int height) : sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{

	this->hitbox.setSize({ float(width), float(height) });
	this->hitbox.setPosition({ this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y });
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.0f);
	this->hitbox.setOutlineColor(sf::Color::Green);
	this->nextPosition = sf::FloatRect({ 0.f,0.f }, { static_cast<float>(width),static_cast<float>(height)});

}

HitboxComponent::~HitboxComponent()
{

}

const sf::Vector2f& HitboxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

void HitboxComponent::setPositionX(float x)
{
	this->hitbox.setPosition({ x, this->hitbox.getGlobalBounds().position.y });
}

void HitboxComponent::setPositionY(float y)
{
	this->hitbox.setPosition({ this->hitbox.getGlobalBounds().position.x ,y });
}

void HitboxComponent::setPosition(float x, float y)
{
	this->hitbox.setPosition({ x , y});
	this->sprite.setPosition({ x - this->offsetX ,y - this->offsetY });
}

const sf::FloatRect& HitboxComponent::getNextPosition(const sf::Vector2f& velocity)
{
	this->nextPosition.position.x = this->hitbox.getPosition().x + velocity.x;
	this->nextPosition.position.y = this->hitbox.getPosition().y + velocity.y;
	return this->nextPosition;
}

bool HitboxComponent::checkCollision(const sf::FloatRect& frect)
{
	if (this->hitbox.getGlobalBounds().findIntersection(frect)) {
		return true;
	}

	return false;
}

void HitboxComponent::update()
{

	this->hitbox.setPosition({ this->sprite.getPosition().x + offsetX, this->sprite.getPosition().y + offsetY});

}

void HitboxComponent::render(sf::RenderTarget& target)
{

	//target.draw(this->hitbox);

}
