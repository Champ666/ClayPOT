#pragma once
enum class TaskType { CHOP, CLEAN, CARRY, FARM, REST };

struct Task {
	TaskType type;
	sf::Vector2i position;   // target tile
	float duration;          // how long to perform
	sf::Vector2i home;       // NPC's home tile

	Task(TaskType type, sf::Vector2i pos, float dur, sf::Vector2i home)
		: type(type), position(pos), duration(dur), home(home) {
	}
};

