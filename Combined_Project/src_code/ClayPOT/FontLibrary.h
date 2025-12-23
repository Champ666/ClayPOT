#pragma once
class FontLibrary
{
public:

	// Load a Font into memory (static)
	/*static void loadFont(const std::string& id, const std::string& filename);
	static void setText(const std::string& id, const std::string& fontId, std::string text
		, unsigned short charSize, sf::Color color, sf::Vector2f position);
	static void displayText(const std::string& id, sf::RenderTarget& target);*/

private:
	FontLibrary() = delete;  // prevent object creation

	static std::unordered_map<std::string, std::unique_ptr<sf::Font>> fonts;
	static std::unordered_map<std::string, std::unique_ptr<sf::Text>> texts;

};