#pragma once
#include "BehaviourTree.h"

class BTNode;

class SelectorNode : public BTNode {

private:
	std::vector<std::unique_ptr<BTNode>> children;


public:

	void initialize(AIBlackBoard* bb, Entity* e) override {
		BTNode::initialize(bb, e);
		for (auto& child : children) {
			child->initialize(bb, e);
		}
	}

	void addChild(std::unique_ptr<BTNode> child) {
		this->children.push_back(std::move(child));
	}

	BTResult execute(const float& dt) override {

		for (auto& it : this->children) {
			auto result = it->execute(dt);
			if (result == BTResult::RUNNING || result == BTResult::SUCCESS) {
				return result;
			}
		}

		return BTResult::FAILURE;

	}

};


class SequenceNode : public BTNode {

private:
	std::vector<std::unique_ptr<BTNode>> children;


public:

	void initialize(AIBlackBoard* bb, Entity* e) override {
		BTNode::initialize(bb, e);
		for (auto& child : children) {
			child->initialize(bb, e);
		}
	}

	void addChild(std::unique_ptr<BTNode> child) {
		this->children.push_back(std::move(child));
	}

	BTResult execute(const float& dt) override {

		for (auto& it : this->children) {
			auto result = it->execute(dt);

			if (result == BTResult::FAILURE) {
				return BTResult::FAILURE;
			}

			if (result == BTResult::RUNNING) {
				return BTResult::RUNNING;
			}

		}

		return BTResult::SUCCESS;

	}

};
