#include "UserInputComponent.h"


void UserInputComponent::handleInput(GameObject *object, Input *input)
{
	/* Handle input */
	if (input->isKeyDown(D_KEY))
	{
		object->setVX((float) MAX_VELOCITY);
	}
	else if (input->isKeyDown(A_KEY))
	{
		object->setVX((float) -MAX_VELOCITY);
	}
	else
	{
		object->setVX(0);
	}
}

