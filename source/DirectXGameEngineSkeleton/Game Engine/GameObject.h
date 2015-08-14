#ifndef _GAMEOBJECT_H
#define  _GAMEOBJECT_H
#define WIN32_LEAN_AND_MEAN

class BaseComponent;
class GameObject;
class GraphicComponent;


#include <windows.h>
#include "image.h"
#include "input.h"
#include <list>

class BaseComponent
{
public:
	BaseComponent() {};
	~BaseComponent() {};

	virtual void update(GameObject *gObject, Input *input) = 0;

	virtual bool handleMessage(UINT messageCode) = 0;
};



using namespace std;

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
	UINT ncols;		// number of columns used for spritesheet

	// List of base component;
	GraphicComponent *graphicCom;
	list<BaseComponent*> componentList;
public:
	// GameObject constructor with no parameter
	// Should set x = y = vx = vy = 0
	GameObject();

	GameObject(UINT _x, UINT _y, FLOAT _vx, FLOAT _vy);

	// GameObject destructor
	~GameObject();

	// Initialize sprite object
	bool spriteInitialize(Graphics *g, TextureManager *TextureM);

	// Update GameObject
	// frameTime = used for calculate object physics and sprite animation
	// g = pointer to Graphics object
	// input = pointer to Input object
	void update(Input *input);

	// Render GameObject
	void render(float intepolation);

	// Change Sprite
	void requestChangeSprite();

	// Add component
	void addComponent(BaseComponent *com, bool isGraphicRelate);

	//==========================
	// Fields
	//==========================
	FLOAT getX() const { return x; }
	void setX(FLOAT val) { x = val; }

	FLOAT getY() const { return y; }
	void setY(FLOAT val) { y = val; }

	FLOAT getVX() const { return vx; }
	void setVX(FLOAT val) { vx = val; }

	FLOAT getVY() const { return vy; }
	void setVY(FLOAT val) { vy = val; }

	FLOAT getOldVX() const { return oldVx; }
	void setOldVX(FLOAT val) { oldVx = val; }
};
#endif