#include "game.h"

//=======================================================================
// Constructor
//=======================================================================
Game::Game()
{
	input = new Input();			
	// Additional initialization is handled in the later call of input->initialize()
	paused = false;
	graphics = NULL;
	initialized = false;
}

//=======================================================================
// Destructor
//=======================================================================
Game::~Game()
{
	deleteAll();
	ShowCursor(true);
}

LRESULT Game::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (initialized)		// Do not process message if not initialized
	{
		switch (msg)
		{
		case WM_DESTROY:				// Window Message - Destroy
			PostQuitMessage();
			return 0;
		case WM_KEYDOWN: case WM_SYSKEYDOWN: // Keydown
			input->keyDown(wParam);
			return 0;
		case WM_KEYUP: case WM_SYSKEYUP:	// Keyup
			input->keyUp(wParam);
			return 0;
		case WM_CHAR:						// Character entered
			input->keyIn(wParam);
			return 0;
		case WM_MOUSEMOVE:
			input->mouseIn(lParam);
			return 0;
		case WM_INPUT:						// Raw mouse data in
			input->mouseRawIn(lParam);
			return 0;
		case WM_LBUTTONDOWN:				// Left mouse button down
			input->setMouseLButton(true);
			input->mouseIn(lParam);
			return 0;
		case WM_LBUTTONUP:					// Left mouse button up
			input->setMouseLButton(false);
			input->mouseIn(lParam);
			return 0;
		case WM_RBUTTONDOWN:				// Right mouse button down
			input->setMouseRButton(true);
			input->mouseIn(lParam);
			return 0;
		case WM_RBUTTONUP:					// Right mouse button up
			input->setMouseRButton(false);
			input->mouseIn(lParam);
			return 0;
		case WM_MBUTTONDOWN:				// Middle mouse button down
			input->setMouseMButton(true);
			input->mouseIn(lParam);
			return 0;
		case WM_MBUTTONUP:					// Middle mouse button up
			input->setMouseMButton(false);
			input->mouseIn(lParam);
			return 0;
		case WM_XBUTTONDOWN: case WM_XBUTTONUP:	// Mouse X button down/up
			input->setMouseXButton(wParam);
			input->mouseIn(lParam);
			return 0;
		case WM_DEVICECHANGE:
			input->checkControllers();
			return 0;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);		// Let window handle it.
	}
}