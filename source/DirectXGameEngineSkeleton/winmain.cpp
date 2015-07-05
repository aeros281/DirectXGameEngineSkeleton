#define WIN32_LEAN_AND_MEAN

#include <windows.h>

// Function prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

// Global variable
HINSTANCE hinst;
HDC hdc;							// Handle to device context
TCHAR ch = ' ';						// Character entered
RECT rect;							// Rectangle structure
PAINTSTRUCT ps;						// Used in WM_PAINT

// Constants
const char CLASS_NAME[] = "WinMain";
const char APP_TITLE[] = "Hello World";   // title bar text
const int  WINDOW_WIDTH = 400;             // width of window
const int  WINDOW_HEIGHT = 400;             // height of window

//=============================================================================
// Starting point for a Windows application
// Parameters are:
//   hInstance - handle to the current instance of the application
//   hPrevInstance - always NULL, obsolete parameter, maintained for backwards compatibilty
//   lpCmdLine - pointer to null-terminated string of command line arguments
//   nCmdShow - specifies how the window is to be shown
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	MSG	 msg;

	// Create the window
	if (!CreateMainWindow(hInstance, nCmdShow))
		return false;

	// main message loop
	int done = 0;
	while (!done)
	{
		// PeekMessage is a non-blocking method for checking for Windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//look for quit message
			if (msg.message == WM_QUIT)
				done = 1;

			//decode and pass messages on to WinProc
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

//=============================================================================
// window event callback function
//=============================================================================
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
			//tell Windows to kill this program
			PostQuitMessage(0);
			return 0;
		case WM_CHAR:
			switch (wParam)
			{
			case 0x08:	// Backspace
			case 0x09:	// Tab
			case 0x0A:	// Line feed
			case 0x0D:	// Carriage return
			case 0x1B:	// Escape
				MessageBeep((UINT)-1);	// Beep but do not display
				return 0;
			default:		// Displayable character
				ch = (TCHAR)wParam;		// Get the character
				InvalidateRect(hWnd, NULL, TRUE);	// Force WM_PAINT
				return 0;
			}
		case WM_PAINT:				// The window needs to be redrawn
			hdc = BeginPaint(hWnd, &ps);		// Get handle to device context
			GetClientRect(hWnd, &rect);			// Get the window rectangle
			// Display the character
			TextOut(hdc, rect.right / 2, rect.bottom / 2, &ch, 1);
			EndPaint(hWnd, &ps);
			return 0;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

//=============================================================================
// Create the window
// Returns: false on error
//=============================================================================
bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcx;
	HWND hwnd;

	// Fill in the window class structure with parameters 
	// that describe the main window. 
	wcx.cbSize = sizeof(wcx);           // size of structure 
	wcx.style = CS_HREDRAW | CS_VREDRAW;    // redraw if size changes 
	wcx.lpfnWndProc = WinProc;          // points to window procedure 
	wcx.cbClsExtra = 0;                 // no extra class memory 
	wcx.cbWndExtra = 0;                 // no extra window memory 
	wcx.hInstance = hInstance;          // handle to instance 
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);   // predefined arrow 
	wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);    // black background brush 
	wcx.lpszMenuName = NULL;           // name of menu resource 
	wcx.lpszClassName = CLASS_NAME;     // name of window class 
	wcx.hIconSm = NULL;                 // small class icon 

	// Register the window class. 
	// RegisterClassEx returns 0 on error.
	if (RegisterClassEx(&wcx) == 0)    // if error
		return false;

	// Create window
	hwnd = CreateWindow(
		CLASS_NAME,             // name of the window class
		APP_TITLE,              // title bar text
		WS_OVERLAPPEDWINDOW,    // window style
		CW_USEDEFAULT,          // default horizontal position of window
		CW_USEDEFAULT,          // default vertical position of window
		WINDOW_WIDTH,           // width of window
		WINDOW_HEIGHT,          // height of the window
		(HWND)NULL,            // no parent window
		(HMENU)NULL,           // no menu
		hInstance,              // handle to application instance
		(LPVOID)NULL);         // no window parameters

	// if there was an error creating the window
	if (!hwnd)
		return false;

	// Show the window
	ShowWindow(hwnd, nCmdShow);

	// Send a WM_PAINT message to the window procedure
	UpdateWindow(hwnd);
	return true;
}
