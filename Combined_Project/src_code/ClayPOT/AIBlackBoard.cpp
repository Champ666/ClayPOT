#include "stdafx.h"
#include "AIBlackBoard.h"

void AIBlackBoard::set(const std::string& key, const std::any& val)
{
	store[key] = val;
}

bool AIBlackBoard::has(const std::string& key) const
{
	return store.find(key) != store.end();
}

void AIBlackBoard::setTarget(Entity* e)
{
	this->set("target", e);
}

Entity* AIBlackBoard::getTarget() const
{
	auto v = get<Entity* >("target");

	return v ? *v : nullptr;
}
