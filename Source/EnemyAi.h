#ifndef ENEMYAI_H
#define ENEMYAI_H
#include"Component.h"
#include"Battle.h"
class EnemyAi:public Component
{
public:
	EnemyAi(GameObject* owner, tinyxml2::XMLElement* componentElement, Battle* battle);
	~EnemyAi();
	void start();
	GameObject* update();
	void finish();
	void behaviorTree();
	void moveToPlayer();
	void getTarget();
private:
	Battle* battle;
	GameObject* target;
};

#endif