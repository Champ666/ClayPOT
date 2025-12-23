#pragma once

class Entity;


class AIBlackBoard
{

private:
	std::unordered_map<std::string, std::any> store;


public:
	AIBlackBoard() = default;
	~AIBlackBoard() = default;

	//Getter & Setters
	
	//This fn is to set the val for each Property, e.g:
	// "Health" --> 100 (int) , "Name" --> "Lucifer" (string) , "Target" --> Someone (Entity)
	void set(const std::string& key, const std::any& val);

	//This would return that particular property for specific key:
	template <typename T>
	std::optional<T> get(const std::string& key)const;

	//To check if the key has some val:
	bool has(const std::string& key)const;

	//This is spcifically for setting the target, means if we want to set target and modify the target for npc we would use this:
	//And target is always and entity
	void setTarget(Entity* e);

	//This is to get the particular target:
	Entity* getTarget()const;



};

template <typename T>
std::optional<T>
AIBlackBoard::get(const std::string& key) const
{
	auto it = store.find(key);
	if (it == store.end()) return std::nullopt;
	try {
		return std::any_cast<T>(it->second);
	}
	catch (...) {
		return std::nullopt;
	}
}

