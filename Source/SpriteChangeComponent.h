#ifndef SPRITECHANGE_H
#define SPRITECHANGE_H

#include "Component.h"
#include "tinyxml2.h"
class GameObject;
class GameLibrary;
class Texture;
struct SDL_Renderer;

class RidgidBody : public Component
{
public:
	RidgidBody(GameObject* owner, tinyxml2::XMLElement* componentElement);
	~RidgidBody();
	void initialize(SDL_Renderer* renderer, ObjectTemplate* temp);

	void start();
	GameObject* update();
	void finish();

	
protected:

	// used to get width and height of play area
	


};


#endif