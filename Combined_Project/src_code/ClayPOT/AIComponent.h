#pragma once
#include "AIBlackBoard.h"
#include "BehaviourTree.h"

class BehaviorTree; // forward
class Entity;

class AIComponent
{



private:



protected:


	Entity* owner;
	std::unique_ptr<AIBlackBoard> blackBoard;
	std::unique_ptr<BehaviourTree> behaviourTree;

	float tickRate = 0.1f;
	float tickAccumulator = 0;
	bool active = true;

public:

	//We are declaring the explicit constructor which it to explicity define the owner of that compenent that forces user to define the any kind of 
	//Owner
	explicit AIComponent(Entity* owner);
	virtual ~AIComponent();

	//Normal getters and setter:
	AIBlackBoard* getBlackboard() { return blackBoard.get(); }
	void setTickRate(float t) { tickRate = t; }
	void setActive(bool a) { active = a; }
	Entity* getOwner() const { return owner; }

	void setBehaviourTree(std::unique_ptr<BehaviourTree> bt);


	//Updating the brain what to do:
	void update(const float& dt);



};

