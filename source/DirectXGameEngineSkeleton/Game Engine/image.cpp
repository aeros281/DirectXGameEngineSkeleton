#include "image.h"

//=============================================================================
// default constructor
//=============================================================================
Image::Image()
{
	initialized = false;            // set true when successfully initialized
	spriteData.width = 2;
	spriteData.height = 2;
	spriteData.x = 0.0;
	spriteData.y = 0.0;
	spriteData.scale = 1.0;
	spriteData.angle = 0.0;
	spriteData.rect.left = 0;       // used to select one frame from multi-frame image
	spriteData.rect.top = 0;
	spriteData.rect.right = spriteData.width;
	spriteData.rect.bottom = spriteData.height;
	spriteData.texture = NULL;      // the sprite texture (picture)
	spriteData.flipHorizontal = false;
	spriteData.flipVertical = false;
	cols = 1;
	textureManager = NULL;
	startFrame = 0;
	endFrame = 0;
	currentFrame = 0;
	frameDelay = 1.0;               // default to 1 second per frame of animation
	animTimer = 0.0;
	visible = true;                 // the image is visible
	loop = true;                    // loop frames
	animComplete = false;
	graphics = NULL;                // link to graphics system
	colorFilter = graphicsNS::WHITE; // WHITE for no change
}

//=============================================================================
// destructor
//=============================================================================
Image::~Image()
{}


//===============================================================
// Initialize the image
// Post: returns true if successful, false if failed
// Prev: *g = pointer to Graphics object
//		width = Width of Image in pixels (0 = use full texture width)
//		height = Height of Image in pixels (0 = use full texture height)
//		ncols = Nunber of columns in texture (1 to n) (0 same as 1)
//		*textureM = pointer to TextureManager
//===============================================================
bool Image::initialize(Graphics *g, int width, int height, int ncols, TextureManager *textureM)
{
	try {
		graphics = g;
		textureManager = textureM;
		spriteData.texture = textureManager->getTexture();
		if (width == 0)
			width = textureManager->getWidth();
		spriteData.width = width;
		if (height == 0)
			height = textureManager->getHeight();
		spriteData.height = height;
		cols = ncols;
		if (cols == 0)
			cols = 1;

		// Configure spriteData.rect to draw current Frame
		spriteData.rect.left = (currentFrame % cols) * spriteData.width;
		// Right edge + 1
		spriteData.rect.right = spriteData.rect.left + spriteData.width;
		
		spriteData.rect.top = (currentFrame / cols) * spriteData.height;
		// Bottom edge + 1
		spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
	}
	catch (...) {
		return false;
	}

	initialized = true;
	return true;
}

//===============================================================
// Draw the image using color as filter
// The color parameter is optional, white is assigned as default 
// Pre: spriteBegin() is called
// Post: spriteEnd() is called
//===============================================================
void Image::draw(COLOR_ARGB color)
{
	if (!visible || graphics == NULL) return;

	// Get fresh texture incase onReset was called
	spriteData.texture = textureManager->getTexture();

	// If draw with filter color
	if (color == graphicsNS::FILTER)
		graphics->drawSprite(spriteData, colorFilter);
	else
		graphics->drawSprite(spriteData, color);
}

//===============================================================
// Draw this image using the specified SpriteData
// The current SpriteData.rect is used to select the texture
// Pre: spriteBegin() is called
// Post: spriteEnd() is called
//===============================================================
void Image::draw(SpriteData sd, COLOR_ARGB color /* = graphicsNS::WHITE */)
{
	if (!visible || graphics == NULL) return;

	// Use this image rect to select the texture
	sd.rect = spriteData.rect;

	// Get fresh texture incase onReset was called
	sd.texture = textureManager->getTexture();

	// If draw with filter color
	if (color == graphicsNS::FILTER)
		graphics->drawSprite(sd, colorFilter);
	else
		graphics->drawSprite(sd, color);
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Image::update(float frameTime)
{
	if (endFrame - startFrame > 0)          // if animated sprite
	{
		animTimer += frameTime;             // total elapsed time
		if (animTimer > frameDelay)
		{
			animTimer -= frameDelay;
			currentFrame++;
			if (currentFrame < startFrame || currentFrame > endFrame)
			{
				if (loop == true)            // if looping animation
					currentFrame = startFrame;
				else                        // not looping animation
				{
					currentFrame = endFrame;
					animComplete = true;    // animation complete
				}
			}
			setRect();                      // set spriteData.rect
		}
	}
}

//=============================================================================
// Set the current frame of the image
//=============================================================================
void Image::setCurrentFrame(int c)
{
	if (c >= 0)
	{
		currentFrame = c;
		animComplete = false;
		setRect();                          // set spriteData.rect
	}
}

//=============================================================================
//  Set spriteData.rect to draw currentFrame
//=============================================================================
inline void Image::setRect()
{
	// configure spriteData.rect to draw currentFrame
	spriteData.rect.left = (currentFrame % cols) * spriteData.width;
	// right edge + 1
	spriteData.rect.right = spriteData.rect.left + spriteData.width;
	spriteData.rect.top = (currentFrame / cols) * spriteData.height;
	// bottom edge + 1
	spriteData.rect.bottom = spriteData.rect.top + spriteData.height;
}

