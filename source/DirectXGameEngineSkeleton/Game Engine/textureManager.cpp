#include "textureManager.h"

//=============================================================================
// default constructor
//=============================================================================
TextureManager::TextureManager()
{
	texture = NULL;
	width = 0;
	height = 0;
	file = NULL;
	graphics = NULL;
	initialized = false;            // set true when successfully initialized
}

//=============================================================================
// destructor
//=============================================================================
TextureManager::~TextureManager()
{
	SAFE_RELEASE(texture);
}


//============================================================
// Loads the texture file from disk
// Post: returns true if successful, false if failed
//============================================================
bool TextureManager::initialize(Graphics *g, const char *f)
{
	try {
		graphics = g;
		file = f;
		hr = graphics->loadTexture(file, TRANSCOLOR, width, height, texture);

		if (FAILED(hr))
		{
			SAFE_DELETE(texture);
			return false;
		}
	}
	catch (...) {
		return false;
	}

	initialized = true;
	return true;
}

//============================================================
// Called when graphics device is lost
//============================================================
void TextureManager::onLostDevice()
{
	if (!initialized)
		return;
	SAFE_RELEASE(texture);
}

//============================================================
// Called when graphics device is reset
//============================================================
void TextureManager::onResetDevice()
{
	if (!initialized)
		return;
	graphics->loadTexture(file, TRANSCOLOR, width, height, texture);
}