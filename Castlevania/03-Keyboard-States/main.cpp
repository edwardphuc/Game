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
#include "Whip.h"
#include "Brazier.h"

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
#define ID_TEX_BRAZIER 40

CGame *game;
Simon *simon;
Map  *map;
Whip* whip;
//Brazier* brazier1;
//Brazier* brazier2;
//Brazier* brazier3;
//Brazier* brazier4;
//Brazier* brazier5;
vector<LPGAMEOBJECT> oj; //brazier ob

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

		break;
	case DIK_A:
		simon->SetState(SIMON_STATE_ATTACK);
		whip->SetState(WHIP_STATE_ACTIVE);
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
	/*else if (game->IsKeyDown(DIK_A))
	{
		simon->SetState(SIMON_STATE_ATTACK);
		whip->SetState(WHIP_STATE_ACTIVE);
	}*/
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
	textures->Add(ID_TEX_WHIP, L"textures\\Whip.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_BRAZIER, L"textures\\Brazier.png", D3DCOLOR_XRGB(176, 224, 248));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	LPDIRECT3DTEXTURE9 texMap = textures->Get(ID_TEX_MAP);
	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);
	LPDIRECT3DTEXTURE9 texBrazier = textures->Get(ID_TEX_BRAZIER);


	//Sprite Simon
	sprites->Add(10001, 0, 3, 50, 60, texSimon); //idle

	sprites->Add(10002, 57, 3, 110, 60, texSimon); //walk
	sprites->Add(10003, 175, 3, 230, 60, texSimon);
	
	sprites->Add(10004, 234, 10, 290, 52, texSimon); //sit

	sprites->Add(10005, 295, 70, 348, 127, texSimon); //attack
	sprites->Add(10006, 355, 70, 410, 127, texSimon);
	sprites->Add(10007, 415, 70, 479, 127, texSimon);

	//Sprite whip
	sprites->Add(10008, 0, 0, 18, 53, texWhip);
	sprites->Add(10009, 39, 0, 73, 36, texWhip);
	sprites->Add(10010, 93, 5, 143, 19, texWhip);

	//Map
	sprites->Add(10101, 0, 0, 1534, 350, texMap);

	//Brazier
	sprites->Add(10200, 0, 0, 30, 60, texBrazier);
	sprites->Add(10201, 32, 0, 60, 60, texBrazier);

	LPANIMATION ani;

	ani = new CAnimation(100);	
	ani->Add(10002);
	animations->Add(400, ani);

	ani = new CAnimation(100);
	ani->Add(10002);
	animations->Add(401, ani);


	ani = new CAnimation(100);
	ani->Add(10002);
	ani->Add(10001);
	ani->Add(10003);
	animations->Add(402, ani);

	ani = new CAnimation(100);
	ani->Add(10002);
	ani->Add(10001);
	ani->Add(10003);
	animations->Add(403, ani);

	ani = new CAnimation(100);
	ani->Add(10004);
	animations->Add(404, ani);

	ani = new CAnimation(100);
	ani->Add(10005);
	ani->Add(10006);
	ani->Add(10007);
	animations->Add(405, ani);

	ani = new CAnimation(100);
	ani->Add(10008);
	ani->Add(10009);
	ani->Add(10010);
	animations->Add(801, ani);

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(406, ani);

	ani = new CAnimation(100);
	ani->Add(10101);
	animations->Add(1000, ani);

	ani = new CAnimation(100);
	ani->Add(10200);
	ani->Add(10201);
	animations->Add(1100, ani);

	simon = new Simon();
	Simon::AddAnimation(400);		// idle right
	Simon::AddAnimation(401);		// idle left
	Simon::AddAnimation(402);		// walk right
	Simon::AddAnimation(403);		// walk left
	Simon::AddAnimation(404);       // sit
	Simon::AddAnimation(405);       // attack
	Simon::AddAnimation(406);		// jump

	map = new Map();
	Map::AddAnimation(1000);

	whip = new Whip(simon);
	Whip::AddAnimation(801);

	Brazier *brazier1 = new Brazier();
	Brazier *brazier2 = new Brazier();
	Brazier *brazier3 = new Brazier();
	Brazier *brazier4 = new Brazier();
	Brazier *brazier5 = new Brazier();
	Brazier::AddAnimation(1100);

	simon->SetPosition(0.0f, 240.0f);
	map->SetPosition(-40.0f, -20.0f);
	float x, y;
	simon->GetPosition(x, y);
	whip->SetPosition(x, y);

	brazier1->SetPosition(253.0f, 235.0f);
    brazier2->SetPosition(375.0f, 235.0f);
	brazier3->SetPosition(506.0f, 235.0f);
	brazier4->SetPosition(700.0f, 235.0f);
	brazier5->SetPosition(870.0f, 235.0f);

	oj.push_back(brazier1);
	oj.push_back(brazier2);
	oj.push_back(brazier3);
	oj.push_back(brazier4);
	oj.push_back(brazier5);
	oj.push_back(whip);
	oj.push_back(simon);
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
	whip->Update(dt);
	
	if (x == 0 || x < SCREEN_WIDTH/10)
	{
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
	}
	else if (x > 1533-640-64)
	{
		CGame::GetInstance()->SetCamPos(1533-640-64-64, 0.0f);
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
		for (int i = 0; i < oj.size(); i++)
		{
			oj[i]->Render();
		}
		
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
	DWORD tickPerFrame = 1000/ MAX_FRAME_RATE;

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