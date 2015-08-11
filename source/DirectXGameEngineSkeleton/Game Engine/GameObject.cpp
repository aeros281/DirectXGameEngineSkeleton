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
	graphicCom = new GraphicComponent();
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
		graphicCom->initialize(g, 31, 30, 6, TextureM, (float)1);
		graphicCom->requestChangeSprite(this, 1);
	}
	catch (...){
		return false;
	}
	return true;

}

//=================================================
// update
//=================================================
void GameObject::update(Input *input)
{
	oldVx = vx;

	if (inputCom != NULL)
		inputCom->handleInput(this, input);

	if (oldVx != vx)
		requestChangeSprite();

	/* Update object properties */
	x += vx;

	graphicCom->update(0.3f);
}

//=================================================
// render
//=================================================
void GameObject::render(float intepolation)
{
	graphicCom->draw(this, intepolation);
}

void GameObject::requestChangeSprite()
{
	graphicCom->requestChangeSprite(this, 1);
}

void GameObject::setInputComponent(InputComponent *iCom)
{
	SAFE_DELETE(inputCom);
	inputCom = iCom;
}

void GameObject::setGraphicComponent(GraphicComponent *gCom)
{
	SAFE_DELETE(graphicCom);
	graphicCom = gCom;
}
