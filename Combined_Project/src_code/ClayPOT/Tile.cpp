#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = DEFAULT;
}

Tile::Tile(float x, float y, sf::Vector2f gridSize, const sf::Texture& texture, const sf::IntRect& textureRect, bool collision, short type)
{

	this->shape.setSize({ gridSize.x, gridSize.y });
	this->shape.setPosition({ x,y });
	this->shape.setFillColor(sf::Color::White);
	this->shape.setTexture(&texture);
	/*this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(sf::Color::Black);*/
	this->shape.setTextureRect(textureRect);
	this->collision = collision;
	this->type = type;

}

Tile::~Tile()
{



}

const sf::FloatRect& Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

const short& Tile::getType() const
{
	return this->type;
}

const bool& Tile::getCollision()
{
	return this->collision;
}

bool Tile::intersects(const sf::FloatRect& bounds)
{
	if (this->shape.getGlobalBounds().findIntersection(bounds))
		return true;
	return false;
}

const sf::Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

const std::string Tile::getAsString() const
{

	std::stringstream ss;

	ss << this->shape.getTextureRect().position.x << " " << this->shape.getTextureRect().position.y << " " << this->collision << " " << this->type;

	return ss.str();
}

void Tile::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if(shader)
		target.draw(this->shape, shader);
	else
		target.draw(this->shape);
}

void Tile::update()
{
	//this->shape.setFillColor(sf::Color::Red);
}
