#ifndef _GRAPHICCOMPONENT_H
#define _GRAPHICCOMPONENT_H
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include "GameObject.h"

class GameObject;

class GraphicComponent
{
private:
	Image *image;

public:
	GraphicComponent();

	~GraphicComponent();

	void initialize(Graphics *g, UINT width, UINT height, UINT ncols, TextureManager *TextureM, FLOAT frameDelay);

	void update(FLOAT frameTime);

	void draw(GameObject *object, float interpolation);

	virtual bool requestChangeSprite(GameObject *object, UINT message);
};

#endif // !_GRAPHICCOMPONENT_H
