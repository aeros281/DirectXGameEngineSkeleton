#include "GameObject.h"


//=================================================
// Constructor
//=================================================
GameObject::GameObject(UINT _x, UINT _y, FLOAT _vx, FLOAT _vy)
{
	x = (float) _x;
	y = (float) _y;
	vx = _vx;
	vy = _vy;
	oldVx = vx;

	ncols = 6;
	width = 31;
	height = 30;

	sprite = new Image();
	inputCom = NULL;
}

GameObject::GameObject() : GameObject(16, 15, 0, 0)
{
}

//=================================================
// Destructor
//=================================================
GameObject::~GameObject()
{
	SAFE_DELETE(sprite);
}

//=================================================
// spriteInitilialize
//=================================================
bool GameObject::spriteInitialize(Graphics *g, TextureManager *TextureM)
{
	try {
		sprite->initialize(g, width, height, ncols, TextureM);
		requestChangeSprite();
		sprite->setFrameDelay((float) 1 / 6);
	}
	catch (...){
		return false;
	}
	return true;

}

//=================================================
// update
//=================================================
void GameObject::update(FLOAT frameTime, Input *input)
{
	oldVx = vx;

	if (inputCom != NULL)
		inputCom->handleInput(this, input);

	if (oldVx != vx)
		requestChangeSprite();

	/* Update object properties */
	x += vx * frameTime;

	sprite->update(frameTime);
}

//=================================================
// render
//=================================================
void GameObject::render()
{
	sprite->setX(x);
	sprite->setY(y);
	sprite->draw();
}

void GameObject::requestChangeSprite()
{
	UINT startFrame = 0, endFrame = 0;
	if (vx == 0) // Not running
	{
		if (oldVx >= 0)
		{
			startFrame = 0;
			endFrame = 0;
		}
		else
		{
			startFrame = 6;
			endFrame = 6;
		}
	}
	else
	{
		startFrame = 2;
		endFrame = 4;
	}
	
	if (vx < 0)
	{
		startFrame += ncols;
		endFrame += ncols;
	}

	sprite->setFrames(startFrame, endFrame);
	sprite->setCurrentFrame(startFrame);
}

void GameObject::setInputComponent(InputComponent *iCom)
{
	SAFE_DELETE(inputCom);
	inputCom = iCom;
}
