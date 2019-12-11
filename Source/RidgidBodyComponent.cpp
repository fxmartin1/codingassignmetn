#include "GameObject.h"
#include "ObjectDefinitions.h"
#include "RidgidBodyComponent.h"
#include <string>

RidgidBody::RidgidBody(GameObject* owner, tinyxml2::XMLElement* componentElement) : Component(owner)
{
	float x;
	float y;
	float cx;
	float cy;
	float vx;
	float vy;
	componentElement->QueryFloatAttribute("x", &x);
	componentElement->QueryFloatAttribute("y", &y);
	
	componentElement->QueryFloatAttribute("vx", &vx);
	componentElement->QueryFloatAttribute("vy", &vy);
	
	componentElement->QueryFloatAttribute("cx", &cx);
	componentElement->QueryFloatAttribute("cy", &cy);
	angle = 0;
	position->x = x;
	position->y = y;
	center->x = cx;
	center->y = cy;
	velocity->x = vx;
	velocity-> y = vy;
	
	
}

RidgidBody::~RidgidBody() {}


void RidgidBody::initialize(SDL_Renderer* renderer, ObjectTemplate* temp)
{
	// get rid of this 

}

void RidgidBody::start() {}

GameObject* RidgidBody::update() {

	return nullptr;
}

void RidgidBody::finish() {}