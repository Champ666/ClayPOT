#include "stdafx.h"
#include "AIComponent.h"

AIComponent::AIComponent(Entity* owner) : owner(owner), blackBoard(std::make_unique<AIBlackBoard>())
{
	if (blackBoard) {
		this->blackBoard->set("owner", owner);//Note book writing who is the owner of that brain
	}
}

AIComponent::~AIComponent()
{
	//No need for manual memory management smart pointer will do it automatically
}

void AIComponent::setBehaviourTree(std::unique_ptr<BehaviourTree> bt)
{
	this->behaviourTree = std::move(bt);
	if (behaviourTree && blackBoard) {
		//this is setting the behaviour tree the behaviour tree need to know the context of AI so sending the noteBook and the owner
		this->behaviourTree->setContext(this->blackBoard.get(), this->owner);
	}
}

void AIComponent::update(const float& dt)
{
	if (!active) return;

	tickAccumulator += dt;
	if (tickAccumulator < tickRate) {
		return;
	}
	tickAccumulator = 0.f;


	if (behaviourTree) {
		this->behaviourTree->tick(tickRate);
	}

}
