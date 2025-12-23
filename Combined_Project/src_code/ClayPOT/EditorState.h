#pragma once
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorModes.h"
#include "MainMenuState.h"
#include "SoundLibrary.h"

class State;
class StateData;
class Gui;
class PauseMenu;
class TileMap;
class Tile;
class EditorMode;
class DefaultEditorMode;
class EnemyEditorMode;
class EditorStateData;
class gui::DialogBox;
class gui::FileLoader;
class MainMenuState;

enum EditorModes { DEFAULT_EDITOR_MODE = 0, ENEMY_EDITOR_MODE };


class EditorState :
	public State
{

private:
	//Side Panel:
	sf::RectangleShape sidePanel;
	gui::Button* mapEditorButton;
	gui::Button* playerEditorButton;



	//Menu Bar stuff:
	sf::RectangleShape menuBar;
	gui::Button* file;
	gui::Button* New;
	gui::Button* Open;
	gui::Button* Save;
	bool isFileButtonActive;
	bool isNewDialogOpen;
	bool isOpenDialogOpen;
	sf::RectangleShape dropDownBox;
	bool isMapSaved = false;
	gui::Button* playButton;


	//Diaglog Box:
	gui::DialogBox* newDialogBox;
	gui::FileLoader* mapLoader;


	//Variables:
	sf::View view;
	sf::Font font;
	sf::Text* cursorText;
	std::map<std::string, gui::Button*> buttons;
	PauseMenu* pauseMenu;
	TileMap* tileMap;


	//EditorModes Stuff:
	EditorStateData editorStateData;
	std::vector<EditorMode*> modes;
	unsigned activeMode;


	sf::IntRect textureRect;
	sf::RectangleShape selectorRext;
	gui::TextureSelecter* textureSelecter;

	bool collision;
	short type;
	float cameraSpeed;
	int layer;

	//Initializers Functions:
	void initVariables();
	void initMenuBar();
	void initDialogBox();
	void initSidePanel();
	void initEditorStateData();
	void initView();
	void initFonts();
	void initButtons();
	void initKeyBinds();
	void initPauseMenu();
	void initTileMap(unsigned worldSizeX, unsigned worldSizeY, const std::string path);
	void initTileMap(const std::string path);
	void initGUI();
	void initModes();
	void initPlayButton();



public:



	EditorState(StateData* state_Data);
	~EditorState();




	//Funtions:
	void updateButtons();
	void updateNewDialogBox();
	void updateOpenDialogBox();
	void checkForMapData();
	void loadMapFromPath();
	void handleEvent(const sf::Event& event);
	void updateSaveButton();
	void updateDropDownBox();
	void updateFileButton();
	void updateInput(const float& dt);
	void updateModes(const float& dt);
	void updateSidePanel();
	void updatePlayButton();
	void update(const float& dt);



	void renderButtons(sf::RenderTarget& target);
	void renderModes(sf::RenderTarget& target);
	void renderDropDownBox(sf::RenderTarget& target);
	void renderMenuBar(sf::RenderTarget& target);
	void renderSidePanel(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);



};
