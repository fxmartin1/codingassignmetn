#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<memory>
#include<iostream>
#include<vector>
#include "SDL.h"
#include "ObjectDefinitions.h"

class Component;
class Sprite;
class InputHandler;
class GameLibrary;

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();
	bool initialize();

	void addComponent( Component* component);
	//come back to this

	template<class T>
	T* getComponent()
	{
		for (auto& component : components)
		{
			if (T* target = nullptr; target = dynamic_cast<T*>(component.get()))
			{
				return(target);
			}
		}
		return(nullptr);
	}

	GameObject* update();
	void draw();
	string createPrimaryID();
	// vitality
	bool live{ true };
	bool isDead = false;
	string id;
	string id2;
	string primaryId = id + id2 + createPrimaryID();

protected:

	vector<unique_ptr<Component>> components;
	bool initialized{ false };

};

#endif
