#pragma once

enum TileTypes{DEFAULT = 0, TOP, FRONT, SHADOW, ENEMYSPAWNER};

class Tile

{

private:


protected:
	sf::RectangleShape shape;
	bool collision;
	short type;

public:

	Tile();
	Tile(float x, float y, sf::Vector2f gridSize, const sf::Texture& texture, const sf::IntRect& textureRect,
	     bool collision = false, short type = DEFAULT 
	);
	~Tile();

	//Accessor
	const sf::FloatRect& getGlobalBounds() const;
	const short& getType() const;


	//Functions:
	const bool& getCollision();
	bool intersects(const sf::FloatRect& bounds);
	const sf::Vector2f& getPosition() const;
	const std::string getAsString() const;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);
	virtual void update();

};

