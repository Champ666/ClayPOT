#include "stdafx.h"
#include "DefaultEditorMode.h"

void DefaultEditorMode::initVariables()
{
	this->textureRect = sf::IntRect({ 0, 0 },{static_cast<int>((this->stateData->gridSize.x)), static_cast<int>((this->stateData->gridSize.y)) });
	this->collision = false;
	this->type = DEFAULT;
	this->layer = 0;
	this->cameraSpeed = 750.f;
}

void DefaultEditorMode::initCursorText()
{
	this->cursorText = new sf::Text(*this->editorStateData->font);
	this->cursorText->setCharacterSize(12);
	this->cursorText->setFillColor(sf::Color::White);
	this->cursorText->setPosition({ this->editorStateData->mousePosView->x, this->editorStateData->mousePosView->y - 50.f });
}

void DefaultEditorMode::initGui()
{

	//General GUI
	this->selectorRect.setSize({ this->stateData->gridSize.x, this->stateData->gridSize.y });
	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
	this->selectorRect.setTexture(this->tileMap->getTextureSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelecter(20.f, 20.f, this->tileMap->getTextureSheet()->getSize().x,
		 this->tileMap->getTextureSheet()->getSize().y,
		this->stateData->gridSize, this->tileMap->getTextureSheet(), *this->editorStateData->font
	);
	
	//Buttons
}



void DefaultEditorMode::initButtons()
{

}

DefaultEditorMode::DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
	: EditorMode(state_data, tile_map, editor_state_data)
{
	this->initVariables();
	this->initCursorText();
	this->initGui();
}


DefaultEditorMode::~DefaultEditorMode()
{
	delete this->textureSelector;
	delete this->cursorText;
}



//Functions


void DefaultEditorMode::updateGui(const float& dt)
{


	if (!this->textureSelector->getActive()) {
		this->selectorRect.setPosition({(this->editorStateData->mousePosGrid->x * (this->stateData->gridSize.x)),
		this->editorStateData->mousePosGrid->y * (this->stateData->gridSize.y) });
	}

	this->cursorText->setPosition({ this->editorStateData->mousePosView->x + 50.f,this->editorStateData->mousePosView->y + 50.f });

	std::stringstream ss;
	ss << "X pos: " << this->editorStateData->mousePosView->x << "        Y pos: " << this->editorStateData->mousePosView->y
		<< "\n\n\n"
		<< "X Grid: " << this->editorStateData->mousePosGrid->x << "        Y Grid: " << this->editorStateData->mousePosGrid->y
		<< "\n\n\n"
		<< "Sheet X:  " << this->textureRect.position.x << "      Sheet Y:  " << this->textureRect.position.y
		<< "\n\n\n"
		<< "Collision:  " << this->collision << "    Tile Type:  " << this->type
		<< "\n\n\nLayers: " << this->tileMap->getLayerSize(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, this->layer);
	;
	this->cursorText->setString(ss.str());

	this->textureSelector->update(*this->editorStateData->mousePosWindow, dt);

}

void DefaultEditorMode::updateButtons()
{

}

void DefaultEditorMode::updateMouseInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (!this->textureSelector->getActive()) {
			if (this->type == TileTypes::TOP || this->type == TileTypes::FRONT || this->type == TileTypes::SHADOW) {
				while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

				}
				this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
			}
			else {
				this->tileMap->addTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
			}
		}


		else {
			while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

			}
			this->textureRect = this->textureSelector->getTextureRext();
			this->textureSelector->setSelectorRectTexture(textureRect);
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {

		}
		this->tileMap->removeTile(this->editorStateData->mousePosGrid->x, this->editorStateData->mousePosGrid->y, 0);
	}
}

void DefaultEditorMode::updateTile()
{
	if (this->textureSelector->getGridChange()) {
		this->textureSelector->setGridChange(false);
		sf::IntRect temp = this->textureSelector->getChangedGridRect();
		this->textureRect = temp;
		this->selectorRect.setSize({ static_cast<float>(temp.size.x) ,static_cast<float>(temp.size.y) });
		this->selectorRect.setTextureRect(this->textureRect);
		std::cout << "\n\n\nEDITOR STATE::238::INSIDE\n";
		std::cout << "\nGUI::601::SELECTOR RECT: " << temp.size.x;
		std::cout << "\nGUI::601::SELECTOR RECT: " << temp.size.y;
		std::cout << "\nGUI::601::SELECTOR RECT: " << temp.position.x;
		std::cout << "\nGUI::601::SELECTOR RECT: " << temp.position.y;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
		{

		}
		if (this->textureRect.position.x > 0) {
			this->textureRect.position.x -= this->stateData->gridSize.x;
			this->textureSelector->setSelectorRectPos(textureRect);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
		{

		}
		if (this->textureRect.position.x < this->tileMap->getTextureSheet()->getSize().x - this->stateData->gridSize.x) {
			this->textureRect.position.x += this->stateData->gridSize.x;
			this->textureSelector->setSelectorRectPos(textureRect);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
		{

		}
		if (this->textureRect.position.y < this->tileMap->getTextureSheet()->getSize().y - this->stateData->gridSize.y) {
			this->textureRect.position.y += this->stateData->gridSize.y;
			this->textureSelector->setSelectorRectPos(textureRect);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
		{

		}
		if (this->textureRect.position.y > 0) {
			this->textureRect.position.y -= this->stateData->gridSize.y;
			this->textureSelector->setSelectorRectPos(textureRect);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::C)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::C))
		{

		}
		this->collision = !collision;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::U)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::U))
		{

		}
		this->type++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::I)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::I))
		{

		}
		this->type--;
	}
}

void DefaultEditorMode::updateTileData()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
		{

		}
		this->tileMap->saveToFile("Resources/Map/map");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::L))
		{

		}
		this->tileMap->loadFromFile("Resources/Map/map");
	}
}

void DefaultEditorMode::updateView(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
		this->editorStateData->view->move({ 0, -this->cameraSpeed * dt });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
		this->editorStateData->view->move({ -this->cameraSpeed * dt, 0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
		this->editorStateData->view->move({ 0, this->cameraSpeed * dt });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		this->editorStateData->view->move({ this->cameraSpeed * dt, 0 });
	}
}

void DefaultEditorMode::updateKeyBoardInput(const float& dt)
{
	//Switching Between Tiles By KeyBoard
	this->updateTile();

	//Saving & Loading Tile
	this->updateTileData();

	//Updating Camera View:
	if (!this->textureSelector->getActive())
		this->updateView(dt);
}

void DefaultEditorMode::updateInput(const float& dt)
{
	this->updateMouseInput();
	this->updateKeyBoardInput(dt);
	this->selectorRect.setTextureRect(this->textureRect);
}

void DefaultEditorMode::update(const float& dt)
{

	this->updateGui(dt);
	this->updateInput(dt);
	
}



void DefaultEditorMode::renderButtons(sf::RenderTarget& target)
{

}

void DefaultEditorMode::renderGui(sf::RenderTarget& target)
{
	if (!this->textureSelector->getActive()) {
		target.setView(*this->editorStateData->view);
		target.draw(this->selectorRect);
	}


	target.setView(this->stateData->window->getDefaultView());
	this->textureSelector->render(target);

	target.setView(*this->editorStateData->view);
	target.draw(*this->cursorText);

}

void DefaultEditorMode::render(sf::RenderTarget& target)
{
	target.setView(*this->editorStateData->view);
	this->tileMap->render(target, *this->editorStateData->mousePosGrid,
		nullptr, true, this->editorStateData->mousePosView);
	target.setView(this->stateData->window->getDefaultView());
	this->renderGui(target);
}