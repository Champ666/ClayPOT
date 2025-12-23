#pragma once
class SoundLibrary
{
public:

	// Load a sound into memory (static)
	static void loadSound(const std::string& id, const std::string& filename);
	static void loadMusic(const std::string& id, const std::string& filename);

	// Play a loaded sound (static)
	static void playSound(const std::string& id);
	static void playMusic(const std::string& id);
	static void stopMusic(const std::string& id);

private:
	SoundLibrary() = delete;  // prevent object creation

	static std::unordered_map<std::string, sf::SoundBuffer> buffers;
	static std::unordered_map<std::string, std::unique_ptr<sf::Sound>> sounds;
	static std::unordered_map<std::string, sf::Music> music;
};

