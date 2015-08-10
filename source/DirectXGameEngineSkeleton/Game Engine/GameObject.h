#ifndef _GAMEOBJECT_H
#define  _GAMEOBJECT_H
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "image.h"
#include "input.h"

const INT MAX_VELOCITY = 48;

const enum SPRITE_DIRECTION {
	RIGHT,
	LEFT
};

class GameObject
{
private:
	FLOAT x;
	FLOAT y;
	FLOAT vx;
	FLOAT vy;
	FLOAT oldVx;
	UINT width;		// game object width
	UINT height;	// game object height
	FLOAT concurrentFrameTime;

	Image *sprite;
	UINT ncols;		// number of columns used for spritesheet
public:
	// GameObject constructor with no parameter
	// Should set x = y = vx = vy = 0
	GameObject();

	GameObject(UINT _x, UINT _y, FLOAT _vx, FLOAT _vy);

	// GameObject destructor
	~GameObject();

	bool spriteInitialize(Graphics *g, TextureManager *TextureM);

	// Update GameObject
	// frameTime = used for calculate object physics and sprite animation
	// g = pointer to Graphics object
	// input = pointer to Input object
	void update(FLOAT frameTime, Input *input);

	// Render GameObject
	void render();

	// Change Sprite
	void requestChangeSprite();
};
#endif