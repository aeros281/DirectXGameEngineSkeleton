#ifndef _USERINPUTCOMPONENT_H
#define  _USERINPUTCOMPONENT_H
#define  WIN32_LEAN_AND_MEAN

#include "GameObject.h"

class UserInputComponent : public BaseComponent
{
private:
	FLOAT max_velocity;
public:
	UserInputComponent(FLOAT max_velo);
	~UserInputComponent() {};

	void update(GameObject *object, Input *input);
	bool handleMessage(UINT messageCode);


	const FLOAT MAX_VELOCITY = 3.0f; // Pixels per seconds
	const UCHAR A_KEY = 0x41;
	const UCHAR D_KEY = 0x44;
	const UCHAR S_KEY = 0x53;
	const UCHAR W_KEY = 0x57;
	const UCHAR J_KEY = 0x4A;
	const UCHAR K_KEY = 0x4B;

};
#endif