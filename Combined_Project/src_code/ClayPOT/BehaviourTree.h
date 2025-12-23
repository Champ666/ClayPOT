#pragma once
#include "Entity.h"


class AIBlackBoard;
class Entity;

enum class BTResult {SUCCESS, FAILURE, RUNNING};


class BTNode {

protected:
	std::string name;
	AIBlackBoard* blackBoard = nullptr;
	Entity* owner = nullptr;
public:
	BTNode(const std::string& name = "") : name(name){}
	virtual ~BTNode(){}

	virtual void initialize(AIBlackBoard* bb, Entity* e) {
		this->blackBoard = bb;
		this->owner = e;
	}

	virtual void reset(){}
	virtual BTResult execute(const float& dt) = 0;

};


class BehaviourTree
{
private:
	std::unique_ptr<BTNode> rootNode;

public:
	BehaviourTree(std::unique_ptr<BTNode> root) : rootNode(std::move(root)){}

	void setContext(AIBlackBoard* bb, Entity* owner) {
		rootNode->initialize(bb, owner);
	}
	void tick(const float& dt) {
		if (rootNode) rootNode->execute(dt);
	}

};

