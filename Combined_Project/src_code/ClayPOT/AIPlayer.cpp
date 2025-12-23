#include "stdafx.h"
#include "AIPlayer.h"


int AIPlayer::id = 0;



void AIPlayer::initVariables(float x, float y, float width, float height, int maxX)
{
	this->spawnPosition = sf::Vector2i({ static_cast<int>(x), static_cast<int>(y)});
	this->targetPosition = spawnPosition;
	this->setPosition(x*64, y*64);
	this->setSize(width, height);
	AIPlayer::id++;
	this->currentid = AIPlayer::id;
	this->maxX = maxX;
}

void AIPlayer::initAnimations()
{

	this->animationComponent->addAnimation("IDLE", 6.f, 0, 0, 2, 0, 61, 57); 

	this->animationComponent->addAnimation("WALK_DOWN", 6.f, 0, 0, 2, 0, 61, 57);

	this->animationComponent->addAnimation("WALK_LEFT", 32.f, 0, 1, 2, 1, 61, 57);

	this->animationComponent->addAnimation("WALK_RIGHT", 32.f, 0, 2, 2, 2, 61, 57);

	this->animationComponent->addAnimation("WALK_UP", 6.f, 0, 3, 2, 3, 61, 57);

	//this->animationComponent->addAnimations("ATTACK", 7.f, 0, 2, 13, 2, 192 * 2, 192);

}


void AIPlayer::initAStarComponent(std::vector<std::vector<int>>& graph)
{
	this->aStarComponent = new AStarComponent(graph, this->maxX);
}

void AIPlayer::initAIComponent(AIManager* aiManager)
{
	// 1️⃣ Death
	auto root = std::make_unique<SelectorNode>();
	// 1️⃣ Death
	auto deathSeq = std::make_unique<SequenceNode>();
	deathSeq->addChild(std::make_unique<IsDeadNode>());
	deathSeq->addChild(std::make_unique<DieNode>());
	root->addChild(std::move(deathSeq));
	// 2️⃣ Routine or task
	auto taskSeq = std::make_unique<SequenceNode>();
	taskSeq->addChild(std::make_unique<GetTaskNode>(&aiManager->taskManager));
	taskSeq->addChild(std::make_unique<PerformTaskNode>());
	taskSeq->addChild(std::make_unique<RestNode>(3.f));
	root->addChild(std::move(taskSeq));

	// 3️⃣ Simple combat (play attack animation)
	auto attackSeq = std::make_unique<SequenceNode>();
	attackSeq->addChild(std::make_unique<SimpleAttackNode>(&attackComponent));
	root->addChild(std::move(attackSeq));
	// 3️⃣ Idle fallback (if no tasks)
	root->addChild(std::make_unique<IdleNode>(2.f));
	this->aiComponent = std::make_unique<AIComponent>(this);
	aiComponent->setBehaviourTree(std::make_unique<BehaviourTree>(std::move(root)));

}

void AIPlayer::initComponents(sf::Texture& texture_Sheet, AIManager* aiManager, std::vector<std::vector<int>>& graph)
{

	this->createMovementComponent(200.f, 1500.0f, 900.f);
	this->createAnimationComponent(texture_Sheet);
	this->createHitboxComponent(15.f, 55.f, 30.f, 10.f);
	this->createAttributeComponent(1);
	this->initAnimations();
	this->initAStarComponent(graph);

}



AIPlayer::AIPlayer(float x, float y, float width, float height, sf::Texture& texture_sheet,
	AIManager* aiManager, std::vector<std::vector<int>>& graph, int maxX, Entity* player) : Entity(texture_sheet), player(player)
{

	this->initVariables(x, y, width, height, maxX);
	this->initComponents(texture_sheet, aiManager, graph);

}

AIPlayer::~AIPlayer()
{
	if(this->aStarComponent)
		delete this->aStarComponent;
}




//Updates & render calls:

sf::Vector2f AIPlayer::nextPosition(int index)
{
	float x = (index % maxX) * 64;
	float y = (index / maxX) * 64;
	return sf::Vector2f({ x, y });
}

void AIPlayer::resolveVelocity(const float& dt, std::vector<int> path)
{
	if (path.size() > 1) {
		int nextPoint = path[1];
		sf::Vector2f nextPos = this->nextPosition(nextPoint);
		sf::Vector2f currentPos = sf::Vector2f( this->getGridPosition().x * 64.0, this->getGridPosition().y * 64.0 );
		sf::Vector2f direction = nextPos - currentPos;
		this->move(dt, direction.x, direction.y);
		std::cout << "AIPLAYER MOVING\n";
	}
	
}

void AIPlayer::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) && tick) {
		this->chaseMode = !this->chaseMode;
		SoundLibrary::playSound("Whistle");
	}
	
	if (!chaseMode) {
		this->targetPosition = this->spawnPosition;
		return;
	}
	else {
		this->targetPosition = this->player->getGridPosition();
		return;
	}
}

void AIPlayer::updateTimer(const float& dt)
{
	if (timer < timerMax) {
		timer += dt;
		tick = false;
		return;
	}
	timer = 0.f;
	tick = true;
}

void AIPlayer::update(const float& dt, sf::Vector2f& mousePos)
{
	this->updateTimer(dt);
	this->updateInput();
	if (hitboxComponent)
		this->hitboxComponent->update();
	if (movementComponent)
		this->movementComponent->update(dt);
	if (aStarComponent) {
		std::vector<int> path = this->aStarComponent->findPath(this->getGridPosition(), targetPosition);
		this->resolveVelocity(dt, path);
	}
	this->updateAnimations(dt);
}

const int AIPlayer::getId()
{
	return this->currentid;
}

void AIPlayer::markForRemoval()
{
	this->markedForRemoval = true;
}

bool AIPlayer::isMarkedForRemoval() const
{
	return this->markedForRemoval;
}

void AIPlayer::render(sf::RenderTarget& target, sf::Shader* shader, const bool show_hitbox)
{
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getSpritePosition());
		target.draw(this->sprite, shader);
	}
	else
		target.draw(this->sprite);

	if (show_hitbox)
		this->hitboxComponent->render(target);
}


