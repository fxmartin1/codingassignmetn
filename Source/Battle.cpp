#include "Battle.h"
#include "GameObject.h"
#include "RidgidBodyComponent.h"
#include "Component.h"
#include "Stats.h"
#include "Definitions.h"
#include "Equipment.h"
#include "Ability.h"

#include <chrono>
#include <random>
Battle::Battle()
{
	
}

Battle::~Battle()
{
	
}

bool Battle::isPlayerInSpace(GameObject* space)
{
	float pX;
	float pY;
	float sX;
	float sY;

	RidgidBody* sbody = space->getComponent<RidgidBody>();
	RidgidBody* pbody = slectedPlayer->getComponent<RidgidBody>();
	pX = pbody->position->x;
	pY = pbody->position->y;
	sX = sbody->position->x;
	sY = sbody->position->y;
	if (pX == sX && sY == pY)
	{
		return true;
	}
	return false;
}
void Battle::update()
{
	speedCheck();
	if (slectedPlayer == nullptr)
	{
		for (int i = 0; i < players.size(); i++)
		{
			if (players[i]->primaryId == TurnList[currentTurn])
			{
				slectedPlayer = players[i];
				
			}
		}
	}
	if (slectedPlayer != nullptr)
	{
		abilSlected = slectedPlayer->getComponent<Ability>()->getCurrentAbility();
	}
	if (slectedPlayer != nullptr && slectedSpace != nullptr && Target==nullptr)
	{

		moveToSpace();
	}
	if (slectedPlayer != nullptr && Target != nullptr)
	{
		moveToAttack();
	}
}
void Battle::moveToAttack()
{
	RidgidBody* body = slectedPlayer->getComponent<RidgidBody>();
	float sx = body->position->x;
	float sy = body->position->y;
	RidgidBody* eBody=Target->getComponent<RidgidBody>();
	float ex=eBody->position->x;
	float ey=eBody->position->y;
	switch (abilSlected)
	{

	case 1:
		if (ex == sx && ey == sy)
		{
			caculateDamage(abilSlected);
			Target = nullptr;
			slectedPlayer = nullptr;
		}
		else if (ex == (sx + 64) && ey == sy)
		{
			caculateDamage(abilSlected);
			Target = nullptr;
			slectedPlayer = nullptr;
		}
		else if (ex == (sx - 64) && ey == sy)
		{
			caculateDamage(abilSlected);
			Target = nullptr;
			slectedPlayer = nullptr;
		}
		else if (ex == sx && ey == (sy + 64))
		{
			caculateDamage(abilSlected);
			Target = nullptr;
			slectedPlayer = nullptr;
		}
		else if (ex == sx && ey == (sy - 64))
		{
			caculateDamage(1);
			Target = nullptr;
			slectedPlayer = nullptr;
		}
		else if (ex == (sx + 64) && ey == (sy + 64))
		{
			caculateDamage(1);
			Target = nullptr;
			slectedPlayer = nullptr;
		}
		else if (ex == (sx + 64) && ey == (sy - 64))
		{
			caculateDamage(1);
			Target = nullptr;
			slectedPlayer = nullptr;
		}
		else if (ex == (sx - 64) && ey == (sy + 64))
		{
			caculateDamage(1);
			Target = nullptr;
			slectedPlayer = nullptr;
		}
		else if (ex == (sx - 64) && ey == (sy - 64))
		{
			caculateDamage(1);
			Target = nullptr;
			slectedPlayer = nullptr;
		}
		if (sx < ex)
		{
			sx = sx + 2;
		}
		else if (sx > ex)
		{
			sx = sx - 2;
		}
		else if (sy < ey)
		{
			sy = sy + 2;
		}
		else if (sy > ey)
		{
			sy = sy - 2;
		}
		break;
	case 2:
		caculateDamage(1);
		Target = nullptr;
		slectedPlayer = nullptr;
		break;
	}
	if (Target != nullptr && slectedPlayer != nullptr)
	{
		slectedPlayer->getComponent<RidgidBody>()->position->x = sx;
		slectedPlayer->getComponent<RidgidBody>()->position->y = sy;
	}
	
}

void Battle::moveToSpace()
{
	float pX;
	float pY;
	float sX;
	float sY;
	RidgidBody* sbody = slectedSpace->getComponent<RidgidBody>();
	RidgidBody* pbody = slectedPlayer->getComponent<RidgidBody>();
	pX = pbody->position->x;
	pY = pbody->position->y;
	sX = sbody->position->x;
	sY = sbody->position->y;

	if (pX < sX)
	{
		pX = pX + 2;
	}
	else if (pX > sX)
	{
		pX = pX - 2;
	}
	else if (pY < sY)
	{
		pY = pY + 2;
	}
	else if (pY > sY)
	{
		pY = pY - 2;
	}
	slectedPlayer->getComponent<RidgidBody>()->position->x = pX;
	slectedPlayer->getComponent<RidgidBody>()->position->y = pY;
	if (pX == sX && pY == sY)
	{
		slectedPlayer = nullptr;
		slectedSpace = nullptr;
	}

}

void Battle::caculateDamage(int abillty)
{
	int health = Target->getComponent<Stats>()->getHealth();
	int sAttack = slectedPlayer->getComponent<Stats>()->getAtt();
	int tAttack = slectedPlayer->getComponent<Stats>()->getAtt();
	tAttack + (tAttack * (slectedPlayer->getComponent<Equipment>()->getWeapon()->TrustAttack * .01));
	sAttack = sAttack + (sAttack*(slectedPlayer->getComponent<Equipment>()->getWeapon()->slashAttack*.01));
	int tSlashDef = Target->getComponent<Equipment>()->getArmor()->slashDef * .01;
	int tThrustDef= Target->getComponent<Equipment>()->getArmor()->trustDef * .01;
	int attack;

	switch (abilSlected)
	{
	case 1:
		attack = sAttack - (sAttack * tSlashDef);
		attack = (attack + (attack * critCheck())) * accracyCheck(100);
		health = health- attack;
		Target->getComponent<Stats>()->setHealth(health);

	case 2:
		attack = tAttack - (tAttack * tThrustDef);
		attack = (attack + (attack * critCheck())) * accracyCheck(100);
		health = health - attack;
		Target->getComponent<Stats>()->setHealth(health);
	}
}

float Battle::critCheck()
{
	float rate = slectedPlayer->getComponent<Stats>()->getCriticalRate();
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::uniform_real_distribution<float> distribution(0.0, 100.0);
	float num=distribution(generator);
	if (rate >= num)
	{
		return slectedPlayer->getComponent<Stats>()->getCritDamage() * .01;
	}
	else
	{
		return 0;
	}
}

bool Battle::accracyCheck(int mod)
{
	int tEvas = Target->getComponent<Stats>()->getEvvasion();
	int acc = slectedPlayer->getComponent<Stats>()->getAccracy();

	int chance = mod + tEvas - acc;
	float rate = slectedPlayer->getComponent<Stats>()->getCriticalRate();
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::uniform_real_distribution<float> distribution(0.0, 100.0);
	float num = distribution(generator);
	if (num <= mod)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}
void Battle::speedCheck()
{
	bubblesort();
	vector<GameObject*> newlist;
	vector<GameObject*> templist;

	
	for (int i = 0; i < players.size(); i++)
	{
		newlist.push_back(players[i]);
	}
	int num = newlist.size() - 1;
	templist.push_back(newlist[newlist.size()-1]);
	newlist.pop_back();
	while (!newlist.empty())
	{
		int remain;
		int count = 0;
		for (int i = 0; i < templist.size(); i++)
		{
		 remain =templist[i]->getComponent<Stats>()->getSpeed()/newlist[newlist.size()-1]->getComponent<Stats>()->getSpeed() ;
			count = 0;
			for (int j = 0; j < templist.size(); j++)
			{
				if (templist[i]->primaryId == templist[j]->primaryId)
				{
					count++;
				}
			}
			if (count != remain)
			{
				templist.push_back(templist[i]);
			}
		}
		templist.push_back(newlist[newlist.size() - 1]);
		newlist.pop_back();
	}
	TurnList.clear();
	for (int i = 0; i < templist.size(); i++)
	{
		TurnList.push_back(templist[i]->primaryId);
	}
	m_Turn = TurnList.size()-1;
}
void Battle::bubblesort()
{
	int i, j;
	for (i = 0; i < players.size() - 1; i++)

		// Last i elements are already in place  
		for (j = 0; j < players.size() - i - 1; j++)
			if (players[j]->getComponent<Stats>()->getSpeed() > players[j + 1]->getComponent<Stats>()->getSpeed())
				swap(j, j + 1);
}
void Battle::swap(int i, int j)
{

	GameObject* temp = players[i];
	players[i] = players[j];
	players[j] = temp;
}

void Battle::nextTurn()
{
	slectedPlayer = nullptr;
	if (currentTurn == m_Turn)
	{
		currentTurn == 0;
	}
	else
	{
		currentTurn++;
	}


}

GameObject* Battle::getPlayerById(string id)
{
	for (int i = 0; i < players.size(); i++)
	{
		if (id == players[i]->primaryId)
		{
			return players[i];
		}
	}
	return nullptr;
}