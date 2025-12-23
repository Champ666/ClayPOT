#pragma once
#include "BehaviourTree.h"

class BTNode;

class PrintNode : public BTNode {
public:
	PrintNode(const std::string& msg) : message(msg) {}
	BTResult execute(const float& dt) override {
		this->owner->move(dt, 0.5f, 0.5f);
		return BTResult::SUCCESS;
	}
private:
	std::string message;
};

// Wait node
class WaitNode : public BTNode {
public:
	WaitNode(float duration) : duration(duration) {}
	void reset() override { elapsed = 0.f; }

	BTResult execute(const float& dt) override {
		elapsed += dt;
		if (elapsed >= duration) {
			elapsed = 0.f;
			return BTResult::SUCCESS;
		}
		return BTResult::RUNNING;
	}
private:
	float duration;
	float elapsed = 0.f;
};

