#include "Ability.h"
#include "RidgidBodyComponent.h"
#include "Clickable.h"

Ability::Ability(GameObject* owner, tinyxml2::XMLElement* componentElement, Battle* battle,InputHandler* input,ObjectFactory* factory) :Component(owner)
{
	this->battle = battle;
	this->input = input;
	this->factory = factory;
}

Ability::~Ability()
{

}

void Ability::start()
{

}

GameObject* Ability::update()
{
	RidgidBody* eBody;
	if (getOwner()->getComponent<Clickable>()->clickCheck())
	{
		switch (currentAbility)
		{
		case 1:
			break;

		case 2:
			//ranged attack one space
			for (int i = 0; i < battle->getEnemys().size(); i++)
			{
				eBody = battle->getEnemys()[i]->getComponent<RidgidBody>();
				factory->createObject("04", eBody->position->x, eBody->position->y);
			}
			break;
		}
	}
	return nullptr;
}

void Ability::finish()
{

}