#include "GameObject.h"
#include "GraphicComponent.h"


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
	SAFE_DELETE(graphicCom);
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

	list<BaseComponent *>::iterator listIte = componentList.begin();
	
	while (listIte != componentList.end())
	{
		BaseComponent *comp = *listIte;
		comp->update(this, input);
		listIte++;
	}

	if (oldVx != vx)
		requestChangeSprite();

	/* Update object properties */
	x += vx;

	graphicCom->update(this, input);
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

void GameObject::addComponent(BaseComponent *com, bool isGraphicRelate)
{
	if (isGraphicRelate)
	{
		GraphicComponent * temp = graphicCom;
		graphicCom = dynamic_cast<GraphicComponent *>(com);
		if (graphicCom == 0)
		{
			SAFE_DELETE(graphicCom);
			graphicCom = temp;
		}
	}
	else
	{
		componentList.push_back(com);
	}
}
