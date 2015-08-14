#ifndef _AUTOINPUTCOMPONENT_H
#define _AUTOINPUTCOMPONENT_H
#define WIN32_LEAN_AND_MEAN

#include "GameObject.h"

#pragma message("Define AutoInput Component")
class AutoInputComponent : public BaseComponent
{
private:
	FLOAT max_velocity;			// the maximum velocity (maximum number of pixels an object able to move within a frame)
public:
	AutoInputComponent(FLOAT = 2.0f);
	~AutoInputComponent();

	// Implement of virtual method
	void update(GameObject *object, Input *input);
	bool handleMessage(UINT messageCode);


};
#endif