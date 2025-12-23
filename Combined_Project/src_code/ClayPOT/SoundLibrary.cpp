#include "stdafx.h"
#include "SoundLibrary.h"


std::unordered_map<std::string, sf::SoundBuffer> SoundLibrary::buffers;
std::unordered_map<std::string, sf::Music> SoundLibrary::music;
std::unordered_map<std::string, std::unique_ptr<sf::Sound>> SoundLibrary::sounds;


void SoundLibrary::loadSound(const std::string& id, const std::string& filename)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filename)) {
		throw std::runtime_error("Failed to load sound: " + filename);
	}

	// Insert buffer
	buffers[id] = std::move(buffer);

	// Create sound and point it to the buffer
	sounds[id] = std::make_unique<sf::Sound>(buffers[id]);
}

void SoundLibrary::loadMusic(const std::string& id, const std::string& filename)
{
	sf::Music sound;
	if (!sound.openFromFile(filename)) {
		std::cerr << "ENGINE::Error: Could not load background music!\n";
		return;
	}
	music[id] = std::move(sound);
}

void SoundLibrary::playSound(const std::string& id)
{
	if (sounds.count(id))
		sounds[id]->play();
}

void SoundLibrary::playMusic(const std::string& id)
{
	music[id].setLooping(true);
	music[id].play();
}

void SoundLibrary::stopMusic(const std::string& id)
{
	music[id].stop();
}
