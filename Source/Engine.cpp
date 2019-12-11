#include "Engine.h"
#include <string>
#include <vector>
#include "Definitions.h"
#include "GameObject.h"

#include "RidgidBodyComponent.h"
#include "SpriteComponent.h"
#include "Stats.h"
#include "Clickable.h"

// rework this

Engine::Engine(string path)
{
	

	library->imgPath = imgPath;
	factory->xmlPath = xmlPath;
	loadLevel(path);
	
	SDL_StopTextInput();
}


Engine::~Engine() {

}


void Engine::loadLevel(string path)
{
	current_map = path;
	string objectType;
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS) {
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
		const char*objType;

		type = obj->QueryFloatAttribute("type", &type);





		object = factory->applyXML(obj);
		object->id = type;

		inventory.push_back(object);


	}

	createBattleSpace();
}
void Engine::createBattleSpace()
{

	for (int i = 32; i < gDevice->getHeight()-32; i = i + 64)
	{
		for (int j = 32; j < gDevice->getWidth() - 32; j = j + 64)
		{
			factory.get()->createObject("00", j, i);
			
		}
	}
	factory.get()->createObject("01", 32, 32);
	factory.get()->createObject("03", 160, 160);
	factory.get()->createObject("03", 352, 32);
}
void Engine::updateObjects()
{
	for (int i = 0; i < factory.get()->getQue().size(); i++)
	{
		objects.push_back(factory.get()->getQue()[i]);
	}


	factory.get()->clearQue();
	battle->clearLists();
}
void Engine::update()
{
	int w = gDevice->getWidth();
	int h = gDevice->getHeight();
	vector<GameObject*>newObjects;
	updateObjects();
	for (int i = 0; i < objects.size(); i++)

	{


		if (!battle->getPlayers().empty())
		{
			objects[i] = battle->getPlayerById(objects[i]->primaryId);
		}

	}
	for (int i = 0; i < objects.size(); i++)

	{


		if (objects[i]->id2 == "00")
		{
			battle->addPlayer(objects[i]);
			battle->addAlly(objects[i]);

		}
		if (objects[i]->id == "02")
		{

			if (objects[i]->getComponent<Clickable>()->clickCheck() == true)
			{
				if (!battle->isPlayerInSpace(objects[i]))
				{
					battle->setSlectedSpace(objects[i]);
				}
			}
	
			
			
		}
		if (objects[i]->id2 == "01")
		{
			battle->addPlayer(objects[i]);
			battle->addEnemy(objects[i]);

		}
		if (objects[i]->id == "04")
		{
			if (battle->getPlayer() == nullptr)
			{
				objects.erase(objects.begin() + i);
		}
				
			
		}
	}

	battle->update();


	for (int i = 0; i < objects.size(); i++)
	{

		if (!objects[i]->isDead) {
			GameObject* newObject = objects[i]->update();
			if (newObject != nullptr) {
				newObjects.push_back(newObject);
				newObject->initialize();
			}


		}

	}
	
	for (int i = newObjects.size() - 1; i > 0; i--)

	{
		if (newObjects[i]->id == "02" && battle->getPlayer()==nullptr)
		{
			newObjects.erase(newObjects.begin() + i);
		}
	}
	objects.clear();
	for (int i = 0; i < newObjects.size(); i++)
	{
		
		objects.push_back(newObjects[i]);
	}
}

void Engine::draw()
{
	gDevice->begin();
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->draw();
	}
	gDevice->present();
}
	bool Engine::run()
	{
		//Construct Frame Timer
		std::unique_ptr<Timer> frameRate = make_unique<Timer>();
		if (!frameRate->Initialize(gDevice->FPS))
		{
			printf("Frame Timer could not intialize! SDL_Error: %s\n", SDL_GetError());
			exit(1);
		}


		SDL_Event* Event=new SDL_Event;

		while (SDL_PollEvent(Event))
		{
			input->update(Event);

		}

		if (!paused) {
			//Start Frame Timer
			frameRate->start();

			// update objects
			update();

			// draw objects
			draw();

			//pauses until proper refresh time has passed.
			frameRate->fpsRegulate();
		}
		return true;
	}

	bool Engine::detectCollision(GameObject * object1, GameObject * object2)
	{
		return false;
	}

	void Engine::addToLibary(GameObject* object)
	{
		inventory.push_back(object);
	}
	void Engine::createMovementSpace(int moveNum)
	{
		int offset = 2 * moveNum + 1;
		GameObject* player = battle->getPlayer();
		int pX=player->getComponent<RidgidBody>()->position->x;
		int pY = player->getComponent<RidgidBody>()->position->y;
		int sX = pX + (64* (offset/2));
		int sY = pY;

		while (offset > 0)
		{
			for (int i = offset; i != 0; i--)
			{
				factory.get()->createObject("02", sX, sY);
				sX = sX - 64;
				
			}
			offset -= 2;
			sX = pX + (64 * (offset / 2));
			sY -= 64;
			
		}
		offset = (2 * moveNum + 1)-2;
		sX = pX + (pX * (offset / 2));
		sY = pY+64;
		while (offset >= 1)
		{
			for (int i = offset; i != 0; i--)
			{
				factory.get()->createObject("02", sX, sY);
				sX = sX - 64;

			}
			sY += 64;

			offset -= 2;
			sX = pX + (64 * (offset / 2));
		}
	}

