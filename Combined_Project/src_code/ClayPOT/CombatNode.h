#pragma once
#include "BehaviourTree.h"
#include "Entity.h"


class BehaviourTree;
class Entity;

class SimpleAttackNode : public BTNode {
public:
	SimpleAttackNode() {}

	BTResult execute(const float& dt) override {
		if (!owner) return BTResult::FAILURE;

		if (attackToggle) {
			std::cout << "[AI] NPC " << owner->getId() << " performs Attack 1!\n";
		}
		else {
			std::cout << "[AI] NPC " << owner->getId() << " performs Attack 2!\n";
		}
		attackToggle = !attackToggle;
		return BTResult::SUCCESS;
	}

private:
	bool attackToggle = false;
};

// Enemy basic attack (placeholder, Day 5 will expand)
class AttackNode : public BTNode {
public:
	AttackNode(float cooldown) : cooldown(cooldown) {}

	BTResult execute(const float& dt) override {
		if (!owner) return BTResult::FAILURE;

		timer += dt;
		if (timer < cooldown) return BTResult::RUNNING;

		timer = 0.f;
		std::cout << "[AI] Enemy " << owner->getId() << " attacks viciously!\n";
		return BTResult::SUCCESS;
	}

private:
	float cooldown;
	float timer = 0.f;
};
