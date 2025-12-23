#include "stdafx.h"
#include "EditorState.h"

void EditorState::initVariables()
{

}

void EditorState::initMenuBar()
{
	this->menuBar.setSize({ static_cast<float>(this->state_Data->gfx->resolution.size.x), this->p2pY(40) });
	this->menuBar.setPosition({ 0,0 });
	this->menuBar.setFillColor(sf::Color(30, 30, 30));

	this->dropDownBox.setSize({ this->p2pX(120), this->p2pY(120) });
	this->dropDownBox.setPosition({ this->p2pX(40), this->p2pY(40) });
	this->dropDownBox.setFillColor(sf::Color(30, 30, 30, 200));

	this->file = new gui::Button(this->p2pX(80), this->p2pY(20), this->p2pX(60), this->p2pY(25), &this->font, "File", this->characterSize(22),
		sf::Color(58, 47, 35, 0), sf::Color(200, 140, 80, 0), sf::Color(58, 47, 35, 0),
		sf::Color(230, 230, 230, 255), sf::Color(255, 255, 255, 255), sf::Color(230, 230, 230, 255)
	);

	this->New = new gui::Button(this->p2pX(80), this->p2pY(60), this->p2pX(60), this->p2pY(25), &this->font, "New", this->characterSize(22),
		sf::Color(58, 47, 35, 0), sf::Color(200, 140, 80, 0), sf::Color(58, 47, 35, 0),
		sf::Color(230, 230, 230, 255), sf::Color(255, 255, 255, 255), sf::Color(230, 230, 230, 255)
	);
	this->Open = new gui::Button(this->p2pX(80), this->p2pY(100), this->p2pX(60), this->p2pY(25), &this->font, "Open", this->characterSize(22),
		sf::Color(58, 47, 35, 0), sf::Color(200, 140, 80, 0), sf::Color(58, 47, 35, 0),
		sf::Color(230, 230, 230, 255), sf::Color(255, 255, 255, 255), sf::Color(230, 230, 230, 255)
	);
	this->Save = new gui::Button(this->p2pX(80), this->p2pY(140), this->p2pX(60), this->p2pY(25), &this->font, "Save", this->characterSize(22),
		sf::Color(58, 47, 35, 0), sf::Color(200, 140, 80, 0), sf::Color(58, 47, 35, 0),
		sf::Color(230, 230, 230, 255), sf::Color(255, 255, 255, 255), sf::Color(230, 230, 230, 255)
	);

	this->isFileButtonActive = false;
	this->isNewDialogOpen = false;
	this->isOpenDialogOpen = false;

}

void EditorState::initDialogBox()
{
	this->newDialogBox = new gui::DialogBox(this->p2pX(670), this->p2pY(290), this->p2pX(600), this->p2pY(300), this->font, "TILE SHEET", this->characterSize(20));
	this->mapLoader = new gui::FileLoader(this->p2pX(670), this->p2pY(290), this->p2pX(600), this->p2pY(200), this->font, this->characterSize(20));
}

void EditorState::initSidePanel()
{
	this->sidePanel.setSize({ this->p2pX(400), this->p2pY(1080) - this->p2pY(40) });
	this->sidePanel.setPosition({ this->p2pX(1920) - this->sidePanel.getSize().x, this->p2pY(40) });
	this->sidePanel.setFillColor(sf::Color(30, 30, 30));
	this->sidePanel.setOutlineColor(sf::Color::White);
	this->sidePanel.setOutlineThickness(1);
	this->mapEditorButton = new gui::Button(this->sidePanel.getPosition().x + this->p2pX(80), this->p2pY(20),
		this->p2pX(100), this->p2pY(25), &this->font, "Map Editor", this->characterSize(22),
		sf::Color(58, 47, 35, 0), sf::Color(200, 140, 80, 0), sf::Color(58, 47, 35, 0),
		sf::Color(230, 230, 230, 255), sf::Color(255, 255, 255, 255), sf::Color(230, 230, 230, 255)
	);
	this->playerEditorButton = new gui::Button(this->sidePanel.getPosition().x + this->p2pX(280), this->p2pY(20),
		this->p2pX(100), this->p2pY(25), &this->font, "Player Editor", this->characterSize(22),
		sf::Color(58, 47, 35, 0), sf::Color(200, 140, 80, 0), sf::Color(58, 47, 35, 0),
		sf::Color(230, 230, 230, 255), sf::Color(255, 255, 255, 255), sf::Color(230, 230, 230, 255)
	);
}

void EditorState::initEditorStateData()
{
	this->editorStateData.view = &this->view;
	this->editorStateData.font = &this->font;
	this->editorStateData.mousePosGrid = &this->mousePosGrid;
	this->editorStateData.mousePosScreen = &this->mousePosScreen;
	this->editorStateData.mousePosView = &this->mousePosView;
	this->editorStateData.mousePosWindow = &this->mousePosWin;
}

void EditorState::initView()
{
	this->view.setSize({ static_cast<float>(this->state_Data->gfx->resolution.size.x), static_cast<float>(this->state_Data->gfx->resolution.size.y) });
	float worldCenterX = (10 * this->state_Data->gridSize.x) / 2.0f;  // 10 tiles * gridSize / 2
	float worldCenterY = (10 * this->state_Data->gridSize.y) / 2.0f;  // 10 tiles * gridSize / 2
	this->view.setCenter({ worldCenterX, worldCenterY });
}

void EditorState::initFonts()
{
	if (!this->font.openFromFile("Resources/Fonts/FeDPsc2.ttf")) {
		throw("ERROR MAIN MENUSTATE :: CAN'T LAOD FONT FROM :: Resources/Fonts/FeDPsc2.ttf");
	}
}

void EditorState::initButtons()
{

}

void EditorState::initKeyBinds()
{
	std::ifstream ifs("Config/EditorState_keybinds.ini");
	if (ifs.is_open()) {
		std::string key;
		std::string key2;
		while (ifs >> key >> key2) {
			keybinds[key] = this->state_Data->supportedKeys->at(key2);
		}
		ifs.close();
	}
}

void EditorState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->state_Data->window, this->font, 30);
	this->pauseMenu->addButtons("RESUME", this->p2pX(960), this->p2pY(300), "Resume", this->characterSize(45));
	this->pauseMenu->addButtons("QUIT", this->p2pX(960), this->p2pY(950), "Quit", this->characterSize(35));
}

void EditorState::initTileMap(unsigned worldSizeX, unsigned worldSizeY, const std::string path)
{

	this->tileMap = new TileMap(this->state_Data->gridSize, worldSizeX, worldSizeY, path);

}

void EditorState::initTileMap(const std::string path)
{
	this->tileMap = new TileMap(path);
}

void EditorState::initGUI()
{

}

void EditorState::initModes()
{
	this->modes.push_back(new DefaultEditorMode(this->state_Data, this->tileMap, &this->editorStateData));
	//this->modes.push_back(new EnemyEditorMode(this->state_Data, this->tileMap, &this->editorStateData));

	this->activeMode = EditorModes::DEFAULT_EDITOR_MODE;
}

void EditorState::initPlayButton()
{
	this->isMapSaved = false;
	this->playButton = new gui::Button(this->sidePanel.getPosition().x - this->p2pX(120), this->p2pY(8), this->p2pX(60), this->p2pY(25),
		sf::Color(220, 0, 0),    // idle → YouTube red
		sf::Color(255, 40, 40),  // hover → lighter red
		sf::Color(180, 0, 0),    // active → darker red
		0);
}

EditorState::EditorState(StateData* state_Data) : State(state_Data)
{
	this->initFonts();
	this->initMenuBar();
	this->initDialogBox();
	this->initVariables();
	this->initView();
	this->initKeyBinds();
	this->initPauseMenu();
	this->initSidePanel();
	this->initGUI();
	this->initEditorStateData();
	this->initPlayButton();
}

EditorState::~EditorState()
{
	for (auto& it : buttons) {
		delete it.second;
	}
	delete this->pauseMenu;
	if (this->tileMap) {
		delete this->tileMap;
	}
	delete this->file;
	for (size_t i = 0; i < this->modes.size(); i++) {
		delete this->modes[i];
	}
	delete this->newDialogBox;
	delete this->mapLoader;
	delete this->mapEditorButton;
	delete this->playerEditorButton;
}

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close")))) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Close")))) {
		}
		std::cout << "Paused!\n";
		this->pauseState();
	}
}

void EditorState::updateModes(const float& dt)
{
	this->modes[this->activeMode]->update(dt);
}

void EditorState::updateSidePanel()
{
	this->mapEditorButton->update(this->mousePosWin);
	this->playerEditorButton->update(this->mousePosWin);
}

void EditorState::updatePlayButton()
{
	this->playButton->update(this->mousePosWin);
	if (this->playButton->isPressed()) {
		this->state_Data->states->pop();
		this->state_Data->states->push(new MainMenuState(this->state_Data));
	}

}

void EditorState::updateButtons()
{
	if (this->pauseMenu->isButtonsPressed("QUIT")) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		}
		std::cout << "Resuming Game State";
		this->endState();
		SoundLibrary::playMusic("BackGroundMusic");
	}
	if (this->pauseMenu->isButtonsPressed("RESUME")) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		}
		std::cout << "Resuming Game State";
		this->unPauseState();
	}
	
}

void EditorState::updateNewDialogBox()
{
	this->newDialogBox->update(this->mousePosWin);
	if (this->newDialogBox->clearButton->isPressed()) {
		this->isNewDialogOpen = false;
	}
	else if (this->newDialogBox->enterButton->isPressed()) {
		this->checkForMapData();
	}
}

void EditorState::updateOpenDialogBox()
{
	this->mapLoader->update(this->mousePosWin);
	if (this->mapLoader->closeButton->isPressed()) {
		this->isOpenDialogOpen = false;
	}
	else if (this->mapLoader->enterButton->isPressed()) {
		this->loadMapFromPath();
	}
}

void EditorState::checkForMapData()
{
	bool check = true;
	std::fstream ifs(this->newDialogBox->pngPath);
	if (!ifs.is_open() || this->newDialogBox->pngPath.empty() || this->newDialogBox->pngPath == "e.g: Resource / map.png ") {
		this->newDialogBox->pngPathHolder->setInvalid();
		check = false;
	}
	else {
		ifs.close();
	}

	if (this->newDialogBox->gridSizeX <= 0) {
		this->newDialogBox->gridXHolder->setInvalid();
		check = false;
	}

	if (this->newDialogBox->gridSizeY <= 0) {
		this->newDialogBox->gridYHolder->setInvalid();
		check = false;
	}

	if (this->newDialogBox->worldSizeX <= 0) {
		this->newDialogBox->mapXHolder->setInvalid();
		check = false;
	}

	if (this->newDialogBox->worldSizeY <= 0) {
		this->newDialogBox->mapYHolder->setInvalid();
		check = false;
	}

	if (check) {
		std::cout << "All inputs valid! Creating new map with:" << std::endl;
		std::cout << "PNG Path: " << this->newDialogBox->pngPath << std::endl;
		std::cout << "Grid Size: " << this->newDialogBox->gridSizeX << "x" << this->newDialogBox->gridSizeY << std::endl;
		std::cout << "Map Size: " << this->newDialogBox->worldSizeX << "x" << this->newDialogBox->worldSizeY << std::endl;
		this->isNewDialogOpen = false;
		this->state_Data->gridSize.x = this->newDialogBox->gridSizeX;
		this->state_Data->gridSize.y = this->newDialogBox->gridSizeY;
		this->initTileMap(this->newDialogBox->worldSizeX, this->newDialogBox->worldSizeY, this->newDialogBox->pngPath);
		this->initModes();
	}
	else {
		this->newDialogBox->clearAllFields();
	}
}

void EditorState::loadMapFromPath()
{
	std::string mapPath = this->mapLoader->getMapPath();
	if (mapPath.empty() || mapPath == "e.g: Maps/level1.map") {
		this->mapLoader->pathHolder->setInvalid();
		return;
	}

	std::fstream ifs(mapPath);
	if (!ifs.is_open()) {
		this->mapLoader->pathHolder->setInvalid();
		return;
	}
	ifs.close();

	// Load the map
	std::cout << "Loading map from: " << mapPath << std::endl;
	this->initTileMap(mapPath);
	this->initModes();
	this->isOpenDialogOpen = false;
	this->isMapSaved = true;
}

void EditorState::handleEvent(const sf::Event& event)
{
	if (this->isNewDialogOpen) {
		this->newDialogBox->updateInput(this->mousePosWin, event);
		if (this->newDialogBox->enterButton->isPressed()) {
			this->checkForMapData();
		}
	}
	if (this->isOpenDialogOpen) {
		this->mapLoader->updateInput(this->mousePosWin, event);
		if (this->mapLoader->enterButton->isPressed()) {
			this->loadMapFromPath();
		}
	}
}

void EditorState::updateSaveButton()
{
	if (this->tileMap) {
		this->isMapSaved = true;
		this->tileMap->saveToFile("Resources/Map/map");
	}
}

void EditorState::updateDropDownBox()
{
	this->New->update(this->mousePosWin);
	this->Open->update(this->mousePosWin);
	this->Save->update(this->mousePosWin);
	if (this->New->isPressed()) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		}
		this->isFileButtonActive = false;
		this->isNewDialogOpen = true;
		this->newDialogBox->clearAllFields();
	}
	if (this->Open->isPressed()) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		}
		this->isFileButtonActive = false;
		this->isOpenDialogOpen = true;
		this->mapLoader->clearField();
	}
	if (this->Save->isPressed()) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		}
		this->isFileButtonActive = false;
		this->updateSaveButton();
	}
}

void EditorState::updateFileButton()
{
	if (this->file->isPressed()) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		}
		if (this->isFileButtonActive)
			this->isFileButtonActive = false;
		else
			this->isFileButtonActive = true;
	}
	if (this->isFileButtonActive) {
		this->updateDropDownBox();
	}
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateInput(dt);

	if (!this->pause) {
		if (this->isMapSaved)
			this->updatePlayButton();
		this->file->update(this->mousePosWin);
		this->updateFileButton();
		if (this->isNewDialogOpen)
			this->updateNewDialogBox();
		else if (this->isOpenDialogOpen)
			this->updateOpenDialogBox();
		else
			if (!this->modes.empty()) {
				this->updateModes(dt);
				this->updateSidePanel();
			}
	}
	if (this->pause) {
		this->pauseMenu->update(this->mousePosWin);
		this->updateButtons();
	}
}

void EditorState::renderButtons(sf::RenderTarget& target)
{

}

void EditorState::renderModes(sf::RenderTarget& target)
{
	this->modes[this->activeMode]->render(target);
}

void EditorState::renderDropDownBox(sf::RenderTarget& target)
{
	target.draw(this->dropDownBox);
	this->New->render(target);
	this->Open->render(target);
	this->Save->render(target);
}

void EditorState::renderMenuBar(sf::RenderTarget& target)
{
	target.setView(this->state_Data->window->getDefaultView());
	target.draw(this->menuBar);
	this->file->render(target);
	if (this->isFileButtonActive)
		this->renderDropDownBox(target);
}

void EditorState::renderSidePanel(sf::RenderTarget& target)
{
	target.setView(this->state_Data->window->getDefaultView());
	target.draw(this->sidePanel);
	this->mapEditorButton->render(target);
	this->playerEditorButton->render(target);
}

void EditorState::render(sf::RenderTarget& target)
{
	
	if (!this->modes.empty()) {
		this->renderModes(target);
	}
	this->renderMenuBar(target);
	if (this->isMapSaved)
		this->playButton->render(target);
	if (!this->modes.empty()) {
		this->renderSidePanel(target);
	}
	


	if (this->isOpenDialogOpen)
		this->mapLoader->render(target);
	else if (this->isNewDialogOpen)
		this->newDialogBox->render(target);
	if (this->pause) {
		target.setView(this->state_Data->window->getDefaultView());
		this->pauseMenu->render(target);
	}
}
