#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H
#include "Texture.h"




using namespace std;

class GraphicsDevice
{

public:
	GraphicsDevice();
	~GraphicsDevice();
	int getWidth();
	int getHeight();

	SDL_Renderer* getRenderer();

	void begin();

	void present();

	int FPS = 60;

private:

	//
	// PRIVATE METHODS
	//
	void initGraphicsDevice(int width = 640, int height = 320);

	void cleanUp();

	//
	//PRIVATE MEMBERS
	//
	bool quit;

	int width = 640;
	int height = 320;

	//Window(s) to display graphics
	SDL_Window* window;

	//Hardware accelerated renderer
	SDL_Renderer* renderer;
};
#endif