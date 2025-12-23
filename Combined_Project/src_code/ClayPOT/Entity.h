#pragma once

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"
#include "Sword.h"
#include "SoundLibrary.h"


class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class AttributeComponent;
class SkillComponent;
class Sword;

class Entity
{

private:

	void initVariables();
	

protected:
	//Attack var
	bool attack;
	bool markedForRemoval = false;

	sf::Sprite sprite;
	

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;
	SkillComponent* skillComponent;
	

public:
	//Constructors and Destructors
	Entity(sf::Texture& texture);
	virtual ~Entity();

	//Components funs:
	void createMovementComponent(const float maxSpeed, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(float x_pos, float y_pos, int width, int height);
	void createAttributeComponent(const unsigned level);
	void createSkillComponent();

	//Accessors
	const sf::Vector2f& getPosition()const;
	const sf::Vector2f& getSpritePosition()const;
	const sf::FloatRect getGloabalBounds()const;
	virtual const sf::FloatRect& getNextPositionBounds(const float& dt) const;
	const int getIndex(sf::Vector2i pos);
	const int getNodeIndex(const int gridSizeI = 64);
	const sf::Vector2i getGridPosition(const int gridSizeI = 64) const;
	const sf::Vector2f getCenter();
	virtual const int getId();


	//Modifier:
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);
	virtual void setPosition(float x, float y);
	virtual void setSize(float width, float height);
	virtual void setVelocity();
	virtual void setVelocityX();
	virtual void setVelocityY();

	//functions
	void move(const float& dt, float dir_x, float dir_y);
	void updateAnimations(const float& dt);
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool render_Hitbox = false) = 0;
	
	virtual void update(const float& dt, sf::Vector2f& mousePos) = 0;
	bool isDead();
	virtual void markForRemoval();
	virtual bool isMarkedForRemoval() const;
	

};

