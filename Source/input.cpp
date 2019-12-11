#include"input.h"

UserInput::UserInput(GameObject* owner, tinyxml2::XMLElement* componentElement, Battle* battle, InputHandler* input):Component(owner)
{
	this->input = input;
	this->battle = battle;
}

UserInput::~UserInput()
{

}

void UserInput::start()
{

}

GameObject* UserInput::update()
{
	if (input->keyStates[InputHandler::Inputs::ENDTURN] == true)
	{
		input->keyStates[InputHandler::Inputs::ENDTURN] = false;
		battle->nextTurn();
	}
	return nullptr;
}

void UserInput::finish()
{

}