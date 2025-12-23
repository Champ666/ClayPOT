// src/AI/RoutineManager.h
#pragma once
#include "Routine.h"

class RoutineManager {
public:
	std::vector<Routine> routines;
	int currentRoutineIndex = 0;

	void addRoutine(const Routine& r) {
		routines.push_back(r);
	}

	Routine* getCurrentRoutine() {
		if (routines.empty()) return nullptr;
		return &routines[currentRoutineIndex];
	}

	void nextRoutine() {
		currentRoutineIndex = (currentRoutineIndex + 1) % routines.size();
	}
};
