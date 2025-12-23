#pragma once

#include "BehaviourTree.h"
#include "Entity.h"


class BehaviourTree;
class Entity;

class IsDeadNode : public BTNode {
public:
	BTResult execute(const float& dt) override {
		if (!owner) return BTResult::FAILURE;
		return (owner->isDead()) ? BTResult::SUCCESS : BTResult::FAILURE;
	}
};

class DieNode : public BTNode {
public:
	BTResult execute(const float& dt) override {
		if (!owner) return BTResult::FAILURE;
		std::cout << "[AI] Entity " << owner->getId() << " died.\n";
		owner->markForRemoval(); // implement in Entity/EntityManager
		return BTResult::SUCCESS;
	}
};
