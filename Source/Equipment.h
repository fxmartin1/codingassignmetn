#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Component.h"
#include "ObjectFactory.h"
#include "tinyxml2.h"
#include <string>

class Equipment:public Component
{
public:
	Equipment(GameObject* owner, tinyxml2::XMLElement* componentElement);
	~Equipment();

	void start();
	GameObject* update();
	void finish();
	void updateStats();

	void setChangeEquip(bool changeEquip)
	{
		this->changeEquip = changeEquip;
	}

	Weapon* getWeapon()
	{
		return weapon;
	}
	Armor* getArmor()
	{
		return armor;
	}
private:
	bool changeEquip=false;
	string helmet="none";
	string chest="iron";
	string leggings="iron";
	string boots="iron";
	int wep = 1;
	int arm = 1;
	string weapon2="steelSheild";


	Weapon* weapon;
	Armor* armor;
};

#endif