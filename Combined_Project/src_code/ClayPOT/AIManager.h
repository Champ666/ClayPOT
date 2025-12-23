// src/AI/AIManager.h (update)
#pragma once
#include "TaskManager.h"
#include "Pathfinding.h"
#include "RoutineManager.h"

class AIManager {
public:
	TaskManager taskManager;
	Pathfinder pathfinder;
	RoutineManager routineManager;

	AIManager(int width, int height, const std::vector<std::vector<int>>& grid)
		: pathfinder(width, height, grid) {
	}

	void initTasks() {
		taskManager.addTask(Task(TaskType::CHOP, { 5, 5 }, 3.f, { 10, 10 }));
		taskManager.addTask(Task(TaskType::CLEAN, { 7, 2 }, 2.f, { 10, 10 }));
		taskManager.addTask(Task(TaskType::CARRY, { 3, 4 }, 4.f, { 10, 10 }));
	}

	void initRoutines() {
		Routine work;
		work.name = "WorkDay";
		work.tasks = {
			Task(TaskType::CHOP, {5,5}, 3.f, {10,10}),
			Task(TaskType::CARRY, {3,4}, 2.f, {10,10})
		};
		work.home = { 10,10 };
		work.restDuration = 3.f;

		routineManager.addRoutine(work);
	}
};
