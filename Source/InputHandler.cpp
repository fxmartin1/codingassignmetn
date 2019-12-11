#include "SDL.h"
#include "InputHandler.h"

InputHandler::InputHandler()
{
	keyStates[Inputs::NA] = false;
	keyStates[Inputs::FORWARD] = false;
	keyStates[Inputs::LEFT] = false;
	keyStates[Inputs::RIGHT] = false;
	keyStates[Inputs::PRIMARY] = false;
	keyStates[Inputs::MISSILE] = false;
	keyStates[Inputs::PAUSE] = false;
	keyStates[Inputs::QUIT] = false;
	keyStates[Inputs::RELOAD] = false;
	keyStates[Inputs::MAP] = false;
	keyStates[Inputs::CLICK] = false;
	keyStates[Inputs::ENDTURN] = false;
}

void InputHandler::update( SDL_Event* event)
{

	InputHandler::Inputs input;
	SDL_GetMouseState(&mouseX, &mouseY);
	switch (event->type)
	{

	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_a)
		{
			input = Inputs::LEFT;
			keyStates[input] = true;


		}
		if (event->key.keysym.sym == SDLK_w)
		{
			input = Inputs::FORWARD;
			keyStates[input] = true;

		}

		if (event->key.keysym.sym == SDLK_d)
		{
			input = Inputs::RIGHT;
			keyStates[input] = true;

		}
		if (event->key.keysym.sym == SDLK_SPACE)
		{
			input = Inputs::PRIMARY;
			keyStates[input] = true;

		}
		if (event->key.keysym.sym == SDLK_LSHIFT)
		{
			input = Inputs::MISSILE;
			keyStates[input] = true;

		}
		if (event->key.keysym.sym == SDLK_p)
		{
			input = Inputs::PAUSE;
			keyStates[input] = true;

		}
		if (event->key.keysym.sym == SDLK_F5)
		{
			input = Inputs::RELOAD;
			keyStates[input] = true;

		}
		if (event->key.keysym.sym == SDLK_m)
		{
			input = Inputs::MAP;
			keyStates[input] = true;

		}
		if (event->key.keysym.sym == SDLK_n)
		{
			input = Inputs::ENDTURN;
			keyStates[input] = true;

		}
		break;
	case SDL_KEYUP:
		if (event->key.keysym.sym == SDLK_a)
		{
			input = Inputs::LEFT;
			keyStates[input] = false;


		}
		if (event->key.keysym.sym == SDLK_w)
		{
			input = Inputs::FORWARD;
			keyStates[input] = false;

		}

		if (event->key.keysym.sym == SDLK_d)
		{
			input = Inputs::RIGHT;
			keyStates[input] = false;

		}
		if (event->key.keysym.sym == SDLK_SPACE)
		{
			input = Inputs::PRIMARY;
			keyStates[input] = false;

		}
		if (event->key.keysym.sym == SDLK_LSHIFT)
		{
			input = Inputs::MISSILE;
			keyStates[input] = false;

		}
		if (event->key.keysym.sym == SDLK_p)
		{
			input = Inputs::PAUSE;
			keyStates[input] = false;

		}
		if (event->key.keysym.sym == SDLK_F5)
		{
			input = Inputs::RELOAD;
			keyStates[input] = false;

		}
		if (event->key.keysym.sym == SDLK_m)
		{
			input = Inputs::MAP;
			keyStates[input] = false;

		}
		if(event->type == SDL_MOUSEBUTTONDOWN )
		{
			input = Inputs::CLICK;
			keyStates[input] = false;
		}
		if (event->key.keysym.sym == SDLK_n)
		{
			input = Inputs::ENDTURN;
			keyStates[input] = false;

		}
		break;
	case SDL_QUIT:
		keyStates.find(Inputs::QUIT)->second = true;
		break;
	default:
		break;
	}

	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		input = Inputs::CLICK;
		keyStates[input] = true;
	}
	else
	{
		input = Inputs::CLICK;
		keyStates[input] = false;
	}
}
