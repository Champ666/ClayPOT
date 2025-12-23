// src/AI/TaskNodes.h
#pragma once
#include "BehaviourTree.h"
#include "AIBlackboard.h"
#include "TaskManager.h"


class BTNode;
// Pick a task from TaskManager
class GetTaskNode : public BTNode {
public:
	GetTaskNode(TaskManager* manager) : manager(manager) {}

	BTResult execute(const float& dt) override {
		if (!manager || !manager->hasTask()) return BTResult::FAILURE;

		Task t = manager->getNextTask();
		this->blackBoard->set("currentTask", t);
		std::cout << "[AI] Got new task!\n";
		return BTResult::SUCCESS;
	}

private:
	TaskManager* manager;
};

// Perform task at location
class PerformTaskNode : public BTNode {
public:
	PerformTaskNode() {}

	void reset() override { elapsed = 0.f; }

	BTResult execute(const float& dt) override {
		auto taskOpt = this->blackBoard->get<Task>("currentTask");
		if (!taskOpt.has_value()) return BTResult::FAILURE;

		elapsed += dt;
		if (elapsed >= taskOpt->duration) {
			std::cout << "[AI] Finished task!\n";
			elapsed = 0.f;
			return BTResult::SUCCESS;
		}
		return BTResult::RUNNING;
	}

private:
	float elapsed = 0.f;
};

// Rest at home or at task location
class RestNode : public BTNode {
public:
	RestNode(float dur) : duration(dur) {}

	void reset() override { elapsed = 0.f; }

	BTResult execute(const float& dt) override {
		elapsed += dt;
		if (elapsed >= duration) {
			std::cout << "[AI] Finished resting.\n";
			return BTResult::SUCCESS;
		}
		return BTResult::RUNNING;
	}

private:
	float duration;
	float elapsed = 0.f;
};
