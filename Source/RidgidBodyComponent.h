#ifndef RIDGIDBODY_H
#define RIDGIDBODY_H

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

	// position

	Vector2D* position=new Vector2D();
	float angle=0;

	// center of balance
	Vector2D* center=new Vector2D();

	// velocity
	Vector2D* velocity=new Vector2D();
	float* vAngle=0;

	// integrity factors
	std::shared_ptr<int> area = make_shared<int>(0);
	std::shared_ptr<int> layer = make_shared<int>(0);
	std::shared_ptr<bool> shell = make_shared<bool>(false);
protected:

	// used to get width and height of play area
	SDL_Renderer* renderer;

	eFloat pos_mod(eFloat a, eFloat b) {
		return fmod(fmod(a, b) + b, b);
	}
};


#endif