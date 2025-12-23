#pragma once
#include "Task.h"

struct Routine {
	std::string name;                 // e.g. "WorkerMorning"
	std::vector<Task> tasks;          // tasks to perform in this routine
	sf::Vector2i home;                // rest/home position
	float restDuration;               // how long to rest after all tasks
};
