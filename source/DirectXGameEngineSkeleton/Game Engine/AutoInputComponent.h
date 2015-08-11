#ifndef _AUTOINPUTCOMPONENT_H
#define _AUTOINPUTCOMPONENT_H
#define WIN32_LEAN_AND_MEAN

#include "InputComponent.h"

class AutoInputComponent : public InputComponent
{
public:
	AutoInputComponent();
	~AutoInputComponent();

	const INT MAX_VELOCITY = 60;
	void handleInput(GameObject *object, Input *input);
};
#endif