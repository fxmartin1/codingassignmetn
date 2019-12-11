#include"Equipment.h"
#include"Stats.h"

Equipment::Equipment(GameObject* owner, tinyxml2::XMLElement* componentElement) :Component(owner)
{
	float w;
	float a;
	componentElement->QueryFloatAttribute("w", &w);
	componentElement->QueryFloatAttribute("a", &a);

	wep = w;
	arm = a;
	if (wep != NULL)
	{
		updateStats();
	}

	if (arm != NULL)
	{
		updateStats();
	}
}

Equipment::~Equipment()
{

}

void Equipment::start()
{

}

GameObject* Equipment::update()
{
	
	return nullptr;
}

void Equipment::finish()
{

}

void Equipment::updateStats()
{
	//weapons
	
	switch (wep)
	{
	case 1:
		Weapon* steelSword=new Weapon();
		steelSword->slashAttack = 60;
		steelSword->bluntAttack = 5;
		steelSword->TrustAttack = 60;
		steelSword->fireAttack = 0;
		steelSword->forstAttack = 0;
		steelSword->abssAttack = 0;
		steelSword->lightningAttack = 0;
		steelSword->holyAttack = 0;
		steelSword->durability = 200;

		weapon = steelSword;

	}

	switch (arm)
	{
	case 1:
		Armor * crab= new Armor();
		crab->slashDef = 30;
		crab->trustDef = 0;
		crab->bluntDef = 50;
		crab->fireDef = 0;
		crab->lightningDef = 0;
		crab->forstDef = 0;
		crab->abssDef = 0;
		crab->holyDef = 0;
		crab->magicDef = 0;
		armor = crab;
		break;

	}
}