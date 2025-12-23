#include "stdafx.h"
#include "FontLibrary.h"

//static std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts;
//static std::unordered_map<std::string, std::unique_ptr<sf::Text>> texts;
//
//void FontLibrary::loadFont(const std::string& fontId, const std::string& filename)
//{
//	fonts[fontId] = std::make_unique<sf::Font>();
//	if (!fonts[fontId]->openFromFile(filename)) {
//		throw std::runtime_error("Failed to load font: " + filename);
//	}
//}
//
//void FontLibrary::setText(const std::string& fontId, const std::string& textID, std::string text, 
//						 unsigned short charSize, sf::Color color, sf::Vector2f position)
//{
//	texts[textID] = std::make_unique<sf::Text>(fonts[fontId]);
//
//}
//
//void FontLibrary::displayText(const std::string& id, sf::RenderTarget& target)
//{
//
//}
