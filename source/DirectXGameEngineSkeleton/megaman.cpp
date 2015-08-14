#include "megaman.h"

//=============================================================================
// Constructor
//=============================================================================
MegaMan::MegaMan()
{
	rmTexture = new TextureManager();
	megaman = new GameObject();
	megaman->addComponent(new UserInputComponent(2.4f), false);
	megaman->addComponent(new AutoInputComponent(2.4f), false);

}

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

	if (!rmTexture->initialize(graphics, MEGAMAN_SPRITE))
		throw(GameError(gameErrorNS::FATAL_ERROR,
		"Error initializing rockman texture"));

	megaman->spriteInitialize(graphics, rmTexture);
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void MegaMan::update()
{
	UINT step = 10;

	// Scaling world
	if (input->wasKeyPressed(VK_RETURN))
		graphics->setGameScale(graphics->getGameScale() + 0.5f);

	if (input->wasKeyPressed(VK_SPACE) &&  graphics->getGameScale() > 0)
		graphics->setGameScale(graphics->getGameScale() - 0.2f);

	// Move camera code
	D3DXVECTOR2 camera_angle = graphics->getCamera();
	if (input->wasKeyPressed(VK_NUMPAD6))
	{
		camera_angle.x += step;
		graphics->setCamera(camera_angle);
	}
	if (input->wasKeyPressed(VK_NUMPAD4))
	{
		camera_angle.x -= step;
		graphics->setCamera(camera_angle);
	}
	if (input->wasKeyPressed(VK_NUMPAD2))
	{
		camera_angle.y -= step;
		graphics->setCamera(camera_angle);
	}
	if (input->wasKeyPressed(VK_NUMPAD8))
	{
		camera_angle.y += step;
		graphics->setCamera(camera_angle);
	}

	megaman->update(input);
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

	megaman->render(interpolation);

	graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void MegaMan::releaseAll()
{
	rmTexture->onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void MegaMan::resetAll()
{
	rmTexture->onResetDevice();
	Game::resetAll();
	return;
}