#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_
#define WIN32_LEAN_AND_MEAN

#include "graphics.h"
#include "constants.h"

class TextureManager
{
	// Texture Manager properties
private:
	UINT width;					// width of texture in pixels
	UINT height;				// height of texture in pixels
	LP_TEXTURE texture;			// pointer of texture
	const char *file;			// name of file
	Graphics *graphics;			// save pointer to graphics
	bool initialized;			// true when successfully initialized
	HRESULT hr;					// standard return type
public:
	// Constructor
	TextureManager();

	// Destructor
	~TextureManager();

	// Return the pointer to the texture
	LP_TEXTURE getTexture() const 
	{
		return texture;
	}

	// Return the texture's width
	UINT getWidth() const
	{
		return width;
	}

	// Return the texture's height
	UINT getHeight() const
	{
		return height;
	}

	// Initialized the TextureManger
	// Pre: *g points to Graphics object
	//		*file points to name of texture file to load
	// Post: The texture is loaded
	virtual bool initialize(Graphics *g, const char *file);

	// Release resources
	virtual void onLostDevice();

	// Restore resources
	virtual void onResetDevice();
};
#endif