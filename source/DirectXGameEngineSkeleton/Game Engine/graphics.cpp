#include "graphics.h"

//=============================================================================
// Constructor
//=============================================================================
Graphics::Graphics()
{
	direct3d = NULL;
	device3d = NULL;
	fullscreen = false;
	width = GAME_WIDTH;    // width & height are replaced in initialize()
	height = GAME_HEIGHT;
	backColor = SETCOLOR_ARGB(255, 0, 0, 128); // dark blue
	gameScale = 1;
	camera = D3DXVECTOR2(0, GAME_HEIGHT);
}

//=============================================================================
// Destructor
//=============================================================================
Graphics::~Graphics()
{
	releaseAll();
}

//=============================================================================
// Initialize DirectX graphics
// throws GameError on error
//=============================================================================
void Graphics::initialize(HWND hw, int w, int h, bool full)
{
	hwnd = hw;
	width = w;
	height = h;
	fullscreen = full;

	//initialize Direct3D
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Direct3D"));

	initD3Dpp();        // init D3D presentation parameters
	if (fullscreen)      // if full-screen mode
	{
		if (isAdapterCompatible())   // is the adapter compatible
			// set the refresh rate with a compatible one
			d3dpp.FullScreen_RefreshRateInHz = pMode.RefreshRate;
		else
			throw(GameError(gameErrorNS::FATAL_ERROR,
			"The graphics device does not support the specified resolution and/or format."));
	}

	// determine if graphics card supports harware texturing and lighting and vertex shaders
	D3DCAPS9 caps;
	DWORD behavior;
	result = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	// If device doesn't support HW T&L or doesn't support 1.1 vertex 
	// shaders in hardware, then switch to software vertex processing.
	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;  // use software only processing
	else
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;  // use hardware only processing

	//create Direct3D device
	result = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		behavior,
		&d3dpp,
		&device3d);

	if (FAILED(result))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D device"));

	// Try to create a sprite 
	result = D3DXCreateSprite(device3d, &sprite);
	if (FAILED(result))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D Sprite"));

}

//=============================================================================
// Initialize D3D presentation parameters
//=============================================================================
void Graphics::initD3Dpp()
{
	try{
		ZeroMemory(&d3dpp, sizeof(d3dpp));              // fill the structure with 0
		// fill in the parameters we need
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		if (fullscreen)                                  // if fullscreen
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;  // 24 bit color
		else
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;   // use desktop setting
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hwnd;
		d3dpp.Windowed = (!fullscreen);
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR,
			"Error initializing D3D presentation parameters"));

	}
}

//=============================================================================
// Display the backbuffer
//=============================================================================
HRESULT Graphics::showBackbuffer()
{
	// Display backbuffer to screen
	result = device3d->Present(NULL, NULL, NULL, NULL);
	return result;
}

//=============================================================================
// Checks the adapter to see if it is compatible with the BackBuffer height,
// width and refresh rate specified in d3dpp. Fills in the pMode structure with
// the format of the compatible mode, if found.
// Pre: d3dpp is initialized.
// Post: Returns true if compatible mode found and pMode structure is filled.
//       Returns false if no compatible mode found.
//=============================================================================
bool Graphics::isAdapterCompatible()
{
	UINT modes = direct3d->GetAdapterModeCount(D3DADAPTER_DEFAULT,
		d3dpp.BackBufferFormat);
	for (UINT i = 0; i < modes; i++)
	{
		result = direct3d->EnumAdapterModes(D3DADAPTER_DEFAULT,
			d3dpp.BackBufferFormat,
			i, &pMode);
		if (pMode.Height == d3dpp.BackBufferHeight &&
			pMode.Width == d3dpp.BackBufferWidth &&
			pMode.RefreshRate >= d3dpp.FullScreen_RefreshRateInHz)
			return true;
	}
	return false;
}

//=============================================================================
// Test for lost device
//=============================================================================
HRESULT Graphics::getDeviceState()
{
	result = E_FAIL;    // default to fail, replace on success
	if (device3d == NULL)
		return  result;
	result = device3d->TestCooperativeLevel();
	return result;
}

//=============================================================================
// Release all
//=============================================================================
void Graphics::releaseAll()
{
	SAFE_RELEASE(device3d);
	SAFE_RELEASE(direct3d);
}

//=============================================================================
// Reset the graphics device
//=============================================================================
HRESULT Graphics::reset()
{
	initD3Dpp();                        // init D3D presentation parameters
	result = device3d->Reset(&d3dpp);   // attempt to reset graphics device
	return result;
}

//=============================================================================
// loadTexture
//=============================================================================
HRESULT Graphics::loadTexture(const char *filename, COLOR_ARGB transcolor, UINT &width, UINT &height, LP_TEXTURE &texture)
{
	// The struct for reading file info
	D3DXIMAGE_INFO info;
	result = E_FAIL;
	try {
		if (filename == NULL)
		{
			texture = NULL;
			return D3DERR_INVALIDCALL;
		}

		// Get width and height from file
		result = D3DXGetImageInfoFromFile(filename, &info);
		if (result != D3D_OK)
			return result;
		width = info.Width;
		height = info.Height;

		// Create the new texture by loading from file
		result = D3DXCreateTextureFromFileEx(device3d,
			filename,
			info.Width,
			info.Height,
			1,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			transcolor,
			&info,
			NULL,
			&texture);

	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in Graphics::loadTexture"));
	}
	return result;
}

//=============================================================================
// drawSprite
//=============================================================================
void Graphics::drawSprite(const SpriteData &spriteData, COLOR_ARGB color)
{
	float scale = gameScale;
	if (spriteData.texture == NULL) // check if no texture
		return;

	// Find center of the sprite
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2(
		(float)(spriteData.width / 2 * scale),
		(float)(spriteData.height / 2 * scale));

	// Screen position of the sprite
	D3DXVECTOR2 translate = D3DXVECTOR2(0.0f, 0.0f);

	// Scaling
	D3DXVECTOR2 scaling = D3DXVECTOR2(scale, scale);

	// Flip horizontally
	if (spriteData.flipHorizontal)
	{
		scaling.x *= -1;				// Negative X scale to flip
		// Get center of flipped image
		spriteCenter.x == (float)(spriteData.width*scale);
		// Flip occure around left edge, translate right to put
		// flipped image in the same location as original
		translate.x += (float)(spriteData.width*scale);
	}

	// Flip vertically
	if (spriteData.flipVertical)
	{
		scaling.y *= -1;					// Negative Y scale to flip
		// Get center of flipped image
		spriteCenter.y -= (float)(spriteData.height*scale);
		// Flip occure around top edge, translate down to put
		// flipped image in the same location as original
		translate.y += (float)(spriteData.height*scale);
	}




	//*************************************************
	// Turn the world upside down, follow camera angle
	//*************************************************
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);

	mt._22 = -1.0f;
	mt._41 = -camera.x / scale;
	mt._42 = camera.y / scale;

	D3DXVECTOR4 vp_pos;
	D3DXVECTOR3 position = D3DXVECTOR3(spriteData.x, spriteData.y, 1.0f);
	D3DXVec3Transform(&vp_pos, &position, &mt); // vp_pos = position * mt

	D3DXVECTOR3 p = D3DXVECTOR3(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center = D3DXVECTOR3((float)spriteData.width / 2, (float)spriteData.height / 2, 0);

	//translate = D3DXVECTOR2(p.x, p.y);
	// Create transform matrix
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,
		NULL,
		0.0f,
		&scaling,
		&spriteCenter,
		(float)spriteData.angle,
		&translate);

	sprite->SetTransform(&matrix);

	// Draw the sprite
	sprite->Draw(spriteData.texture, &spriteData.rect, &center, &p, color);

}