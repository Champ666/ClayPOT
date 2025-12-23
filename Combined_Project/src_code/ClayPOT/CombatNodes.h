// src/AI/CombatNodes.h
#pragma once
#include "BehaviourTree.h"
#include "Entity.h"
#include "AttackComponent.h"


class SimpleAttackNode : public BTNode {
public:
	SimpleAttackNode(AttackComponent* attackComp) : attackComp(attackComp) {}

	BTResult execute(const float& dt) override {
		if (!owner || !attackComp)
			return BTResult::FAILURE;

		attackComp->update(dt);

		if (attackComp->canAttack()) {
			std::cout << "[AI] Entity " << owner->getId() << " attacks!\n";
			attackComp->attack();
			return BTResult::SUCCESS;
		}

		return BTResult::RUNNING;
	}

private:
	AttackComponent* attackComp;
};
