#ifndef _USERINPUTCOMPONENT_H
#define  _USERINPUTCOMPONENT_H
#define  WIN32_LEAN_AND_MEAN

class UserInputComponent;

#include "InputComponent.h"

class UserInputComponent : public InputComponent
{
public:
	UserInputComponent() {};
	~UserInputComponent() {};

	void handleInput(GameObject *object, Input *input);

	const INT MAX_VELOCITY = 60; // Pixels per seconds
	const UCHAR A_KEY = 0x41;
	const UCHAR D_KEY = 0x44;
	const UCHAR S_KEY = 0x53;
	const UCHAR W_KEY = 0x57;
	const UCHAR J_KEY = 0x4A;
	const UCHAR K_KEY = 0x4B;

};
#endif