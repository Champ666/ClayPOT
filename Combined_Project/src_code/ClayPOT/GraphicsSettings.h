#pragma once


class GraphicsSettings {


public:

	std::string title;
	sf::VideoMode resolution;
	unsigned resolutionIndex;
	bool fullScreen;
	bool verticleSync;
	unsigned frameLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;


	GraphicsSettings();
	~GraphicsSettings();


	void saveToFile(const std::string path) const;
	void loadFromFile(const std::string path);


};


