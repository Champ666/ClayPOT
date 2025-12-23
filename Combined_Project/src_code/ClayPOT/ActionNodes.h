#pragma once

#include "BehaviourTree.h"

class IdleNode : public BTNode {
public:
	IdleNode(float duration) : duration(duration), elapsed(0.f) {}

	void reset() override { elapsed = 0.f; }

	BTResult execute(const float& dt) override {
		elapsed += dt;
		if (elapsed >= duration) {
			std::cout << "[AI] Finished idling.\n";
			elapsed = 0.f;
			return BTResult::SUCCESS;
		}
		std::cout << "[AI] Idling... (" << elapsed << "s)\n";
		return BTResult::RUNNING;
	}

private:
	float duration;
	float elapsed;
};

