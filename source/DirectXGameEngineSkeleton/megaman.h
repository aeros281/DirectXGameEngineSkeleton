#ifndef _MEGAMAN_H             // prevent multiple definitions if this 
#define _SPACEWAR_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "Game Engine/game.h"
#include "Game Engine/textureManager.h"
#include "Game Engine/image.h"
#include <WinUser.h>
#include "Game Engine\UserInputComponent.h"
#include "Game Engine\AutoInputComponent.h"
#include "Game Engine/GameObject.h"

//=============================================================================
// Create game class
//=============================================================================
class MegaMan : public Game
{
private:
	// variables
	// Game items

	TextureManager *rmTexture;

	GameObject *megaman;
public:
	// Constructor
	MegaMan();

	// Destructor
	virtual ~MegaMan();

	// Initialize the game
	void initialize(HWND hwnd);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();
};

#endif