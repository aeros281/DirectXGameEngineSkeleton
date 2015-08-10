#include "AutoInputComponent.h"




AutoInputComponent::~AutoInputComponent()
{

}

AutoInputComponent::AutoInputComponent()
{

}

void AutoInputComponent::handleInput(GameObject *object, Input *input)
{

	if (object->getVX() == 0)
		object->setVX((float) MAX_VELOCITY);

	if (object->getX() >= 300 && object->getVX() > 0)
	{
		object->setVX(-MAX_VELOCITY);
	}

	if (object->getX() <= 0 && object->getVX() < 0)
	{
		object->setVX(MAX_VELOCITY);
	}
}
