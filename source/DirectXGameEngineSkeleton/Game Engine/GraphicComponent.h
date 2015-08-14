#ifndef _GRAPHICCOMPONENT_H
#define _GRAPHICCOMPONENT_H
#define WIN32_LEAN_AND_MEAN

#include "GameObject.h"
#include "image.h"


#pragma message("Begin to define GraphicComponent")
class GraphicComponent : public BaseComponent
{
private:
	Image *image;

public:
	GraphicComponent();

	~GraphicComponent();

	void initialize(Graphics *g, UINT width, UINT height, UINT ncols, TextureManager *TextureM, FLOAT frameDelay);

	void update(GameObject *object, Input *input);
	bool handleMessage(UINT messageCode);

	void draw(GameObject *object, float interpolation);

	virtual bool requestChangeSprite(GameObject *object, UINT message);
};
#pragma message("End define GraphicComponent")

#endif // !_GRAPHICCOMPONENT_H
