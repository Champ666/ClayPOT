#include "stdafx.h"
#include "Player.h"

void Player::initVariables(float x, float y, float width, float height)
{
	this->attack = false;
	this->setPosition(x, y);
	this->setSize(width, height);
}

void Player::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 13.f, 0, 0, 8, 0, 64, 64);

	this->animationComponent->addAnimation("WALK_DOWN", 5.f, 0, 1, 3, 1, 64, 64);

	this->animationComponent->addAnimation("WALK_LEFT", 7.f, 4, 1, 7, 1, 64, 64);

	this->animationComponent->addAnimation("WALK_RIGHT", 7.f, 8, 1, 11, 1, 64, 64);

	this->animationComponent->addAnimation("WALK_UP", 5.f, 12, 1, 15, 1, 64, 64);

	//this->animationComponent->addAnimations("ATTACK", 7.f, 0, 2, 13, 2, 192 * 2, 192);

}

void Player::initComponents(sf::Texture& texture_Sheet)
{

	this->createMovementComponent(200.f, 1500.0f, 900.f);
	this->createAnimationComponent(texture_Sheet);
	this->createHitboxComponent(17.f, 55.f, 30.f, 10.f);
	this->createAttributeComponent(1);
	this->initAnimations();
	this->createSkillComponent();

}


Player::Player(float x, float y, float width, float height, sf::Texture& texture_sheet) : Entity(texture_sheet)
{

	this->initVariables(x * 64, y * 64, width, height);
	this->initComponents(texture_sheet);
	
}

Player::~Player()
{
	
}

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}


const sf::Vector2f& Player::getSpritePos() const
{
	return this->sprite.getPosition();
}

//Fucntions:

void Player::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainExp(exp);
}


void Player::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox)
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getSpritePosition());
		target.draw(this->sprite, shader);
		this->sword.render(target);
	}
	else
		target.draw(this->sprite);

	if(!show_hitbox)
		this->hitboxComponent->render(target);
}



void Player::updateWeaponPos(sf::Vector2f& mousePos)
{
	this->sword.update(mousePos, this->getCenter());
}

void Player::updateTimer(const float& dt)
{
	if (timer < timerMax) {
		timer += dt;
		tick = false;
		return;
	}
	timer = 0.f;
	tick = true;
}

void Player::checkPos(float x_pos)
{

	if (this->sprite.getScale().x > 0.f) { //Facing left
		this->sprite.setOrigin({ x_pos , 0 });
	}
	else {
		this->sprite.setOrigin({ 258 + x_pos , 0 }); //Facing Right
	}


}

void Player::update(const float& dt, sf::Vector2f& mousePos)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::E))//For Debug purposes
		this->attributeComponent->gainExp(20);
	//system("cls");
	this->movementComponent->update(dt);
	if (!this->movementComponent->getState(IDLE)) {
		this->updateTimer(dt);
		if(this->tick)
			SoundLibrary::playSound("Footsteps");
	}
	this->hitboxComponent->update();
	this->updateWeaponPos(mousePos);
	this->updateAnimations(dt);

}


void Player::isAttacking(bool attack)
{
	//this->attack = attack;  //commented for now when attack aniamtion is avaialble uncomment this
}
