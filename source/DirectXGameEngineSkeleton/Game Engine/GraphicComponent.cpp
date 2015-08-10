#include "GraphicComponent.h"




GraphicComponent::~GraphicComponent()
{
	SAFE_DELETE(image);
}

GraphicComponent::GraphicComponent()
{
	image = new Image();
}

void GraphicComponent::update(FLOAT frameTime)
{
	image->update(frameTime);
}

void GraphicComponent::draw(GameObject *object)
{
	if (image != NULL)
	{
		image->setX(object->getX());
		image->setY(object->getY());
		image->draw();
	}
}

void GraphicComponent::initialize(Graphics *g, UINT width, UINT height, UINT ncols, TextureManager *TextureM, FLOAT frameDelay)
{
	image->initialize(g, width, height, ncols, TextureM);
	image->setFrameDelay(frameDelay);
}

bool GraphicComponent::requestChangeSprite(GameObject *object, UINT message)
{
	UINT startFrame = 0, endFrame = 0;
	if (object->getVX() == 0) // Not running
	{
		if (object->getOldVX() >= 0)
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

	if (object->getVX() < 0)
	{
		startFrame += image->getNumberofColumns();
		endFrame += image->getNumberofColumns();
	}

	image->setFrames(startFrame, endFrame);
	image->setCurrentFrame(startFrame);

	return true;
}
