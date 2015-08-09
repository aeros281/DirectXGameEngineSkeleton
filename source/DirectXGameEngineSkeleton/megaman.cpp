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

	if (!rmTexture.initialize(graphics, ROCKMAN_RUN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing rockman texture"));
	if (!rockman.initialize(graphics, 24, 24, 3, &rmTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing rockman image"));

	darksaber.setFrames(0, 59);
	darksaber.setCurrentFrame(0);
	darksaber.setFrameDelay((float) 1/30);

	rockman.setFrames(0, 2);
	rockman.setCurrentFrame(0);
	rockman.setFrameDelay((float)1 / 5);

	rockman.setX(200);
	rockman.setY(100);

	// Game Object position is center around the AABB, so we must move
	// its center somehow to show the full object sprite
	darksaber.setX(546/2);
	darksaber.setY(279/2);
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
		rockman.setX(rockman.getX() + step);
	}
	if (input->wasKeyPressed(VK_UP))
	{
		rockman.setY(rockman.getY() + step);
	}
	if (input->wasKeyPressed(VK_DOWN))
	{
		rockman.setY(rockman.getY() - step);
	}
	if (input->wasKeyPressed(VK_LEFT))
	{
		rockman.setX(rockman.getX() - step);
	}

	// Scaling world
	if (input->wasKeyPressed(VK_RETURN))
		graphics->setGameScale(graphics->getGameScale() + 0.5f);

	if (input->wasKeyPressed(VK_SPACE) &&  graphics->getGameScale() > 0)
		graphics->setGameScale(graphics->getGameScale() - 0.2f);

	darksaber.update(frameTime);
	rockman.update(frameTime);
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
	rockman.draw();

	graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void MegaMan::releaseAll()
{
	dsTexture.onLostDevice();
	rmTexture.onLostDevice();
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
	rmTexture.onResetDevice();
	Game::resetAll();
	return;
}