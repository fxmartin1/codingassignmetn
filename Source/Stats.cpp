#include "Stats.h"
#include "GameObject.h"

Stats::Stats(GameObject* owner, tinyxml2::XMLElement* componentElement) : Component(owner)
{
	float lev;
	float vat;
	float end;
	float str;
	float dex;
	float inte;
	float fai;
	float agi;
	float per;
	float luc;
	
	componentElement->QueryFloatAttribute("lev", &lev);
	componentElement->QueryFloatAttribute("vat", &vat);
	componentElement->QueryFloatAttribute("end", &end);
	componentElement->QueryFloatAttribute("str", &str);
	componentElement->QueryFloatAttribute("int", &inte);
	componentElement->QueryFloatAttribute("fai", &fai);
	componentElement->QueryFloatAttribute("agi", &agi);
	componentElement->QueryFloatAttribute("per", &per);
	componentElement->QueryFloatAttribute("luc", &luc);
	componentElement->QueryFloatAttribute("dex", &dex);

	level = lev;
	vatality = vat;
	endurance = end;
	strength = str;
	intellegance = inte;
	faith = fai;
	agility = agi;
	perception = per;
	this->dex = dex;
	
	caculateStats();
	
}

Stats::~Stats()
{
	

}

void Stats::start()
{

}

GameObject* Stats::update()
{
	if (health <= 0)
	{
		getOwner()->isDead = true;
	}
	return nullptr;
}

void Stats::finish()
{

}

void Stats::caculateStats()
{
	movementSpaces = endurance / 10;
	m_MovementSpaces = movementSpaces;
	health = (vatality * 2);
	end = (endurance * 2);
	att = (strength + dex);
	criticalRate = (luck / 4);
	critDamage = (dex / 2);
	evvasion = (agility + (luck / 2));
	accracy = (perception+ dex / 2);
	speed = agility;
}