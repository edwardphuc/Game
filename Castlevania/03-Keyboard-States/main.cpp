/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 03 - KEYBOARD AND OBJECT STATE

	This sample illustrates how to:

		1/ Process keyboard input
		2/ Control object state with keyboard events
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Simon.h"
#include "Map.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Catslevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 360

#define MAX_FRAME_RATE 90

#define ID_TEX_SIMON 0
#define ID_TEX_WHIP 10
#define ID_TEX_MISC 20
#define ID_TEX_MAP	30

CGame *game;
Simon *simon;
Map  *map;
class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (simon->Getwaitingtime() == 0)
			simon->SetState(SIMON_STATE_JUMP);
		else simon->SetState(SIMON_STATE_IDLE);
	case DIK_A:
		simon->SetState(SIMON_STATE_ATTACK);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	if (game->IsKeyDown(DIK_RIGHT) && simon->Getsittingstate() == false)
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT) && simon->Getsittingstate() == false)
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	else if (game->IsKeyDown(DIK_DOWN))
		simon->SetState(SIMON_STATE_SIT);
	else simon->SetState(SIMON_STATE_IDLE);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_SIMON, L"textures\\Simon.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_MAP, L"textures\\Courtyard.png", D3DCOLOR_XRGB(255, 255, 255));

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	LPDIRECT3DTEXTURE9 texMap = textures->Get(ID_TEX_MAP);
	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);

	textures->Add(ID_TEX_WHIP, L"textures\\Whip.png", D3DCOLOR_XRGB(176, 224, 248));

	//Sprite Simon
	sprites->Add(10001, 16, 3, 50, 60, texSimon);

	sprites->Add(10002, 75, 3, 110, 60, texSimon);
	sprites->Add(10003, 193, 3, 230, 60, texSimon);
	
	sprites->Add(10004, 252, 10, 290, 52, texSimon);

	sprites->Add(10005, 298, 70, 348, 127, texSimon);
	sprites->Add(10006, 373, 70, 410, 127, texSimon);
	sprites->Add(10007, 435, 70, 479, 127, texSimon);

	//Sprite whip
	sprites->Add(10008, 0, 8, 18, 53, texWhip);
	sprites->Add(10009, 39, 0, 73, 36, texWhip);
	sprites->Add(10010, 93, 5, 143, 19, texWhip);

	//Map
	sprites->Add(10101, 0, 0, 760, 202, texMap);

	LPANIMATION ani;

	ani = new CAnimation(100);	
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(401, ani);


	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(501, ani);

	ani = new CAnimation(100);
	ani->Add(10004);
	animations->Add(601, ani);

	ani = new CAnimation(100);
	ani->Add(10005);
	ani->Add(10006);
	ani->Add(10007);
	animations->Add(701, ani);

	ani = new CAnimation(100);
	ani->Add(10008);
	ani->Add(10009);
	ani->Add(100010);
	animations->Add(801, ani);

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(901, ani);

	ani = new CAnimation(100);
	ani->Add(10101);
	animations->Add(1000, ani);

	simon = new Simon();
	Simon::AddAnimation(400);		// idle right
	Simon::AddAnimation(401);		// idle left
	Simon::AddAnimation(500);		// walk right
	Simon::AddAnimation(501);		// walk left
	Simon::AddAnimation(601);       // sit
	Simon::AddAnimation(701);       // attack
	Simon::AddAnimation(901);		// jump

	map = new Map();
	Map::AddAnimation(1000);

	simon->SetPosition(0.0f, 240.0f);
	map->SetPosition(0.0f, 0.0f);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	simon->Update(dt);
	
	float cx, cy;
	simon->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 10 ;
	cy -= SCREEN_HEIGHT/ 10 ;
	float x, y;
	simon->GetPosition(x, y);
	if (x == 0 || x < SCREEN_WIDTH/10)
	{
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
	}
	else if (x > SCREEN_WIDTH)
	{
		CGame::GetInstance()->SetCamPos(SCREEN_WIDTH - SCREEN_WIDTH/10, 0.0f);
	}
	else CGame::GetInstance()->SetCamPos(cx, 0.0f);
	
	
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		map->Render();
		simon->Render();
		
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();
	Run();

	return 0;
}