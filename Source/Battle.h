#ifndef BATTLE_H
#define BATTLE_H
#include "GameObject.h"
#include "ObjectFactory.h"
class Battle
{
public:
	Battle();
	~Battle();
	void setSlectedSpace(GameObject* space) {
		slectedSpace = space;
	};
	void setSlectedPlayer(GameObject* player)
	{
		slectedPlayer = player;
	};
	void setTarget(GameObject* target)
	{
		this->Target = target;
	}
	GameObject* getPlayer()
	{
		return slectedPlayer;
	}
	GameObject* getSpace() { return slectedSpace; };
	GameObject* getTarget(){ return Target; };
	void clearLists()
	{
		players.clear();
		enemys.clear();
		allys.clear();
	}
	vector<GameObject*>getAlly() { return allys; };
	vector<GameObject*>getEnemys() { return enemys; };
	vector<GameObject*>getPlayers() { return players; };

	void addPlayer(GameObject* player) { players.push_back(player); };
	void addEnemy(GameObject* enemy) { enemys.push_back(enemy); };
	void addAlly(GameObject* ally) { allys.push_back(ally); };

	bool isPlayerInSpace(GameObject* space);
	void update();
	void updateEnemyList();
	void moveToSpace();
	void moveToAttack();
	void caculateDamage(int ability);
	float critCheck();
	bool accracyCheck(int mod);
	void speedCheck();
	void swap(int i, int j);
	void nextTurn();
	GameObject* getPlayerById(string id);


	void bubblesort();

private:
	GameObject* slectedSpace;
	GameObject* slectedPlayer;
	GameObject* Target;


	vector<GameObject*> enemys;
	vector<GameObject*>players;
	vector<GameObject*>allys;

	vector<string>TurnList;
	int abilSlected = 1;
	int m_Turn;
	int currentTurn = 0;

};
#endif // !BATTLE_H
