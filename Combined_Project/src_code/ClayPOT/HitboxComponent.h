#pragma once


class HitboxComponent
{

private:

	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

public:

	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, int width, int hieght);
	~HitboxComponent();


	//Functions:
	//Accessor
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	//Modifier
	void setPositionX(float x);
	void setPositionY(float y);
	void setPosition(float x, float y);
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	//Updates:
	bool checkCollision(const sf::FloatRect& frect);
	void update();
	void render(sf::RenderTarget& target);

};

