#pragma once
#include "Entity.h"


class Player : public Entity
{

private:
	//Attack Variables:
	Sword sword;

	//Timer
	float timer = 0.f;
	float timerMax = 0.5f;
	bool tick = true;

	//Initializers:
	void initVariables(float x, float y, float width, float height);
	void initAnimations();
	void initComponents(sf::Texture&);


public:
	Player(float x, float y, float width, float height, sf::Texture& texture);
	~Player();

	//Getter
	AttributeComponent* getAttributeComponent();
	const sf::Vector2f& getSpritePos() const;

    //Functions:
	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool show_hitbox = false);
	void updateWeaponPos(sf::Vector2f& mousePos);
	void updateTimer(const float& dt);
	virtual void update(const float& dt, sf::Vector2f& mousePos);
	void checkPos(float x_pos);
	void isAttacking(bool);

};

