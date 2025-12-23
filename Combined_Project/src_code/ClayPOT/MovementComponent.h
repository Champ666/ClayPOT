#pragma once

enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent
{


private:
	sf::Sprite& sprite;
	float maxVelocity;
	sf::Vector2f velocity;
	float acceleration;
	float decceleration;


	//Initializers:



public:

	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	~MovementComponent();


	//Accessors:
	const sf::Vector2f& getVelocity() const;
	const float& getMaxVelocity() const;

	//Modifier
	void setVelocity();
	void setVelocityX();
	void setVelocityY();

	//Funtions:
	const bool getState(const unsigned short state) const;
	void update(const float& dt);
	bool isIdle() const;
	void move(float dir_x, float dir_y, const float& dt);

};

