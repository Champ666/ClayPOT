#include "stdafx.h"
#include "TileMap.h"



//Initializers:
void TileMap::initializeVar(sf::Vector2f girdsize, unsigned width, unsigned height, std::string textureFile)
{
	this->textureFile = textureFile;
	this->gridSizeF = girdsize;
	this->gridSizeU = static_cast<sf::Vector2i>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->worldSize.x = static_cast<float>((this->maxSize.x) * gridSizeF.x);
	this->worldSize.y = static_cast<float>((this->maxSize.y) * gridSizeF.y);
	this->registeredWorldSize = sf::Vector2f({ 0,0 });
	this->layers = 1;
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;
}

void TileMap::remove()
{

	if (!this->map.empty()) {
		for (size_t x = 0; x < this->map.size(); ++x) {

			for (size_t y = 0; y < this->map[x].size(); ++y) {

				for (size_t z = 0; z < this->map[x][y].size(); ++z) {

					for (size_t k = 0; k < this->map[x][y][z].size(); k++) {
						if (this->map[x][y][z][k]) {
							delete this->map[x][y][z][k];
							this->map[x][y][z][k] = nullptr;
						}
					}
					this->map[x][y][z].clear();
				}
				this->map[x][y].clear();
			}

			this->map[x].clear();
		}

		this->map.clear();

	}
	

}

void TileMap::initializeMAP()
{

	this->map.resize(this->maxSize.x, std::vector < std::vector < std::vector< Tile* > > >());
	for (size_t x = 0; x < this->maxSize.x; ++x) {

		for (size_t y = 0; y < this->maxSize.y; ++y) {

			this->map[x].resize(this->maxSize.y, std::vector < std::vector< Tile* > >());

			for (size_t z = 0; z < this->layers; ++z) {

				this->map[x][y].resize(this->layers, std::vector < Tile* >() );

			}

		}

	}

	if (!this->textureSheet.loadFromFile(this->textureFile))
		std::cerr << "ERROR::TILEMAP::FAILED TO LOAD::" << this->textureFile << "\n";
	
	this->collisionBox.setSize({ this->gridSizeF.x, this->gridSizeF.y });
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);

}

TileMap::TileMap(sf::Vector2f girdsize, unsigned width, unsigned height, std::string textureFile)
{

	this->initializeVar(girdsize, width, height, textureFile);
	this->initializeMAP();
	

}

TileMap::TileMap(const std::string file_name)
{
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->loadFromFile(file_name);
	

	this->collisionBox.setSize({ this->gridSizeF.x, this->gridSizeF.y });
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{

	this->remove();

}





//Update Functions:
void TileMap::updateBoundaryCollision(Entity* entity)
{

	if (entity->getPosition().x < 0.f) {
		entity->setPosition(0.f, entity->getPosition().y);
	}
	if (entity->getPosition().y < 0.f) {
		entity->setPosition(entity->getPosition().x, 0.f);
	}
	if (entity->getPosition().x + entity->getGloabalBounds().size.x > this->worldSize.x) {
		entity->setPosition(this->worldSize.x - entity->getGloabalBounds().size.x, entity->getPosition().y);
	}
	if (entity->getPosition().y + entity->getGloabalBounds().size.y > this->worldSize.y) {
		entity->setPosition(entity->getPosition().x, this->worldSize.y - entity->getGloabalBounds().size.y);
	}
}

void TileMap::updateTileCollision(Entity* entity, const float& dt)
{

	this->fromX = (entity->getPosition().x / this->gridSizeU.x) - 1;
	this->fromY = (entity->getPosition().y / this->gridSizeU.y) - 1;


	this->toX = (entity->getPosition().x / this->gridSizeU.x) + 3;
	this->toY = (entity->getPosition().y / this->gridSizeU.y) + 3;

	if (this->fromX < 0) {
		this->fromX = 0;
	}
	else if (this->fromX >= this->maxSize.x) {
		this->fromX = this->maxSize.x;
	}
	if (this->fromY < 0) {
		this->fromY = 0;
	}
	else if (this->fromY >= this->maxSize.y) {
		this->fromY = this->maxSize.y;
	}

	if (this->toX < 0) {
		this->toX = 0;
	}
	else if (this->toX >= this->maxSize.x) {
		this->toX = this->maxSize.x;
	}
	if (this->toY < 0) {
		this->toY = 0;
	}
	else if (this->toY >= this->maxSize.y) {
		this->toY = this->maxSize.y;
	}

	for (size_t x = fromX; x < this->toX; ++x) {

		for (size_t y = fromY; y < this->toY; ++y) {

			for (size_t k = 0; k < this->map[x][y][layer].size(); ++k) {

				if (map[x][y][layer][k] != nullptr) {

					map[x][y][layer][k]->update();
					sf::FloatRect playerBounds = entity->getGloabalBounds();
					sf::FloatRect wallBounds = this->map[x][y][layer][k]->getGlobalBounds();
					sf::FloatRect nextPosition = entity->getNextPositionBounds(dt);

					if (this->map[x][y][layer][k]->intersects(nextPosition) && this->map[x][y][layer][k]->getCollision()) {

						float overlapLeft = (playerBounds.position.x + playerBounds.size.x) - wallBounds.position.x;
						float overlapRight = (wallBounds.position.x + wallBounds.size.x) - playerBounds.position.x;
						float overlapTop = (playerBounds.position.y + playerBounds.size.y) - wallBounds.position.y;
						float overlapBottom = (wallBounds.position.y + wallBounds.size.y) - playerBounds.position.y;

						bool hasHorizontalOverlap = (playerBounds.position.x < wallBounds.position.x + wallBounds.size.x) &&
							(playerBounds.position.x + playerBounds.size.x > wallBounds.position.x);
						bool hasVerticalOverlap = (playerBounds.position.y < wallBounds.position.y + wallBounds.size.y) &&
							(playerBounds.position.y + playerBounds.size.y > wallBounds.position.y);

						// Determine collision direction based on smallest overlap
						if (hasHorizontalOverlap && hasVerticalOverlap) {
							if (overlapTop > 0 && overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight) {
								// Bottom Collision - player is above the wall and moving down
								entity->setVelocityY(); // Reset Y velocity to stop downward movement
								entity->setPositionY(wallBounds.position.y - playerBounds.size.y);
							}
							else if (overlapBottom > 0 && overlapBottom < overlapTop && overlapBottom < overlapLeft && overlapBottom < overlapRight) {
								// Top Collision - player is below the wall and moving up
								entity->setVelocityY(); // Reset Y velocity to stop upward movement
								entity->setPositionY(wallBounds.position.y + wallBounds.size.y);
							}
							else if (overlapLeft > 0 && overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom) {
								// Right Collision - player is to the left of wall and moving right
								entity->setVelocityX(); // Reset X velocity to stop rightward movement
								entity->setPositionX(wallBounds.position.x - playerBounds.size.x);
							}
							else if (overlapRight > 0 && overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom) {
								// Left Collision - player is to the right of wall and moving left
								entity->setVelocityX(); // Reset X velocity to stop leftward movement
								entity->setPositionX(wallBounds.position.x + wallBounds.size.x);
							}
						}

					}
				}

			}
				
		}

	}
}

void TileMap::updateCollision(Entity* entity, const float& dt)
{

	updateBoundaryCollision(entity);
	updateTileCollision(entity, dt);

}

void TileMap::update(const float& dt, Entity* entity)
{
	this->updateCollision(entity, dt);

}


void TileMap::renderDeferredTiles(sf::RenderTarget& target)
{

	while (!this->deferredRenderTiles.empty()) {
		this->deferredRenderTiles.top()->render(target);
		deferredRenderTiles.pop();
	}

}

//Render Functions:
void TileMap::render(sf::RenderTarget& target, sf::Vector2i& resolution, Entity* entity, const bool show_collsion, sf::Vector2f* mousepos)
{

	if (entity) {
		this->fromX = std::floor(((resolution.x))) - 15;
		this->fromY = std::floor(((resolution.y))) - 9;


		this->toX = std::floor(((resolution.x ) )) + 16;
		this->toY = std::floor(((resolution.y ) )) + 10;

		if (this->fromX < 0) {
			this->fromX = 0;
		}
		else if (this->fromX >= this->maxSize.x) {
			this->fromX = this->maxSize.x;
		}
		if (this->fromY < 0) {
			this->fromY = 0;
		}
		else if (this->fromY >= this->maxSize.y) {
			this->fromY = this->maxSize.y;
		}

		if (this->toX < 0) {
			this->toX = 0;
		}
		else if (this->toX >= this->maxSize.x) {
			this->toX = this->maxSize.x;
		}
		if (this->toY < 0) {
			this->toY = 0;
		}
		else if (this->toY >= this->maxSize.y) {
			this->toY = this->maxSize.y;
		}


		for (size_t x = fromX; x < this->toX; ++x) {

			for (size_t y = fromY; y < this->toY; ++y) {

				for (size_t k = 0; k < map[x][y][layer].size(); ++k) {

					if (map[x][y][layer][k] != nullptr) {
						if (this->map[x][y][layer][k]->getType() == TileTypes::TOP) {
							this->deferredRenderTiles.push(this->map[x][y][layer][k]);
						}
						else {
							map[x][y][layer][k]->render(target);
						}
						if (show_collsion) {
							if (map[x][y][layer][k]->getCollision()) {
								this->collisionBox.setPosition(map[x][y][layer][k]->getPosition());
								target.draw(this->collisionBox);
							}
						}
						
					}

				}

			}

		}
	}
	else {

		this->fromX = (mousepos->x / this->gridSizeU.x) - std::floor(((resolution.x))) - 1;
		this->fromY = (mousepos->y / this->gridSizeU.y) - std::floor(((resolution.y))) - 1;


		this->toX = (mousepos->x / this->gridSizeU.x) + std::floor(((resolution.x ))) + 1;
		this->toY = (mousepos->y / this->gridSizeU.y) + std::floor(((resolution.y ))) + 1;

		if (this->fromX < 0) {
			this->fromX = 0;
		}
		else if (this->fromX >= this->maxSize.x) {
			this->fromX = this->maxSize.x;
		}
		if (this->fromY < 0) {
			this->fromY = 0;
		}
		else if (this->fromY >= this->maxSize.y) {
			this->fromY = this->maxSize.y;
		}

		if (this->toX < 0) {
			this->toX = 0;
		}
		else if (this->toX >= this->maxSize.x) {
			this->toX = this->maxSize.x;
		}
		if (this->toY < 0) {
			this->toY = 0;
		}
		else if (this->toY >= this->maxSize.y) {
			this->toY = this->maxSize.y;
		}


		for (size_t x = fromX; x < this->toX; ++x) {

			for (size_t y = fromY; y < this->toY; ++y) {

				for (size_t k = 0; k < map[x][y][layer].size(); ++k) {

					if (map[x][y][layer][k] != nullptr) {
						
						map[x][y][layer][k]->render(target);

							if (map[x][y][layer][k]->getCollision()) {
								this->collisionBox.setPosition(map[x][y][layer][k]->getPosition());
								target.draw(this->collisionBox);
							}

					}

				}

			}

		}

	}

		
}




std::vector< std::vector < std::vector < std::vector < Tile* > > > > TileMap::getMap()
{
	return this->map;
}

std::vector<std::vector<int>>& TileMap::getGraph()
{
	return this->graphNodes;
}

int TileMap::toIndex(int x, int y)
{
	return y * this->maxSize.x + x;
}

void TileMap::initializeGraphNodes()
{

	this->graphNodes.resize(this->maxSize.x * this->maxSize.y, std::vector<int>());

	for (size_t x = 0; x < this->maxSize.x; ++x) {

		for (size_t y = 0; y < this->maxSize.y; ++y) {

			for (size_t z = 0; z < this->layers; ++z) {
				if (!this->map[x][y][z].empty()) {
					if (!this->map[x][y][z].back()->getCollision()) {

						int u = this->toIndex(x, y);

						if (x == 0 && y == 0) {
							if (!this->map[x + 1][y][z].empty()) {
								if (!this->map[x + 1][y][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x + 1, y));
								}
							}
							if (!this->map[x][y + 1][z].empty()) {
								if (!this->map[x][y + 1][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x, y + 1));
								}
							}
						}

						else if (x == this->maxSize.x - 1 && y == this->maxSize.y - 1) {
							if (!this->map[x - 1][y][z].empty()) {
								if (!this->map[x - 1][y][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x - 1, y));
								}
							}
							if (!this->map[x][y - 1][z].empty()) {
								if (!this->map[x][y - 1][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x, y - 1));
								}
							}
						}

						else if (x == this->maxSize.x - 1 && y == 0) {
							if (!this->map[x - 1][y][z].empty()) {
								if (!this->map[x - 1][y][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x - 1, y));
								}
							}
							if (!this->map[x][y + 1][z].empty()) {
								if (!this->map[x][y + 1][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x, y + 1));
								}
							}
						}

						else if (x == 0 && y == this->maxSize.y - 1) {
							if (!this->map[x + 1][y][z].empty()) {
								if (!this->map[x + 1][y][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x + 1, y));
								}
							}
							if (!this->map[x][y - 1][z].empty()) {
								if (!this->map[x][y - 1][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x, y - 1));
								}
							}
						}

						else if (x == 0 && y != 0 && y != this->maxSize.y - 1) {
							if (!this->map[x + 1][y][z].empty()) {
								if (!this->map[x + 1][y][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x + 1, y));
								}
							}
							if (!this->map[x][y + 1][z].empty()) {
								if (!this->map[x][y + 1][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x, y + 1));
								}
							}
							if (!this->map[x][y - 1][z].empty()) {
								if (!this->map[x][y - 1][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x, y - 1));
								}
							}
						}

						else if (y == 0 && x != 0 && x != this->maxSize.x - 1) {
							if (!this->map[x + 1][y][z].empty()) {
								if (!this->map[x + 1][y][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x + 1, y));
								}
							}
							if (!this->map[x - 1][y][z].empty()) {
								if (!this->map[x - 1][y][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x - 1, y));
								}
							}
							if (!this->map[x][y + 1][z].empty()) {
								if (!this->map[x][y + 1][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x, y + 1));
								}
							}
						}

						else if (x == this->maxSize.x - 1 && y != this->maxSize.y - 1 && y != 0 ) {
							if (!this->map[x - 1][y][z].empty()) {
								if (!this->map[x - 1][y][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x - 1, y));
								}
							}
							if (!this->map[x][y + 1][z].empty()) {
								if (!this->map[x][y + 1][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x, y + 1));
								}
							}
							if (!this->map[x][y - 1][z].empty()) {
								if (!this->map[x][y - 1][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x, y - 1));
								}
							}
						}

						else if (y == this->maxSize.y - 1 && x != this->maxSize.x - 1 && x != 0) {
							if (!this->map[x + 1][y][z].empty()) {
								if (!this->map[x + 1][y][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x + 1, y));
								}
							}
							if (!this->map[x - 1][y][z].empty()) {
								if (!this->map[x - 1][y][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x - 1, y));
								}
							}
							if (!this->map[x][y - 1][z].empty()) {
								if (!this->map[x][y - 1][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x, y - 1));
								}
							}
						}

						else {
							if (!this->map[x + 1][y][z].empty()) {
								if (!this->map[x + 1][y][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x + 1, y));
								}
							}
							if (!this->map[x][y + 1][z].empty()) {
								if (!this->map[x][y + 1][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x, y + 1));
								}
							}
							if (!this->map[x - 1][y][z].empty()) {
								if (!this->map[x - 1][y][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x - 1, y));
								}
							}
							if (!this->map[x][y - 1][z].empty()) {
								if (!this->map[x][y - 1][z].back()->getCollision()) {
									graphNodes[u].push_back(this->toIndex(x, y - 1));
								}
							}
						}

					}
				}
			}

		}

	}

}

//Adders Removers:
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect, const bool collision, const short type)
{

	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0) {
		if (this->map[x][y][z].empty() || type != TileTypes::DEFAULT ) {
			this->map[x][y][z].push_back(new Tile(x * this->gridSizeF.x, y * this->gridSizeF.y, this->gridSizeF, this->textureSheet, textureRect, collision, type));
			std::cout << "DEBUG::ADDED TILE\n";
		}	
	}

}



void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{

	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0) {
		if (!this->map[x][y][z].empty()) {
			delete this->map[x][y][z][this->map[x][y][z].size() - 1];
			this->map[x][y][z].pop_back();
			std::cout << "DEBUG::REMOVED TILE\n";
		}
	}

}

void TileMap::saveToFile(const std::string path)
{
	/*Format:
	Size x y
	GridSize
	layers
	texture file
	Positions x y layer TextureRect x y collision type
	*/
	std::ofstream of;
	of.open(path);


	if (of.is_open()) {

		of << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU.x << "\n"
			<< this->gridSizeU.y << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (size_t x = 0; x < this->maxSize.x; ++x) {

			for (size_t y = 0; y < this->maxSize.y; ++y) {

				for (size_t z = 0; z < this->layers; ++z) {
					if (!this->map[x][y][z].empty()) {
						for (size_t k = 0; k < this->map[x][y][z].size(); ++k) {
							of << x << " " << y << " " << z << " " << this->map[x][y][z][k]->getAsString() << " ";
						}
						
					}
				}

			}

		}
	}
	else
	{
		std::cout << "TILEMAP::ERROR::CAN'T LOAD FILE::" << path << "\n";
	}

	of.close();

}

void TileMap::loadFromFile(const std::string path)
{

	std::ifstream ifs;
	ifs.open(path);

	if (ifs.is_open()) {



		//local variables to store loaded data
		std::string textureFile = "";
		sf::Vector2i gridSize = sf::Vector2i({0,0});
		unsigned layers = 0;
		sf::Vector2u size;
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;



		//Reading the saved data to load in local data
		ifs >> size.x >> size.y >> gridSize.x >> gridSize.y >> layers >> textureFile;

		std::cout << size.x << " " << size.y << " " << gridSize.x << " " << gridSize.y << " " << layers << " " << textureFile;

		//Saving Loaded data to program data
		this->textureFile = textureFile;
		this->gridSizeF = static_cast<sf::Vector2f>(gridSize); 
		this->gridSizeU = gridSize;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->worldSize.x = static_cast<float>((this->maxSize.x) * gridSizeF.x);
		this->worldSize.y = static_cast<float>((this->maxSize.y) * gridSizeF.y);
		this->layers = layers;


		//Clearing if there is something in map
		this->remove();

		//Initializing Map
		this->initializeMAP();


		////Reading the saved Map data to load in local Map data
		
		while (ifs >> x >> y >> z >> trX >> trY >> collision >> type) {

			this->map[x][y][z].push_back(new Tile(x * this->gridSizeF.x, y * this->gridSizeF.y, this->gridSizeF,
				this->textureSheet, sf::IntRect({ trX, trY }, { gridSize.x,gridSize.y }), collision, type));

		}


	}
	else
	{
		std::cout << "TILEMAP::ERROR::CAN'T LOAD FILE FROM" << path << "\n";
	}

	ifs.close();


}

const sf::Texture* TileMap::getTextureSheet() const
{
	return &this->textureSheet;
}

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < static_cast<int>(this->map.size()))
	{
		if (y >= 0 && y < static_cast<int>(this->map[x].size()))
		{
			if (layer >= 0 && layer < static_cast<int>(this->map[x][y].size()))
			{
				return this->map[x][y][layer].size();
			}
		}
	}

	return -1;
}
