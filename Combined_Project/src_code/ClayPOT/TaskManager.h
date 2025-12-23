// src/AI/TaskManager.h
#pragma once
#include "Task.h"

class TaskManager {
public:
	void addTask(const Task& t) {
		tasks.push(t);
	}

	bool hasTask() const { return !tasks.empty(); }

	Task getNextTask() {
		if (tasks.empty()) throw std::runtime_error("No tasks!");
		Task t = tasks.front();
		tasks.pop();
		return t;
	}

private:
	std::queue<Task> tasks;
};
