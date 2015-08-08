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
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing nebula texture"));	
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing nebula image"));

	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing planet texture"));
	if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing planet image"));

	if (!trollTexture.initialize(graphics, TROLL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing troll texture"));
	if (!troll.initialize(graphics, 0, 0, 0, &trollTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing troll image"));

	if (!dsTexture.initialize(graphics, DARK_SABER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing darksaber texture"));
	if (!darksaber.initialize(graphics, 546, 279, 12, &dsTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing darksaber image"));

	darksaber.setFrames(0, 59);
	darksaber.setCurrentFrame(0);
	darksaber.setFrameDelay((float) 1/30);

	// Place planet in the central of the screen
	planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	// Place cowboy in the central of the screen
	darksaber.setX(GAME_WIDTH*0.5f - darksaber.getWidth()*0.5f);
	darksaber.setY(GAME_HEIGHT*0.5f - darksaber.getHeight()*0.5f);
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void MegaMan::update()
{
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
	nebula.draw();
	planet.draw();
	troll.setScale(0.5f);
	troll.setColorFilter(graphicsNS::BLUE);
	troll.draw(graphicsNS::FILTER);

	darksaber.draw();

	graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void MegaMan::releaseAll()
{
	planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();
	trollTexture.onLostDevice();
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
	nebulaTexture.onResetDevice();
	planetTexture.onResetDevice();
	trollTexture.onResetDevice();
	dsTexture.onResetDevice();
	Game::resetAll();
	return;
}