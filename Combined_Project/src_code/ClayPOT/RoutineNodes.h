// src/AI/RoutineNodes.h
#pragma once
#include "BehaviourTree.h"
#include "AIBlackboard.h"
#include "RoutineManager.h"


// Checks which routine to run
class CheckRoutineNode : public BTNode {
public:
	CheckRoutineNode(RoutineManager* manager) : manager(manager) {}

	BTResult execute(const float& dt) override {
		if (!manager) return BTResult::FAILURE;
		Routine* routine = manager->getCurrentRoutine();
		if (!routine) return BTResult::FAILURE;

		blackBoard->set("currentRoutine", *routine);
		std::cout << "[AI] Running routine: " << routine->name << "\n";
		return BTResult::SUCCESS;
	}

private:
	RoutineManager* manager;
};

// After finishing all tasks, rest then go home
class ReturnHomeNode : public BTNode {
public:
	ReturnHomeNode(float speed) : speed(speed) {}

	BTResult execute(const float& dt) override {
		auto routineOpt = blackBoard->get<Routine>("currentRoutine");
		if (!routineOpt.has_value()) return BTResult::FAILURE;

		auto home = routineOpt->home;
		sf::Vector2f homePos(home.x * 32.f, home.y * 32.f);
		auto myPos = owner->getPosition();

		float dx = homePos.x - myPos.x;
		float dy = homePos.y - myPos.y;
		float dist = std::sqrt(dx * dx + dy * dy);

		if (dist < 5.f) {
			std::cout << "[AI] Reached home.\n";
			return BTResult::SUCCESS;
		}

		float nx = dx / dist;
		float ny = dy / dist;
		owner->move(nx * speed, ny * speed, dt);
		return BTResult::RUNNING;
	}

private:
	float speed;
};
