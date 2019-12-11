#include "Battle.h"
#include "ObjectFactory.h"
#include "GameObject.h"
#include "TextureLibrary.h"
#include "SpriteComponent.h"
#include "RidgidBodyComponent.h"
#include "Stats.h"
#include "Clickable.h"
#include "InputHandler.h"
#include "input.h"
#include "DetectedEnemy.h"
#include "SetTarget.h"
#include "Equipment.h"
#include "Ability.h"
#include "MoveSpace.h"
#include "EnemyAi.h"



ObjectFactory::ObjectFactory(InputHandler* input, TextureLibrary* library, Battle* battle) {
	
	this->input = input;
	this->library = library;
	this->battle = battle;
	
}

ObjectFactory::~ObjectFactory() {
}

GameObject* ObjectFactory::applyXML(XMLElement* ObjectXML)
{
	// allocate new GameObject
	
	
	GameObject* object=new GameObject;

	for (
		tinyxml2::XMLElement* componentElement = ObjectXML->FirstChildElement();
		componentElement;
		componentElement = componentElement->NextSiblingElement()
		)
	{
		string componentName = componentElement->Attribute("name");
		if (componentName == "sprite")
		{
			object->addComponent(new Sprite(object, componentElement,library));
		}
		else if (componentName == "body")
		{
			object->addComponent(new RidgidBody(object, componentElement));
			
		}
		else if (componentName == "clickable")
		{
			object->addComponent(new Clickable(object, componentElement,input));

		}
		else if (componentName == "stats")
		{
			object->addComponent(new Stats(object, componentElement));

		}
		else if (componentName == "detectedenemy")
		{
			object->addComponent(new DetectedEnemy(object, componentElement,battle,this));

		}
		else if (componentName == "settarget")
		{
			object->addComponent(new SetTarget(object, componentElement, battle));

		}
		else if (componentName == "equipment")
		{
			object->addComponent(new Equipment(object, componentElement));

		}
		else if (componentName == "ability")
		{
			object->addComponent(new Ability(object, componentElement,battle,input,this));

		}
		else if (componentName == "input")
		{
			object->addComponent(new UserInput(object, componentElement, battle, input));

		}
		else if (componentName == "movespace")
		{
			object->addComponent(new MoveSpace(object, componentElement, battle, this));

		}
		else if (componentName == "enemyai")
		{
			object->addComponent(new EnemyAi(object, componentElement, battle));

		}
	}
	return object;
}

void ObjectFactory::createObject(string pType, float x, float y)
{

	string current_map = "Assets/Config/level1.xml";
	string objectType;
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(current_map.c_str()) != tinyxml2::XML_SUCCESS) {
		printf("Bad File Path");
		exit(1);
	}

	//Get root
	tinyxml2::XMLElement* root = doc.FirstChildElement("Level");

	char tempType;
	float type;
	GameObject* object;
	for (tinyxml2::XMLElement* obj = root->FirstChildElement("Object"); obj != NULL; obj = obj->NextSiblingElement())
	{
		const char* objType;

		objType = obj->Attribute("type");


		if (objType == pType)
		{
			object = applyXML(obj);
			object->id = objType;
			object->id2 = obj->Attribute("type2");
			RidgidBody* body = object->getComponent<RidgidBody>();
			body->position->x = x;
			body->position->y = y;
			objectsQue.push_back(object);
		}








	}


}