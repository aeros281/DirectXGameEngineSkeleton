#ifndef _INPUTCOMPONENT_H
#define  _INPUTCOMPONENT_H
#define  WIN32_LEAN_AND_MEAN


class GameObject;

#include "GameObject.h"

class InputComponent
{
public:

	InputComponent() {};
	~InputComponent() {};

	virtual void handleInput(GameObject *object, Input *input);

};

#endif