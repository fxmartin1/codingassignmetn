#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include<string>
#include<map>
#include"ObjectDefinitions.h"

#include "tinyxml2.h"

using namespace tinyxml2;
using namespace std;

class Engine;
class GameObject;
class InputHandler;
class TextureLibrary;
class Battle;
struct SDL_Renderer;

class ObjectFactory {
public:
	ObjectFactory(  InputHandler* input, TextureLibrary* library,Battle*battle );
	~ObjectFactory();

	GameObject* applyXML(XMLElement* obj);
	
	void createObject(string pType, float x, float y);
	vector<GameObject*> getQue()
	{
		return objectsQue;
	}
	void clearQue()
	{
		objectsQue.clear();
	}

	
	//void objectFromTemplate(ObjectTemplate* temp, shared_ptr<GameObject>);
	//void objectFromXML( XMLElement* ObjectXML, ObjectTemplate* baseObject, shared_ptr<GameObject>);

	string xmlPath = "";

private:
	InputHandler* input;
	TextureLibrary* library;
	Battle* battle;
	
	vector<GameObject*>objectsQue;
	SDL_Renderer* renderer;
	Engine* engine;


	//void getListObjects( XMLElement* comp, ObjectTemplate* baseObject, shared_ptr<vector<shared_ptr<GameObject>>> list);

	//ObjectTemplate templateFromXML( XMLElement * ObjectXML, ObjectTemplate* baseObject );
};


#endif
