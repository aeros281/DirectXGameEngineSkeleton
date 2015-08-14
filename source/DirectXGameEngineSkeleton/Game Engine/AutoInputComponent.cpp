#include "AutoInputComponent.h"


AutoInputComponent::~AutoInputComponent()
{
}

AutoInputComponent::AutoInputComponent(FLOAT max_velo)
{
	max_velocity = max_velo;
}

void AutoInputComponent::update(GameObject *object, Input *input)
{

	if (object->getVX() == 0)
		object->setVX(max_velocity);

	if (object->getX() >= 300 && object->getVX() > 0)
	{
		object->setVX(-max_velocity);
	}

	if (object->getX() <= 0 && object->getVX() < 0)
	{
		object->setVX(max_velocity);
	}
}

bool AutoInputComponent::handleMessage(UINT messageCode)
{
	return true;
}
