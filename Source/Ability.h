#ifndef ABILTY_H
#define ABILITY_H
#include"Component.h"
#include"Battle.h"
#include"ObjectFactory.h"
#include "tinyxml2.h"
class Ability :public Component
{
public:
	Ability(GameObject* owner, tinyxml2::XMLElement* componentElement, Battle* battle,InputHandler* input, ObjectFactory* factory);
	~Ability();
	void start();
	GameObject* update();
	void finish();
	int getCurrentAbility() { return currentAbility; };
private:
	int currentAbility = 2;
	Battle* battle;
	ObjectFactory* factory;
	InputHandler* input;
};
#endif // !ABILTY_H

