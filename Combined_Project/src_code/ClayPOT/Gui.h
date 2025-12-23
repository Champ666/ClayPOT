#pragma once

#include "SoundLibrary.h"

enum{ BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui{

const float p2pX(float size, const sf::VideoMode& vm);
const float p2pY(float size, const sf::VideoMode& vm);
const unsigned characterSize(const sf::VideoMode& vm, unsigned size);


class Button
{

private:

	unsigned lastState;
	unsigned short buttonState;
	sf::RectangleShape shape;
	sf::VertexArray playIcon;
	bool isPlayIcon = false;
	sf::Font* font;
	sf::Text* text;
	unsigned short id;
	sf::Color text_idleColor;
	sf::Color text_hoverColor;
	sf::Color text_activeColor;
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;


public:

	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned short fontSize,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
		sf::Color text_idleColor, sf::Color text_hoverColor, sf::Color text_activeColor, unsigned short id = 0
	);

	Button(float x, float y, float width, float height,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
		unsigned short id = 0
	);


	~Button();

	//Accessors:
	const bool isPressed() const;
	const std::string getText() const;
	const short unsigned& getId()const;
	//Modifiers:
	void setText(std::string text);
	void setId(unsigned short id);

	//Functions:
	void updatePositions(float x, float y, float width, float height, unsigned size);
	void update(const sf::Vector2i& mousePosWin);
	void render(sf::RenderTarget& target);

};




class DropDownList {

private:

	sf::Font& font;
	gui::Button* activeElement;
	std::vector<gui::Button* > list;
	bool showList;
	static bool change;


public:

	DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], size_t listSize, unsigned default_index = 0, unsigned short charSize = 30);
	

	~DropDownList();


	const static bool& getChange();
	static void setChange(bool change);
	void updatePositions(float x, float y, float width, float height, unsigned fontSize);
	void update(const sf::Vector2i mousePosWin);
	void render(sf::RenderTarget& target);


	//Getter
	const short unsigned& getActiveId() const;

};



class GridSelector {

private:
	sf::RectangleShape selectorBox;
	sf::IntRect selectorRect;
	bool isSelecting;
	bool isActive;
	sf::Vector2f startPos;

public:
	GridSelector(sf::IntRect selectorRect);
	~GridSelector();


	//General Engine Function:
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& render);

	//Initializers:
	void initVariaibles(sf::IntRect selectorRect);

	//Updates:
	void updateSelectorBox(const sf::Vector2i& mousePosWindow);

	//Renders:

	//Modifier:
	void setActive(const bool active);
	void setSelection(const bool selection);

	//Accessor:
	const bool getActive();
	const bool getSelection();
	const sf::IntRect& getselectorRect();

};



class TextureSelecter {

private:

	bool active;
	bool hidden;
	bool isGridChanged;
	sf::Vector2f gridSize;
	int xPos;
	int yPos;
	int textureSizeX;
	int textureSizeY;
	GridSelector* gridSelector;

	Button* hideBTN;
	Button* gridSelectorButton;
	sf::RectangleShape bounds;
	sf::Sprite* sheet;
	sf::RectangleShape selector;
	sf::Vector2u mousePosGrid;
	sf::IntRect selectorRect;


	//Initializers:
	void initVariables(sf::Vector2f gridSize);
	void initBounds(float x, float y, float width, float height);
	void initSheet(float x, float y, const sf::Texture* textureSheet);
	void initSelector(float x, float y, sf::Vector2f gridSize);
	void initSelectorRect();
	void initGridSelector();
	void initButton(sf::Font& font);


public:

	TextureSelecter(float x, float y, float width, float height, sf::Vector2f gridSize, const sf::Texture* textureSheet, sf::Font& font);

	~TextureSelecter();
	

	//Modifier;
	void setSelectorRectPos(sf::IntRect rect);
	void setSelectorRectTexture(sf::IntRect& rect);
	void moveSprite(float x, float y);
	void setGridChange(const bool change);

	//Accessor:
	const bool getGridChange();
	const sf::IntRect& getChangedGridRect();

	//Functions
	const bool& getActive();
	const sf::IntRect getTextureRext();


	//Update Functions:
	void calculatePosition(float x, float y, const float& dt);
	void updatePosition(const float& dt);
	void updateKeyBoardInput();
	void updateButton(const sf::Vector2i& mousePosWindow);
	void updateGridSelector(const sf::Vector2i& mousePosWindow);
	void updateTextureSelector(const sf::Vector2i& mousePosWindow);
	void update(const sf::Vector2i& mousePosWindow, const float& dt);
	void render(sf::RenderTarget& target);

};


class ProgressBar
{
private:
	std::string barString;
	float maxWidth;
	sf::RectangleShape back;
	sf::RectangleShape inner;

public:
	ProgressBar(float x, float y, float width, float height,
		sf::Color inner_color, sf::VideoMode& vm);
	~ProgressBar();

	//Accessors

	//Modifiers

	//Functions
	void update(const int current_value, const int max_value);
	void render(sf::RenderTarget& target);
};




class TextHolder {
private:
	sf::RectangleShape inputBox;
	sf::Text* inputText;
	sf::Font* font;
	std::string inputString;
	std::string placeholderText;
	bool isActive;
	bool isNumericOnly;

public:
	TextHolder(float x, float y, float width, float height, sf::Font& font,
		const std::string& placeholder, unsigned short chrSize, bool numericOnly = false);
	~TextHolder();

	// Accessors
	sf::Vector2f getPos() const;
	sf::Vector2f getSize() const;
	const std::string& getInputString() const;
	bool getActive() const;

	// Modifiers
	void setActive(bool active);
	void setInvalid();
	void clearField();

	// Functions
	void updateInput(const sf::Event& event);
	void update(const sf::Vector2i& mousePosWin);
	void render(sf::RenderTarget& target);
};





class DialogBox {

public:

	sf::RectangleShape panel;
	sf::Font* font;
	sf::Text* placeHolderText;

	TextHolder* pngPathHolder;
	TextHolder* gridXHolder;
	TextHolder* gridYHolder;
	TextHolder* mapXHolder;
	TextHolder* mapYHolder;

	std::string pngPath;
	float gridSizeX;
	float gridSizeY;
	unsigned worldSizeX;
	unsigned worldSizeY;

	gui::Button* enterButton;
	gui::Button* clearButton;


	DialogBox(float x, float y, float width, float height, sf::Font& font, const std::string placeHolderText, unsigned short chrSize);

	~DialogBox();


	void updateInput(sf::Vector2i& mousePosWin, const sf::Event& event);
	void update(sf::Vector2i& mousePosWin);

	void render(sf::RenderTarget& target);

	void clearAllFields();

};

class FileLoader {
public:
	sf::RectangleShape panel;
	sf::Font* font;
	sf::Text* titleText;
	TextHolder* pathHolder;
	gui::Button* enterButton;
	gui::Button* closeButton;


	std::string mapPath;

	FileLoader(float x, float y, float width, float height, sf::Font& font, unsigned short chrSize);
	~FileLoader();

	void updateInput(sf::Vector2i& mousePosWin, const sf::Event& event);
	void update(sf::Vector2i& mousePosWin);
	void render(sf::RenderTarget& target);
	void clearField();

	const std::string& getMapPath() const;
};

};



