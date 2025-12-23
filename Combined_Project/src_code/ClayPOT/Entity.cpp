#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{

	this->hitboxComponent = nullptr;
	this->movementComponent = nullptr;

}

Entity::Entity(sf::Texture& texture) : sprite(texture)
{

	std::cout << "Into Entity text\n";
	//this->sprite->setTexture(texture);
	initVariables();

}

Entity::~Entity()
{

	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->attributeComponent;
	delete this->skillComponent;

}

void Entity::createMovementComponent(const float maxSpeed, const float acceleration, const float deceleration)
{

	this->movementComponent = new MovementComponent(this->sprite, maxSpeed, acceleration, deceleration);

}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{

	animationComponent = new AnimationComponent(this->sprite, texture_sheet);

}

void Entity::createHitboxComponent(float x_pos, float y_pos, int width, int height)
{

	this->hitboxComponent = new HitboxComponent(this->sprite, x_pos, y_pos, width, height);

}

void Entity::createAttributeComponent(const unsigned level)
{
	this->attributeComponent = new AttributeComponent(level);
}

void Entity::createSkillComponent()
{
	this->skillComponent = new SkillComponent();
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	return this->sprite.getPosition();
}

const sf::Vector2f& Entity::getSpritePosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Entity::getGloabalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect& Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitboxComponent && this->movementComponent) {
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
	}
	return sf::FloatRect();
}

const int Entity::getIndex(sf::Vector2i pos)
{
	return pos.y * 20 + pos.x;
}


const int Entity::getNodeIndex(const int gridSizeI /*= 64*/)
{

	sf::Vector2i gridPos;
	if (this->hitboxComponent)
		gridPos = sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI
		);

	else {
		gridPos = sf::Vector2i(
			static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
			static_cast<int>(this->sprite.getPosition().y) / gridSizeI
		);
	}
	
	return this->getIndex(gridPos);
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	if (this->hitboxComponent)
		return sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI
		);

	return sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI
	);
}


const sf::Vector2f Entity::getCenter()
{
	return
		this->sprite.getPosition() +
		sf::Vector2f
		(
			this->sprite.getGlobalBounds().size.x / 2.f + 15,
			this->sprite.getGlobalBounds().size.y / 2.f + 10
		);
}

const int Entity::getId()
{
	//implementation in AIPLayer.cpp
	return 1;
}

void Entity::setPositionX(float x)
{
	this->hitboxComponent->setPositionX(x);
	this->sprite.setPosition({ x - 17.f , this->sprite.getPosition().y });
}

void Entity::setPositionY(float y)
{
	this->hitboxComponent->setPositionY(y);
	this->sprite.setPosition({ this->sprite.getPosition().x, y - 55.f});
}

void Entity::setPosition(float x, float y)
{
	if (this->hitboxComponent) {
		this->hitboxComponent->setPosition(x, y);
		return;
	}
	this->sprite.setPosition({ x, y });
}

void Entity::setSize(float width, float height)
{

	//this->sprite.setScale({ width, height });

}


void Entity::setVelocity()
{
	this->movementComponent->setVelocity();
}

void Entity::setVelocityX()
{
	this->movementComponent->setVelocityX();
}

void Entity::setVelocityY()
{
	this->movementComponent->setVelocityY();
}

void Entity::move(const float& dt, float dir_x, float dir_y)
{
	if(this->movementComponent){
		this->movementComponent->move(dir_x, dir_y, dt);
	}
	if (this->attributeComponent) {
		
	}
	if (this->skillComponent) {
		this->skillComponent->gainExp(SKILLS::MELEE_COMBAT, 1);
	}
}


void Entity::updateAnimations(const float& dt)
{

	if (this->attack) {
		this->attack = this->animationComponent->play("ATTACK", dt);
	}
	if (this->movementComponent->getState(IDLE)) {
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT)) {
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT)) {
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP)) {
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN)) {
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}

}


bool Entity::isDead()
{
	if (this->attributeComponent) {
		if (this->attributeComponent->hp <= 0) {
			return true;
		}
		return false;
	}
	return false;
}

void Entity::markForRemoval()
{
	//implementation in AIPlayer.cpp
}

bool Entity::isMarkedForRemoval() const
{
	//implementation in AIPlayer.cpp
	return false;
}

