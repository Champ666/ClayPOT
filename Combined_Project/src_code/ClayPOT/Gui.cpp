#include "stdafx.h"
#include "Gui.h"

//=================================== GUI ===================== CALCULATIONS ==========================




const float gui::p2pX(float size, const sf::VideoMode& vm)
{
	size = size / 1920;
	return std::floor(static_cast<float>(vm.size.x * size));
}

const float gui::p2pY(float size, const sf::VideoMode& vm)
{
	size = size / 1080;
	return std::floor(static_cast<float>(vm.size.y * size));
}

const unsigned gui::characterSize(const sf::VideoMode& vm, unsigned size)
{
	float percent = (static_cast<float>(size) / 1080.f);
	return std::floor(static_cast<unsigned>(vm.size.y * percent));
}








//============================ ============== Button Stuff ============== ============================ //

gui::Button::Button(
	float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned short fontSize,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color text_idleColor, sf::Color text_hoverColor, sf::Color text_activeColor, unsigned short id
)
{
	this->lastState = BTN_IDLE;
	this->buttonState = BTN_IDLE;
	this->id = id;
	this->shape.setFillColor(idleColor);
	this->shape.setPosition({ x,y });
	this->shape.setSize({ width,height });
	this->shape.setOrigin({ this->shape.getGlobalBounds().size.x / 2.0f, this->shape.getGlobalBounds().size.y / 2.0f });
	this->font = font;
	this->text = new sf::Text(*this->font);
	this->text->setString(text);
	this->text->setFillColor(text_idleColor);
	this->text->setCharacterSize(fontSize);
	this->text->setOrigin({
		this->text->getGlobalBounds().size.x / 2.0f,
		this->text->getGlobalBounds().size.y / 2.0f
		});
	this->text->setPosition({
		this->shape.getPosition().x - 1.0f,
		this->shape.getPosition().y - 5.0f
		});



	this->text_idleColor = text_idleColor;
	this->text_hoverColor = text_hoverColor;
	this->text_activeColor = text_activeColor;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
}

gui::Button::Button(float x, float y, float width, float height, sf::Color idleColor,
	sf::Color hoverColor, sf::Color activeColor, unsigned short id /*= 0 */)
{

	this->isPlayIcon = true;
	// === Rectangle background ===
	shape.setSize({ width, height });
	shape.setPosition({ x, y });
	shape.setFillColor(idleColor);
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(sf::Color::White);

	// === Triangle play icon using sf::VertexArray ===
	playIcon.setPrimitiveType(sf::PrimitiveType::Triangles);
	playIcon.resize(3);

	float left = x + width * 0.35f;
	float top = y + height * 0.3f;
	float right = x + width * 0.65f;
	float bottom = y + height * 0.7f;
	float midY = y + height * 0.5f;

	// Points: a simple right-pointing triangle
	playIcon[0].position = { left, top };
	playIcon[1].position = { left, bottom };
	playIcon[2].position = { right, midY };

	for (int i = 0; i < 3; ++i)
		playIcon[i].color = sf::Color::White;
}

gui::Button::~Button()
{
	if(text)
		delete text;
	text = nullptr;
	font = nullptr;
}

const bool gui::Button::isPressed() const
{
	return this->buttonState == BTN_ACTIVE;
}

const std::string gui::Button::getText() const
{
	return this->text->getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

void gui::Button::setText(std::string text)
{
	this->text->setString(text);
}

void gui::Button::setId(unsigned short id)
{
	this -> id = id;
}

void gui::Button::updatePositions(float x, float y, float width, float height, unsigned fontSize)
{
	this->shape.setPosition({x, y});
	this->shape.setSize({ width,height });
	this->text->setCharacterSize(fontSize);
	this->text->setPosition({
		this->shape.getPosition().x - 1.0f,
		this->shape.getPosition().y - 5.0f
		});
}

void gui::Button::update(const sf::Vector2i& mousePosWin)
{

	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWin))) {
		this->buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			this->buttonState = BTN_ACTIVE;
	}

	if (this->buttonState == BTN_HOVER && this->lastState != BTN_HOVER) {
		// Mouse just entered play hover sound once
		SoundLibrary::playSound("BTN_HOVER");
	}

	switch (this->buttonState) {

	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		if (this->text)
			this->text->setFillColor(this->text_idleColor);

		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		if (this->text)
			this->text->setFillColor(this->text_hoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		if (this->text)
			this->text->setFillColor(this->text_activeColor);
		SoundLibrary::playSound("BTN_ACTIVE");
		break;

	}
	this->lastState = this->buttonState;
}

void gui::Button::render(sf::RenderTarget& target)
{

	target.draw(this->shape);
	if (this->isPlayIcon)
		target.draw(this->playIcon);
	if(this->text)
		target.draw(*this->text);
	
}




// ============================ ============== Drop Down List Stuff ============== ============================ //

bool gui::DropDownList::change = false;

gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], size_t listSize, unsigned default_index, unsigned short charSize) : font(font), showList(false)
{

	gui::DropDownList::change = false;

	this->activeElement = new gui::Button(x, y, width, height, &this->font, list[default_index], charSize,
		sf::Color(58, 47, 35, 0.85 * 255), sf::Color(160, 96, 48, 0.9 * 255), sf::Color(44, 30, 18, 0.85 * 255),
		sf::Color(255, 214, 138, 1.0 * 255), sf::Color(255, 240, 190, 1.0 * 255), sf::Color(255, 202, 120, 1.0 * 255)
	);

	for(size_t i = 0; i < listSize; i++){
	this->list.push_back(
		new gui::Button(x, y + ((i + 1 )* height) + 1, width, height, &this->font, list[i], charSize,
			sf::Color(58, 47, 35, 0.85 * 255), sf::Color(160, 96, 48, 0.9 * 255), sf::Color(44, 30, 18, 0.85 * 255),
	  sf::Color(255, 214, 138, 1.0 * 255), sf::Color(255, 240, 190, 1.0 * 255), sf::Color(255, 202, 120, 1.0 * 255), i
	));
	}


}


gui::DropDownList::~DropDownList()
{


	for (auto& it : this->list) {
		delete it;
	}
	delete this->activeElement;

}

const bool& gui::DropDownList::getChange()
{
	return DropDownList::change;
}

void gui::DropDownList::setChange(bool change)
{
	DropDownList::change = change;
}

void gui::DropDownList::updatePositions(float x, float y, float width, float height, unsigned fontSize)
{
	this->activeElement->updatePositions(x, y, width, height, fontSize);
	for (size_t i = 0; i < this->list.size(); ++i) {
		list[i]->updatePositions(x, y + ((i + 1) * height), width, height, fontSize);
	}
	
}

void gui::DropDownList::update(const sf::Vector2i mousePosWin)
{

	this->activeElement->update(mousePosWin);
	if (this->activeElement->isPressed()) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

		}
		this->showList = !this->showList;
	}
	if(this->showList){
		for (auto& it : this->list) {
			it->update(mousePosWin);

			if (it->isPressed()) {
				DropDownList::change = true;
				this->showList = !this->showList;
				this->activeElement->setText(it->getText());
				this->activeElement->setId(it->getId());
			}
		}
	}
	
}

void gui::DropDownList::render(sf::RenderTarget& target)
{

	this->activeElement->render(target);

	if (this->showList){

		for (auto& it : this->list) {
			it->render(target);
		}

	}

}

const short unsigned& gui::DropDownList::getActiveId() const
{
	return this->activeElement->getId();
}




// ============================ ============== TEXTURE SELECTOR Stuff ============== ============================ //



void gui::TextureSelecter::initVariables(sf::Vector2f gridSize)
{
	this->gridSize = gridSize;
	this->active = false;
	this->hidden = false;
	this->isGridChanged = false;
	this->hideBTN = nullptr;
	this->xPos = 0.f;
	this->yPos = 0.f;
}

void gui::TextureSelecter::initBounds(float x, float y, float width, float height)
{
	float selectorSize = 1000;
	this->bounds.setSize({ selectorSize , selectorSize });
	this->bounds.setPosition({ x, y });
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color::Green);
}

void gui::TextureSelecter::initSheet(float x, float y,const sf::Texture* textureSheet)
{
	int selectorSize = 1000;
	this->textureSizeX = textureSheet->getSize().x;
	this->textureSizeY = textureSheet->getSize().y;
	this->sheet = new sf::Sprite(*textureSheet);
	this->sheet->setPosition({ x,y });
	this->sheet->setTexture(*textureSheet);
	if (this->sheet->getGlobalBounds().size.x < selectorSize || this->sheet->getGlobalBounds().size.y < selectorSize) {
		if (this->sheet->getGlobalBounds().size.x > this->bounds.getGlobalBounds().size.x) {
			this->sheet->setTextureRect(sf::IntRect({ 0,0 }, { int(this->bounds.getGlobalBounds().size.x)
				,int(this->sheet->getGlobalBounds().size.y) }));
		}
		if (this->sheet->getGlobalBounds().size.y > this->bounds.getGlobalBounds().size.y) {
			this->sheet->setTextureRect(sf::IntRect({ 0,0 }, { int(this->sheet->getGlobalBounds().size.x)
				,int(this->bounds.getGlobalBounds().size.y) }));
		}
	}
	else {
		this->sheet->setTextureRect(sf::IntRect({ 0,0 }, { selectorSize, selectorSize }));
	}
	

}

void gui::TextureSelecter::initSelector(float x, float y, sf::Vector2f gridSize)
{
	this->selector.setPosition({ x,y });
	this->selector.setSize({ gridSize.x, gridSize.y });
	this->selector.setFillColor(sf::Color(250,250,250,200));
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);
	this->selector.setTexture(&sheet->getTexture());
	this->selector.setTextureRect(sf::IntRect({ 0,0 }, { static_cast<int>(this->gridSize.x), static_cast<int>(this->gridSize.y) }));
}

void gui::TextureSelecter::initSelectorRect()
{
	this->selectorRect.size.x = static_cast<float>(this->gridSize.x);
	this->selectorRect.size.y = static_cast<float>(this->gridSize.y);
}

void gui::TextureSelecter::initGridSelector()
{
	this->gridSelector = new GridSelector(this->selectorRect);
}

void gui::TextureSelecter::initButton(sf::Font& font)
{
	this->hideBTN = new gui::Button(25, 1055, 30, 30, &font, "EDIT", 15,
		sf::Color(58, 47, 35, 100), sf::Color(160, 96, 48, 100), sf::Color(44, 30, 18, 100),
		sf::Color(255, 214, 138, 255), sf::Color(255, 240, 190, 255), sf::Color(255, 202, 120, 255)
	);

	this->gridSelectorButton = new gui::Button(85, 1055, 30, 30, &font, "Grid", 15,
		sf::Color(58, 47, 35, 100), sf::Color(160, 96, 48, 100), sf::Color(44, 30, 18, 100),
		sf::Color(255, 214, 138, 255), sf::Color(255, 240, 190, 255), sf::Color(255, 202, 120, 255)
	);
}

gui::TextureSelecter::TextureSelecter(float x, float y, float width, float height, sf::Vector2f gridSize, const sf::Texture* textureSheet, sf::Font& font)
{
	this->initVariables(gridSize);
	this->initBounds(x, y, width, height);
	this->initSheet(x, y, textureSheet);
	this->initSelector(x, y, gridSize);
	this->initSelectorRect();
	this->initGridSelector();
	this->initButton(font);
}

gui::TextureSelecter::~TextureSelecter()
{

	delete this->sheet;
	delete this->hideBTN;
	delete this->gridSelectorButton;

}



//Modifier
void gui::TextureSelecter::setSelectorRectPos(sf::IntRect rect)
{
	this->selector.setTextureRect(rect);
	this->selector.setPosition({ this->bounds.getPosition().x + static_cast<float>(rect.position.x) ,
		this->bounds.getPosition().y + static_cast<float>(rect.position.y) });
}

void gui::TextureSelecter::setSelectorRectTexture(sf::IntRect& rect)
{
	this->selector.setTextureRect(rect);
}

void gui::TextureSelecter::moveSprite(float x, float y)
{
	this->sheet->move({ x,y });
}


void gui::TextureSelecter::setGridChange(const bool change)
{
	this->isGridChanged = change;
}

const bool gui::TextureSelecter::getGridChange()
{
	return this->isGridChanged;
}

const sf::IntRect& gui::TextureSelecter::getChangedGridRect()
{
	return this->selectorRect;
}

//Fucntions
const bool& gui::TextureSelecter::getActive()
{
	return this->active;
}

const sf::IntRect gui::TextureSelecter::getTextureRext()
{
	return this->selectorRect;
}

void gui::TextureSelecter::calculatePosition(float x, float y, const float& dt)
{
	int tempX = static_cast<int>(this->sheet->getGlobalBounds().size.x);
	int tempY = static_cast<int>(this->sheet->getGlobalBounds().size.y);


	if (x < 0 && this->xPos > 0) {
		this->xPos += x * this->gridSize.x;
		this->selectorRect.position.x += this->xPos;
		this->sheet->setTextureRect(sf::IntRect({this->xPos,this->yPos},{ tempX,tempY }));
	}
	if (x > 0 && this->xPos + tempX < this->textureSizeX) {
		this->xPos += x * this->gridSize.x;
		this->selectorRect.position.x += this->xPos;
		this->sheet->setTextureRect(sf::IntRect({ this->xPos,this->yPos },{ tempX,tempY }));
	}
	if (y < 0 && this->yPos > 0) {
		this->yPos += y * this->gridSize.y;
		this->selectorRect.position.y += this->yPos;
		this->sheet->setTextureRect(sf::IntRect({ this->xPos,this->yPos },{tempX, tempY}));
	}
	if (y > 0 && this->yPos + tempY < this->textureSizeY) {
		this->yPos += y * this->gridSize.y;
		this->selectorRect.position.y += this->yPos;
		this->sheet->setTextureRect(sf::IntRect({ this->xPos,this->yPos }, {tempX, tempY}));
	}
	
}

void gui::TextureSelecter::updatePosition(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
		this->calculatePosition(0, -1, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
		this->calculatePosition(-1, 0, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
		this->calculatePosition(0, 1, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		this->calculatePosition(1, 0, dt);
	}
}


void gui::TextureSelecter::updateKeyBoardInput()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Tab)) {
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Tab)) {

		}
		this->hidden = !this->hidden;
		if(active == true)
			this->active = false;
		else
			this->active = true;
	}

}

void gui::TextureSelecter::updateButton(const sf::Vector2i& mousePosWindow)
{

	this->hideBTN->update(mousePosWindow);
	

	if (this->hideBTN->isPressed()) {
		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

		}
		this->hidden = !this->hidden;
	}
	if(!this->hidden){
		this->gridSelectorButton->update(mousePosWindow);
		if (this->gridSelectorButton->isPressed()) {
			while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

			}
			if (this->gridSelector->getActive()) {
				this->gridSelector->setActive(false);
			}
			else {
				this->gridSelector->setActive(true);
			}
			
		}
	}

}

void gui::TextureSelecter::updateGridSelector(const sf::Vector2i& mousePosWindow)
{
	this->gridSelector->update(mousePosWindow);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		this->gridSelector->setSelection(true);
	}
	else {
		if (this->gridSelector->getSelection()) {
			this->gridSelector->setSelection(false);
			sf::IntRect temp = this->gridSelector->getselectorRect();
			temp.position.x += (this->xPos - this->bounds.getPosition().x);
			temp.position.y += (this->yPos - this->bounds.getPosition().y);
			this->selector.setSize({ static_cast<float>(temp.size.x) ,static_cast<float>(temp.size.y) });
			this->selector.setTextureRect(temp);
			this->selectorRect.size.x = static_cast<int>(this->selector.getSize().x);
			this->selectorRect.size.y = static_cast<int>(this->selector.getSize().y);
			this->selectorRect.position.x = static_cast<int>(this->selector.getPosition().x -
				this->bounds.getPosition().x) + this->xPos;
			this->selectorRect.position.y = static_cast<int>(this->selector.getPosition().y -
				this->bounds.getPosition().y) + this->yPos;
			this->isGridChanged = true;
		}
		
	}
}

void gui::TextureSelecter::updateTextureSelector(const sf::Vector2i& mousePosWindow)
{

	if (!this->hidden) {
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			this->active = true;
		else
			this->active = false;

		if (!this->gridSelector->getActive()) {
			if (this->active) {

				this->mousePosGrid.x = static_cast<int>((mousePosWindow.x - this->bounds.getGlobalBounds().position.x) / this->gridSize.x);
				this->mousePosGrid.y = static_cast<int>((mousePosWindow.y - this->bounds.getGlobalBounds().position.y) / this->gridSize.y);

				if (this->mousePosGrid.x * this->gridSize.x < this->bounds.getSize().x &&
					this->mousePosGrid.y * this->gridSize.y < this->bounds.getSize().y) {
					this->selector.setPosition({
					this->bounds.getPosition().x + mousePosGrid.x * this->gridSize.x,
					this->bounds.getPosition().y + mousePosGrid.y * this->gridSize.y
						});

					this->selectorRect.size.x = static_cast<int>(this->selector.getSize().x);
					this->selectorRect.size.y = static_cast<int>(this->selector.getSize().y);
					this->selectorRect.position.x = static_cast<int>(this->selector.getPosition().x -
						this->bounds.getPosition().x) + this->xPos;
					this->selectorRect.position.y = static_cast<int>(this->selector.getPosition().y -
						this->bounds.getPosition().y) + this->yPos;

				}

			}
		}
		
	}
	
}

void gui::TextureSelecter::update(const sf::Vector2i& mousePosWindow, const float& dt)
{

	this->updateKeyBoardInput();
	this->updateButton(mousePosWindow);
	this->updateTextureSelector(mousePosWindow);

	if (this->active) {
		this->updatePosition(dt);
		if (this->gridSelector->getActive()) {
			sf::Vector2i pos = { static_cast<int>(mousePosWindow.x) ,
								 static_cast<int>(mousePosWindow.y) };
			this->updateGridSelector(pos);
		}
	}
		
	
	
}

void gui::TextureSelecter::render(sf::RenderTarget& target)
{
	if (!this->hidden) {
		if (this->active) {
			target.draw(this->bounds);
		}
		target.draw(*this->sheet);
		if (this->active) {
			if (this->gridSelector->getActive()) {
				this->gridSelector->render(target);
			}
			else {
				target.draw(this->selector);
			}
			
			
		}
		this->gridSelectorButton->render(target);
	}
	
	this->hideBTN->render(target);
	

}








// ============================ ============== GRID SELECTOR Stuff ============== ============================ //

gui::GridSelector::GridSelector(sf::IntRect selectorRect)
{
	this->isActive = false;
	this->isSelecting = false;
	this->startPos = {0,0};
	this->initVariaibles(selectorRect);
}

gui::GridSelector::~GridSelector()
{

}

void gui::GridSelector::initVariaibles(sf::IntRect selectorRect)
{
	this->selectorRect = selectorRect;
	this->selectorBox.setFillColor(sf::Color::Transparent);
	this->selectorBox.setFillColor(sf::Color::Transparent);
	this->selectorBox.setOutlineThickness(1);
	this->selectorBox.setOutlineColor(sf::Color::White);
	this->selectorBox.setPosition({ static_cast<float>(this->selectorRect.position.x), static_cast<float>(this->selectorRect.position.y) });
	this->selectorBox.setSize({ static_cast<float>(this->selectorRect.size.x), static_cast<float>(this->selectorRect.size.y) });
}


void gui::GridSelector::updateSelectorBox(const sf::Vector2i& mousePosWindow)
{
	
	if (!isSelecting) {
		this->startPos = static_cast<sf::Vector2f>(mousePosWindow);
		this->selectorBox.setPosition(startPos);
		this->selectorBox.setSize({ 0.f, 0.f });

		this->selectorRect.position = mousePosWindow;
		this->selectorRect.size = { 0, 0 };
	}
	else {
		sf::Vector2f currentPos = static_cast<sf::Vector2f>(mousePosWindow);

		// Calculate top-left corner and size
		sf::Vector2f topLeft(
			std::min(startPos.x, currentPos.x),
			std::min(startPos.y, currentPos.y)
		);
		sf::Vector2f size(
			std::abs(currentPos.x - startPos.x),
			std::abs(currentPos.y - startPos.y)
		);

		this->selectorBox.setPosition(topLeft);
		this->selectorBox.setSize(size);

		this->selectorRect.position = static_cast<sf::Vector2i>(topLeft);
		this->selectorRect.size = static_cast<sf::Vector2i>(size);

		std::cout << "\n\n\nGUI::601::SELECTOR RECT: " << selectorRect.size.x;
		std::cout << "\nGUI::601::SELECTOR RECT: " << selectorRect.size.y;
		std::cout << "\nGUI::601::SELECTOR RECT: " << selectorRect.position.x;
		std::cout << "\nGUI::601::SELECTOR RECT: " << selectorRect.position.y;
		
	}


}

const bool gui::GridSelector::getActive()
{
	return this->isActive;
}

const bool gui::GridSelector::getSelection()
{
	return this->isSelecting;
}

const sf::IntRect& gui::GridSelector::getselectorRect()
{
	return this->selectorRect;
}

void gui::GridSelector::update(const sf::Vector2i& mousePosWindow)
{
	this->updateSelectorBox(mousePosWindow);
}

void gui::GridSelector::render(sf::RenderTarget& target)
{
	target.draw(this->selectorBox);
}

void gui::GridSelector::setActive(const bool active)
{
	this->isActive = active;
}

void gui::GridSelector::setSelection(const bool selection)
{
	this->isSelecting = selection;
}


// PROGRESSBAR ============================================================================= PROGRESSBAR

gui::ProgressBar::ProgressBar(float _x, float _y, float _width, float _height,
	sf::Color inner_color, sf::VideoMode& vm)
{
	float width = gui::p2pX(_width, vm);
	float height = gui::p2pY(_height, vm);
	float x = gui::p2pX(_x, vm);
	float y = gui::p2pY(_y, vm);

	this->maxWidth = width;

	this->back.setSize(sf::Vector2f(width, height));
	this->back.setFillColor(sf::Color(50, 50, 50, 200));
	this->back.setPosition({ x, y });

	this->inner.setSize(sf::Vector2f(width, height));
	this->inner.setFillColor(inner_color);
	this->inner.setPosition(this->back.getPosition());
	
}

gui::ProgressBar::~ProgressBar()
{
	
}

//Functions
void gui::ProgressBar::update(const int current_value, const int max_value)
{
	float percent = static_cast<float>(current_value) / static_cast<float>(max_value);

	this->inner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->maxWidth * percent)),
			this->inner.getSize().y
		)
	);

}

void gui::ProgressBar::render(sf::RenderTarget& target)
{
	target.draw(this->back);
	target.draw(this->inner);
}


//======================================================      TEXT HOLDER =================================================================

gui::TextHolder::TextHolder(float x, float y, float width, float height, sf::Font& font,
	const std::string& placeholder, unsigned short chrSize, bool numericOnly)
	: font(&font), placeholderText(placeholder), isActive(false), isNumericOnly(numericOnly)
{
	this->inputBox.setSize({ width, height });
	this->inputBox.setFillColor(sf::Color(30, 30, 30, 220));
	this->inputBox.setOutlineColor(sf::Color(200, 200, 200));
	this->inputBox.setOutlineThickness(2);
	this->inputBox.setPosition({ x, y });

	this->inputText = new sf::Text(*this->font);
	this->inputText->setString(placeholder);
	this->inputText->setCharacterSize(chrSize);
	this->inputText->setFillColor(sf::Color(200, 200, 200, 180));
	this->inputText->setPosition({ x + (chrSize / 2), y + (chrSize / 2) });

	this->inputString = "";
}

gui::TextHolder::~TextHolder()
{
	delete this->inputText;
}

sf::Vector2f gui::TextHolder::getPos() const
{
	return this->inputBox.getPosition();
}

sf::Vector2f gui::TextHolder::getSize() const
{
	return this->inputBox.getSize();
}

const std::string& gui::TextHolder::getInputString() const
{
	return this->inputString;
}

bool gui::TextHolder::getActive() const
{
	return this->isActive;
}

void gui::TextHolder::setActive(bool active)
{
	this->isActive = active;
	if (active && (this->inputString.empty() || this->inputText->getString() == this->placeholderText || this->inputText->getString() == "Invalid")) {
		this->inputText->setString("");
		this->inputText->setFillColor(sf::Color::White);
		this->inputString = "";
	}
}

void gui::TextHolder::setInvalid()
{
	this->inputText->setString("Invalid");
	this->inputText->setFillColor(sf::Color::Red);
	this->inputString = "";
}

void gui::TextHolder::clearField()
{
	this->inputString = "";
	this->inputText->setString(this->placeholderText);
	this->inputText->setFillColor(sf::Color(200, 200, 200, 180));
	this->isActive = false;
}

void gui::TextHolder::updateInput(const sf::Event& event)
{
	if (this->isActive) {
		if (const auto* textEntered = event.getIf<sf::Event::TextEntered>()) {
			if (textEntered->unicode == 8 && !this->inputString.empty()) {
				this->inputString.pop_back(); // backspace
			}
			else if (this->isNumericOnly) {
				if (textEntered->unicode >= 48 && textEntered->unicode <= 57) { // Only allow digits
					this->inputString += static_cast<char>(textEntered->unicode);
				}
			}
			else {
				if (textEntered->unicode >= 32 && textEntered->unicode < 128) {
					this->inputString += static_cast<char>(textEntered->unicode);
				}
			}
			this->inputText->setString(this->inputString);
		}
	}
}

void gui::TextHolder::update(const sf::Vector2i& mousePosWin)
{
	// Click detection is handled by parent class
}

void gui::TextHolder::render(sf::RenderTarget& target)
{
	target.draw(this->inputBox);
	target.draw(*this->inputText);
}



//======================================================      DIALOG BOX =================================================================

gui::DialogBox::DialogBox(float x, float y, float width, float height, sf::Font& font, const std::string placeHolderText, unsigned short chrSize)
{
	this->font = &font;
	this->panel.setSize({ width, height });
	this->panel.setFillColor(sf::Color(45, 45, 45, 230));
	this->panel.setOutlineColor(sf::Color::White);
	this->panel.setOutlineThickness(2);
	this->panel.setPosition({ x, y });

	this->placeHolderText = new sf::Text(*this->font);
	this->placeHolderText->setString(placeHolderText);
	this->placeHolderText->setCharacterSize(chrSize);
	this->placeHolderText->setFillColor(sf::Color::White);
	this->placeHolderText->setPosition({ this->panel.getPosition().x + this->panel.getSize().x * 0.38f, this->panel.getPosition().y + chrSize * 2 });

	float inputWidth = this->panel.getSize().x / 2;
	float inputHeight = (this->panel.getSize().y / 5) * 0.7f;
	float startX = this->panel.getPosition().x + this->panel.getSize().x / 4;
	float startY = this->panel.getPosition().y + this->panel.getSize().y / 1.5f;

	this->pngPathHolder = new TextHolder(startX, startY, inputWidth, inputHeight, font, "e.g: Resource / map.png ", chrSize, false);

	float smallWidth = inputWidth / 2 - 10;
	this->gridYHolder = new TextHolder(startX, startY - inputHeight - 10, smallWidth, inputHeight, font, "Grid Size Y", chrSize, true);
	this->gridXHolder = new TextHolder(startX, startY - 2 * (inputHeight + 10), smallWidth, inputHeight, font, "Grid Size X", chrSize, true);
	this->mapXHolder = new TextHolder(startX + smallWidth + 20, startY - 2 * (inputHeight + 10), smallWidth, inputHeight, font, "Map Size X", chrSize, true);
	this->mapYHolder = new TextHolder(startX + smallWidth + 20, startY - inputHeight - 10, smallWidth, inputHeight, font, "Map Size Y", chrSize, true);

	this->enterButton = new gui::Button(startX + inputWidth / 4, startY + inputHeight * 1.75f,
		inputWidth / 3, inputHeight, this->font, "Enter", chrSize,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(230, 230, 230, 255), sf::Color(255, 255, 255, 255), sf::Color(230, 230, 230, 255));

	this->clearButton = new gui::Button(startX + inputWidth - inputWidth / 4, startY + inputHeight * 1.75f,
		inputWidth / 3, inputHeight, this->font, "Close", chrSize,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(230, 230, 230, 255), sf::Color(255, 255, 255, 255), sf::Color(230, 230, 230, 255));

	this->pngPath = "";
	this->gridSizeX = 0;
	this->gridSizeY = 0;
	this->worldSizeX = 0;
	this->worldSizeY = 0;
}

gui::DialogBox::~DialogBox()
{
	delete this->placeHolderText;
	delete this->pngPathHolder;
	delete this->gridXHolder;
	delete this->gridYHolder;
	delete this->mapXHolder;
	delete this->mapYHolder;
	delete this->enterButton;
	delete this->clearButton;
}

void gui::DialogBox::updateInput(sf::Vector2i& mousePos, const sf::Event& event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		// Reset all active states first
		this->pngPathHolder->setActive(false);
		this->gridXHolder->setActive(false);
		this->gridYHolder->setActive(false);
		this->mapXHolder->setActive(false);
		this->mapYHolder->setActive(false);

		// Check which input box was clicked
		sf::Vector2f mouseFloat = { static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) };

		if (sf::FloatRect(this->pngPathHolder->getPos(), this->pngPathHolder->getSize()).contains(mouseFloat)) {
			this->pngPathHolder->setActive(true);
		}
		else if (sf::FloatRect(this->gridXHolder->getPos(), this->gridXHolder->getSize()).contains(mouseFloat)) {
			this->gridXHolder->setActive(true);
		}
		else if (sf::FloatRect(this->gridYHolder->getPos(), this->gridYHolder->getSize()).contains(mouseFloat)) {
			this->gridYHolder->setActive(true);
		}
		else if (sf::FloatRect(this->mapXHolder->getPos(), this->mapXHolder->getSize()).contains(mouseFloat)) {
			this->mapXHolder->setActive(true);
		}
		else if (sf::FloatRect(this->mapYHolder->getPos(), this->mapYHolder->getSize()).contains(mouseFloat)) {
			this->mapYHolder->setActive(true);
		}
	}

	this->pngPathHolder->updateInput(event);
	this->gridXHolder->updateInput(event);
	this->gridYHolder->updateInput(event);
	this->mapXHolder->updateInput(event);
	this->mapYHolder->updateInput(event);

	// Update stored values from TextHolder inputs
	this->pngPath = this->pngPathHolder->getInputString();

	if (!this->gridXHolder->getInputString().empty()) {
		try {
			this->gridSizeX = std::stof(this->gridXHolder->getInputString());
		}
		catch (...) {
			this->gridSizeX = 0;
		}
	}
	else {
		this->gridSizeX = 0;
	}

	if (!this->gridYHolder->getInputString().empty()) {
		try {
			this->gridSizeY = std::stof(this->gridYHolder->getInputString());
		}
		catch (...) {
			this->gridSizeY = 0;
		}
	}
	else {
		this->gridSizeY = 0;
	}

	if (!this->mapXHolder->getInputString().empty()) {
		try {
			this->worldSizeX = std::stoul(this->mapXHolder->getInputString());
		}
		catch (...) {
			this->worldSizeX = 0;
		}
	}
	else {
		this->worldSizeX = 0;
	}

	if (!this->mapYHolder->getInputString().empty()) {
		try {
			this->worldSizeY = std::stoul(this->mapYHolder->getInputString());
		}
		catch (...) {
			this->worldSizeY = 0;
		}
	}
	else {
		this->worldSizeY = 0;
	}
}

void gui::DialogBox::update(sf::Vector2i& mousePosWin)
{
	this->clearButton->update(mousePosWin);
	this->enterButton->update(mousePosWin);
}

void gui::DialogBox::render(sf::RenderTarget& target)
{
	target.draw(this->panel);
	target.draw(*this->placeHolderText);

	this->pngPathHolder->render(target);
	this->gridXHolder->render(target);
	this->gridYHolder->render(target);
	this->mapXHolder->render(target);
	this->mapYHolder->render(target);

	this->clearButton->render(target);
	this->enterButton->render(target);
}

void gui::DialogBox::clearAllFields()
{
	this->pngPathHolder->clearField();
	this->gridXHolder->clearField();
	this->gridYHolder->clearField();
	this->mapXHolder->clearField();
	this->mapYHolder->clearField();

	// Reset stored values
	this->pngPath = "";
	this->gridSizeX = 0;
	this->gridSizeY = 0;
	this->worldSizeX = 0;
	this->worldSizeY = 0;
}

//======================================================      MAP LOADER =================================================================

gui::FileLoader::FileLoader(float x, float y, float width, float height, sf::Font& font, unsigned short chrSize)
	: font(&font), mapPath("")
{
	this->panel.setSize({ width, height });
	this->panel.setFillColor(sf::Color(45, 45, 45, 230));
	this->panel.setOutlineColor(sf::Color::White);
	this->panel.setOutlineThickness(2);
	this->panel.setPosition({ x, y });

	this->titleText = new sf::Text(*this->font);
	this->titleText->setString("Load Existing Map");
	this->titleText->setCharacterSize(chrSize);
	this->titleText->setFillColor(sf::Color::White);
	this->titleText->setPosition({ this->panel.getPosition().x + this->panel.getSize().x * 0.35f, this->panel.getPosition().y + chrSize });

	float inputWidth = this->panel.getSize().x * 0.8f;
	float inputHeight = (this->panel.getSize().y / 4) * 0.7f;
	float startX = this->panel.getPosition().x + this->panel.getSize().x * 0.1f;
	float startY = this->panel.getPosition().y + this->panel.getSize().y * 0.4f;

	this->pathHolder = new TextHolder(startX, startY, inputWidth, inputHeight, font, "e.g: Maps/level1.map", chrSize, false);

	this->enterButton = new gui::Button(startX + inputWidth * 0.3f, startY + inputHeight * 2.5f,
		inputWidth * 0.25f, inputHeight * 0.8f, this->font, "Load", chrSize,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(230, 230, 230, 255), sf::Color(255, 255, 255, 255), sf::Color(230, 230, 230, 255));

	this->closeButton = new gui::Button(startX + inputWidth * 0.65f, startY + inputHeight * 2.5f,
		inputWidth * 0.25f, inputHeight * 0.8f, this->font, "Close", chrSize,
		sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0), sf::Color(0, 0, 0, 0),
		sf::Color(230, 230, 230, 255), sf::Color(255, 255, 255, 255), sf::Color(230, 230, 230, 255));
}

gui::FileLoader::~FileLoader()
{
	delete this->titleText;
	delete this->pathHolder;
	delete this->enterButton;
	delete this->closeButton;
}

void gui::FileLoader::updateInput(sf::Vector2i& mousePos, const sf::Event& event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		sf::Vector2f mouseFloat = { static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) };

		if (sf::FloatRect(this->pathHolder->getPos(), this->pathHolder->getSize()).contains(mouseFloat)) {
			this->pathHolder->setActive(true);
		}
		else {
			this->pathHolder->setActive(false);
		}
	}

	this->pathHolder->updateInput(event);
	this->mapPath = this->pathHolder->getInputString();
}

void gui::FileLoader::update(sf::Vector2i& mousePosWin)
{
	this->enterButton->update(mousePosWin);
	this->closeButton->update(mousePosWin);
}

void gui::FileLoader::render(sf::RenderTarget& target)
{
	target.draw(this->panel);
	target.draw(*this->titleText);
	this->pathHolder->render(target);
	this->enterButton->render(target);
	this->closeButton->render(target);
}

void gui::FileLoader::clearField()
{
	this->pathHolder->clearField();
	this->mapPath = "";
}

const std::string& gui::FileLoader::getMapPath() const
{
	return this->mapPath;
}