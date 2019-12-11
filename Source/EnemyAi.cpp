#include"EnemyAi.h"
#include <chrono>
#include <random>
#include"Stats.h"
#include"MoveSpace.h"
#include"RidgidBodyComponent.h"


EnemyAi::EnemyAi(GameObject* owner, tinyxml2::XMLElement* componentElement, Battle* battle) : Component(owner)
{
	this->battle = battle;
}

EnemyAi::~EnemyAi()
{

}

void EnemyAi::start()
{

}

GameObject* EnemyAi::update()
{
	if (getOwner()->getComponent<Stats>()->getMoveSpace() == 0)
	{
		battle->nextTurn();
		getOwner()->getComponent<Stats>()->movementSpaces = getOwner()->getComponent<Stats>()->m_MovementSpaces;
	}
	if (battle->getPlayer() == getOwner())
	{


		if (target == nullptr )
		{
			getTarget();
		}

		if (getOwner()->getComponent<Stats>()->getHealth() > (getOwner()->getComponent<Stats>()->getHealth() - (getOwner()->getComponent<Stats>()->getHealth() * .2)))
		{
			moveToPlayer();
		}
		
	}
	return nullptr;
}

void EnemyAi::finish()
{

}
void EnemyAi::getTarget()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	float size = battle->getAlly().size() - 1;
	std::uniform_real_distribution<float> distribution(0.0, size);
	int num = distribution(generator);
	target = battle->getAlly()[num];
}

void EnemyAi::moveToPlayer()
{
	GameObject* closestSpace=NULL;
	int distance;
	int tempDistance=-1;
	

	int sX;
	int sY;
	int pX;
	int pY;
	for (int i = 0; i < getOwner()->getComponent<MoveSpace>()->getSpaces().size(); i++)
	{
		sX = getOwner()->getComponent<MoveSpace>()->getSpaces()[i]->getComponent<RidgidBody>()->position->x;
		sY = getOwner()->getComponent<MoveSpace>()->getSpaces()[i]->getComponent<RidgidBody>()->position->y;
		pX = target->getComponent<RidgidBody>()->position->x;
		pY = target->getComponent<RidgidBody>()->position->y;
		distance = sqrt(pow((sX - pX), 2) + pow((sY - pY), 2));
		if (tempDistance == -1)
		{
			closestSpace = getOwner()->getComponent<MoveSpace>()->getSpaces()[i];
			tempDistance = distance;
		}
		else if(distance<tempDistance)
		{
			closestSpace = getOwner()->getComponent<MoveSpace>()->getSpaces()[i];
			tempDistance = distance;
		}
	}
	battle->setSlectedSpace(closestSpace);
}