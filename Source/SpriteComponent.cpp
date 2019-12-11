#include "TextureLibrary.h"
#include "GameObject.h"
#include "Component.h"
#include "RidgidBodyComponent.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include <string>

Sprite::Sprite(GameObject* owner, tinyxml2::XMLElement* componentElement, TextureLibrary* library) : Component(owner)
{
// update this!!
	this->library = library;
	float sx;
	float sy;
	float cx;
	float cy;
	componentElement->QueryFloatAttribute("sx",&sx);
	componentElement->QueryFloatAttribute("sy", &sy);
	componentElement->QueryFloatAttribute("cx", &cx);
	componentElement->QueryFloatAttribute("cy", &cy);
	sposition->x = sx;
	sposition->y = sy;
	scenter->x = cx;
	scenter->y = cy;

	int sw;
	int sh;
	componentElement->QueryIntAttribute("sw", &sw);
	componentElement->QueryIntAttribute("sh",&sh);
	size->x = sw;
	size->y = sh;
	rect->x=sx;
	rect->y = sy;
	rect->w = sw;
	rect->h = sh;
	const char* pathName;
	componentElement->QueryStringAttribute("path", &pathName);
	path = pathName;
	angle = 0;
	setTexture(&path);
	componentElement->QueryStringAttribute("path", &pathName);
	ready = true;
	
}

Sprite::~Sprite() {}

void Sprite::initialize(TextureLibrary* library, ObjectTemplate* temp)
{
	// get rid of this!!!

}

void Sprite::start() {}

GameObject* Sprite::update() {
	

 
	return nullptr;
}

void Sprite::finish() {}

void Sprite::draw()
{
	RidgidBody* body = getOwner()->getComponent<RidgidBody>();
	if(ready)texture->draw(body->position, body->angle, body->center, rect);
}

void Sprite::setTexture(string * path)
{       
	    this->path = *path;
		texture = library->getArtAsset(library->imgPath + *path);
		texture->setRGBA(color);
}

string Sprite::getPath()
{
	return path;
}
