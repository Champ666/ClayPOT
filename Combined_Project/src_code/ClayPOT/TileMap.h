#pragma once
#include"Tile.h"
#include "Entity.h"

class Entity;



class TileMap
{
private:

	//Map stuff
public:
	sf::Vector2f gridSizeF;
	sf::Vector2i gridSizeU;
	sf::Vector2u maxSize;
	sf::Vector2f worldSize;
	sf::Vector2f registeredWorldSize;
	unsigned layers;
	int layer;

private:
	std::vector< std::vector < std::vector < std::vector < Tile* > > > > map;
	std::string textureFile;
	sf::Texture textureSheet;
	std::stack<Tile* > deferredRenderTiles;
	std::vector<std::vector<int>> graphNodes;

	//Collision Stuff:
	sf::RectangleShape collisionBox;
	int fromX;
	int toX;
	int fromY;
	int toY;
	


public:

	TileMap(sf::Vector2f girdsize, unsigned width, unsigned height, std::string textureFile);
	TileMap(const std::string file_name);
	~TileMap();

	//EngineFunctions:
	void updateBoundaryCollision(Entity* entity);
	void updateTileCollision(Entity* entity, const float& dt);
	void updateCollision(Entity* entity, const float& dt);
	void update(const float& dt, Entity* entity);
	void renderDeferredTiles(sf::RenderTarget& target);
	void render(sf::RenderTarget& target, sf::Vector2i& resolution, Entity* entity = nullptr, const bool show_collsion = false, sf::Vector2f* mousepos = nullptr);
	
	//Getter
	std::vector< std::vector < std::vector < std::vector < Tile* > > > > getMap();
	std::vector<std::vector<int>>& getGraph();

	//Editor Functions:
	int toIndex(int x, int y);
	void initializeGraphNodes();
	void initializeVar(sf::Vector2f girdsize, unsigned width, unsigned height, std::string textureFile);
	void remove();
	void initializeMAP();
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect, const bool collision, const short type);

	void removeTile(const unsigned x, const unsigned y, const unsigned z);
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);

	//Accessor:
	const sf::Texture* getTextureSheet() const;
	const int getLayerSize(const int x, const int y, const int layer) const;
	

};

