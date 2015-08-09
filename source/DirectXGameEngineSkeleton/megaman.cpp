#include "megaman.h"

//=============================================================================
// Constructor
//=============================================================================
MegaMan::MegaMan()
{}

//=============================================================================
// Destructor
//=============================================================================
MegaMan::~MegaMan()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void MegaMan::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	// Initialize game resources

	if (!dsTexture.initialize(graphics, DARK_SABER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing darksaber texture"));
	if (!darksaber.initialize(graphics, 546, 279, 12, &dsTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing darksaber image"));

	darksaber.setFrames(0, 59);
	darksaber.setCurrentFrame(0);
	darksaber.setFrameDelay((float) 1/30);

	// Place cowboy in the central of the screen
	darksaber.setX(0);
	darksaber.setY(0);
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void MegaMan::update()
{
	UINT step = 10;
	if (input->wasKeyPressed(VK_RIGHT))
	{
		darksaber.setX(darksaber.getX() + step);
	}
	if (input->wasKeyPressed(VK_UP))
	{
		darksaber.setY(darksaber.getY() + step);
	}
	if (input->wasKeyPressed(VK_DOWN))
	{
		darksaber.setY(darksaber.getY() - step);
	}
	if (input->wasKeyPressed(VK_LEFT))
	{
		darksaber.setX(darksaber.getX() - step);
	}

	// Scaling world
	if (input->wasKeyPressed(VK_RETURN))
		darksaber.setScale(darksaber.getScale() + 0.5f);

	if (input->wasKeyPressed(VK_SPACE) &&  darksaber.getScale() > 0)
		darksaber.setScale(darksaber.getScale() - 0.2f);

	darksaber.update(frameTime);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void MegaMan::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void MegaMan::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void MegaMan::render()
{
	graphics->spriteBegin();


	darksaber.draw();

	graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void MegaMan::releaseAll()
{
	dsTexture.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void MegaMan::resetAll()
{
	dsTexture.onResetDevice();
	Game::resetAll();
	return;
}