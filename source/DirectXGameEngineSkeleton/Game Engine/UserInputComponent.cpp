#include "UserInputComponent.h"


UserInputComponent::UserInputComponent(FLOAT max_velo)
{
	max_velocity = max_velo;
}

void UserInputComponent::update(GameObject *object, Input *input)
{
	/* Handle input */
	if (input->isKeyDown(D_KEY))
	{
		object->setVX((float)max_velocity);
	}
	else if (input->isKeyDown(A_KEY))
	{
		object->setVX((float)-max_velocity);
	}
	else
	{
		object->setVX(0);
	}
}

bool UserInputComponent::handleMessage(UINT messageCode)
{
	return true;
}

