#include "stdafx.h"
#include "GraphicsSettings.h"


GraphicsSettings::GraphicsSettings() {

	this->title = "Unintialized";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->resolutionIndex = 0;
	this->fullScreen = true;
	this->verticleSync = false;
	this->frameLimit = 120;
	this->contextSettings.antiAliasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();
	std::cout << "In Graphics Settings";
}

GraphicsSettings::~GraphicsSettings() {

}

void GraphicsSettings::saveToFile(const std::string path) const{

	std::ofstream ofs(path);

	if (ofs.is_open()) {

		ofs << title;
		ofs << this->resolution.size.x << " " << this->resolution.size.y;
		ofs << this->fullScreen;
		ofs << this->frameLimit;
		ofs << this->verticleSync;
		ofs << this->contextSettings.antiAliasingLevel;
		
		ofs.close();
	}

}

void GraphicsSettings::loadFromFile(const std::string path) {

	std::ifstream ifs(path);

	if (ifs.is_open()) {

		std::getline(ifs, title);
		ifs >> this->resolution.size.x >> this->resolution.size.y;
		ifs >> this->fullScreen;
		ifs >> this->frameLimit;
		ifs >> this->verticleSync;
		ifs >> this->contextSettings.antiAliasingLevel;
		std::cout << "In Graphics Settings";
		ifs.close();
	}

}