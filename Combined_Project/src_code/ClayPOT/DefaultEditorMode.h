#pragma once

#include "EditorMode.h"
#include "Gui.h"

class State;
class StateData;
class EditorMode;
class TileMap;
class Tile;
class gui::TextureSelecter;

class DefaultEditorMode :
	public EditorMode
{
private:

	//Map Mouse
	sf::Text* cursorText;

	//Texture selector tile adder
	sf::RectangleShape selectorRect;
	gui::TextureSelecter* textureSelector;
	sf::IntRect textureRect;

	//Tiles Data
	float cameraSpeed;
	bool collision;
	short type;
	int layer;


	void initVariables();
	void initCursorText();
	void initGui();
	void initButtons();

public:
	DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
	virtual ~DefaultEditorMode();


	void updateGui(const float& dt);
	void updateButtons();
	void updateMouseInput();
	void updateTile();
	void updateTileData();
	void updateView(const float& dt);
	void updateKeyBoardInput(const float& dt);
	void updateInput(const float& dt);
	void update(const float& dt);


	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};
