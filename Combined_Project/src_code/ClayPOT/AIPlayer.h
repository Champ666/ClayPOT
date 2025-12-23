#pragma once
#include "Entity.h"
#include "AIComponent.h"4
#include "CompositeNodes.h"
#include "TestNode.h"
#include "TaskNodes.h"
#include "TaskManager.h"
#include "ActionNodes.h"
#include "DeathNode.h"
#include "AIManager.h"
#include "RoutineNodes.h"
#include "CombatNodes.h"
#include "AStarComponent.h"
#include "SoundLibrary.h"


class AIComponent;
class BehaviourTree;
class BTNode;
class SequenceNode;
class PrintNode;
class WaitNode;
class PrintNode;
class GetTaskNode;
class FindPathNode;
class PerformTaskNode;
class RestNode;
class IsDeadNode;
class DieNode;
class AIManager;
class AStarComponenet;


class AIPlayer :
    public Entity
{
private:

	static int id;
	int currentid;
	int maxX;
	Entity* player;

	//Timer
	float timer = 0.f;
	float timerMax = 0.5f;
	bool tick = true;



protected:
	std::unique_ptr<AIComponent> aiComponent;
	AttackComponent attackComponent;
	AStarComponent* aStarComponent;

	
	void initVariables(float x, float y, float width, float height, int maxX);
	void initAnimations();
	void initAStarComponent(std::vector<std::vector<int>>& graph);
	void initComponents(sf::Texture&, AIManager* aiManager, std::vector<std::vector<int>>& graph);
	void initAIComponent(AIManager* aiManager);


public:

	sf::Vector2i spawnPosition;
	sf::Vector2i targetPosition;
	bool chaseMode = false;

    AIPlayer(float x, float y, float width, float height, sf::Texture& texture_sheet,
		AIManager* aiManager, std::vector<std::vector<int>>& graph, int maxX, Entity* player);
    virtual ~AIPlayer();


	//renders:
	virtual void render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox = false);


	//updates:
	sf::Vector2f nextPosition(int index);
	void resolveVelocity(const float& dt, std::vector<int> path);
	void updateInput();
	void updateTimer(const float& dt);
	virtual void update(const float& dt, sf::Vector2f& mousePos);

	//getter & setter
	AttackComponent* getAttackComponent() { return &attackComponent; }
	const int getId() override;

	virtual void markForRemoval() override;
	virtual bool isMarkedForRemoval() const override;


};

