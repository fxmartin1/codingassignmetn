#ifndef ENGINE_H
#define ENGINE_H
#include "Timer.h"
#include "GraphicsDevice.h"
#include "ObjectFactory.h"
#include "TextureLibrary.h"
#include "InputHandler.h"
#include "Library.h"
#include "Battle.h"

#include <vector>
using namespace std;



class Engine
{

public:
	Engine(std::string path);
	~Engine();

	void loadLevel(std::string levelPath);
	void createBattleSpace();
	void createMovementSpace(int moveNum);
	void updateObjects();
	void update();
	void draw();
	bool run();


	int getScore() { return score; };


	bool detectCollision(GameObject* object1, GameObject* object2);// simple collistion detection

	shared_ptr<GameObject> getShip();
	void addToLibary(GameObject*object);
	void createObject(string type, float x, float y);


	

private:
	// get stuff
	vector<GameObject*> inventory;
	

	vector<GameObject*> objects;

	GraphicsDevice* gDevice=new GraphicsDevice();

	// create input handler
	unique_ptr<InputHandler>input=make_unique <InputHandler>();

	// create library
	TextureLibrary* library = new TextureLibrary(gDevice);

	// create factory

	
	//Battle function
	unique_ptr <Battle> battle = make_unique <Battle>();
	unique_ptr<ObjectFactory> factory = make_unique<ObjectFactory>(input.get(), library,battle.get());

	string imgPath = "./Assets/Images/";
	string xmlPath = "./Assets/Config/";

	// MiniMap


	///////////////

	bool paused{ 0 };
	bool isBattle = true;
	bool spaceCreated = false;
	bool gameOver;
	int score;


	
	string current_map="";

};


#endif