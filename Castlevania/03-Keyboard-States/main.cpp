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
#include "Heart.h"
#include "Ghost.h"
#include "Brick.h"

#include "Dagger.h";

#include "WhipUpgrade.h";
#include "Panther.h";
#include "StairOj.h";

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Catslevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(200, 200, 255)
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 360

#define MAX_FRAME_RATE 90

#define ID_TEX_SIMON 0
#define ID_TEX_WHIP 10
#define ID_TEX_MISC 20
#define ID_TEX_MAP1	30
#define ID_TEX_BRAZIER 40
#define ID_TEX_MAP2 50
#define ID_TEX_ITEM 60
#define ID_TEX_GHOST 70
#define ID_TEX_BRICK 80
#define ID_TEX_PANTHER 90


CGame *game;
Simon *simon;
Map  *map1;
Map  *map2;
Map* map3;
Map* map4;
Map* map5;
Whip* whip;
bool cancreateghost;
int countGhost = 0;
DWORD timecreateGhost;
//Brazier* brazier1;
//Brazier* brazier2;
//Brazier* brazier3;
//Brazier* brazier4;
//Brazier* brazier5;
vector<LPGAMEOBJECT> oj; 
vector<LPGAMEOBJECT> enemy;
vector<LPGAMEOBJECT> stairoj;

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
 		if (simon->Getwaitingtime() == 0 && simon->Getattackingstate() == false)
			simon->SetState(SIMON_STATE_JUMP);
		else simon->SetState(SIMON_STATE_IDLE);

		break;
	case DIK_A:
		if (simon->Getattackingstate() == false)
		{
			if (game->IsKeyDown(DIK_DOWN))
			{
				simon->SetState(SIMON_STATE_SIT);
				simon->StartSitAttack();
				whip->SetState(WHIP_STATE_ACTIVE);
				whip->StartAttack();

			}
			else
			{
				simon->SetState(SIMON_STATE_ATTACK);
			    whip->SetState(WHIP_STATE_ACTIVE);
			    simon->StartAttack();
			    whip->StartAttack();
			}
		}
		break;
	}
	
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	/*switch (KeyCode)
	{
	case DIK_A:
		simon->SetState(SIMON_STATE_IDLE);
		whip->SetState(WHIP_STATE_UNACTIVE);
		break;
	}*/
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	int z;
	simon->GetDirect(z);
	if (game->IsKeyDown(DIK_RIGHT) && simon->Getsittingstate() == false && simon->Getwaitingtimeatt() == 0 && simon->Getattackingstate() == false && simon->Getchangecolor() == false)
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT) && simon->Getsittingstate() == false && simon->Getwaitingtimeatt() == 0 && simon->Getattackingstate() == false && simon->Getchangecolor() == false)
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	else if (game->IsKeyDown(DIK_UP) && simon->Getonstair() == true)
	{
		if (z == 1)
		{
			simon->SetState(SIMON_STATE_WALKING_UP_STAIR_RIGHT);
		}
		else if (z == -1)
		{
			simon->SetState(SIMON_STATE_WALKING_UP_STAIR_LEFT);
		}
		
	}
	else if (game->IsKeyDown(DIK_DOWN) )
	{
		if (simon->Getonstair() == false) simon->SetState(SIMON_STATE_SIT);
		else if (simon->Getonstair() == true)
		{
			if (z == 1)
			{
				simon->SetState(SIMON_STATE_WALKING_DOWN_STAIR_RIGHT);
			}
			else if (z == -1)
			{
				simon->SetState(SIMON_STATE_WALKING_DOWN_STAIR_LEFT);
			}
		}
	}
	else if (simon->Getonstair() == true) simon->SetState(SIMON_STATE_ONSTAIR_IDLE);
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
	textures->Add(ID_TEX_ITEM, L"textures\\All_small_item.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_MAP1, L"textures\\Courtyard.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_WHIP, L"textures\\Whip.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_BRAZIER, L"textures\\Brazier.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_MAP2, L"textures\\lv2.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_GHOST, L"textures\\Ghost.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_BRICK, L"textures\\Block.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_PANTHER, L"textures\\Panther.png", D3DCOLOR_XRGB(176, 224, 248));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	LPDIRECT3DTEXTURE9 texMap1 = textures->Get(ID_TEX_MAP1);
	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);
	LPDIRECT3DTEXTURE9 texBrazier = textures->Get(ID_TEX_BRAZIER);
	LPDIRECT3DTEXTURE9 texMap2 = textures->Get(ID_TEX_MAP2);
	LPDIRECT3DTEXTURE9 texItem = textures->Get(ID_TEX_ITEM);
	LPDIRECT3DTEXTURE9 texGhost = textures->Get(ID_TEX_GHOST);
	LPDIRECT3DTEXTURE9 texBrick = textures->Get(ID_TEX_BRICK);
	LPDIRECT3DTEXTURE9 texPanther = textures->Get(ID_TEX_PANTHER);

	//Sprite Simon
	sprites->Add(10001, 0, 3, 50, 60, texSimon); //idle

	sprites->Add(10002, 57, 3, 110, 60, texSimon); //walk
	sprites->Add(10003, 175, 3, 230, 60, texSimon);
	
	sprites->Add(10004, 234, 10, 290, 52, texSimon); //sit

	sprites->Add(10005, 295, 70, 348, 127, texSimon); //attack
	sprites->Add(10006, 355, 70, 410, 127, texSimon);
	sprites->Add(10007, 415, 70, 479, 127, texSimon);

	sprites->Add(20001, 298, 10, 346, 52, texSimon); // sit attack
	sprites->Add(20002, 353, 10, 405, 52, texSimon);
	sprites->Add(20003, 412, 10, 477, 52, texSimon);

	sprites->Add(20004, 131, 68, 160, 128, texSimon);
	sprites->Add(20005, 205, 68, 234, 128, texSimon);
	sprites->Add(20006, 258, 68, 290, 128, texSimon);

	sprites->Add(20007, 14, 220, 48, 260, texSimon);
	sprites->Add(20008, 60, 220, 124, 260, texSimon);

	sprites->Add(20009, 0, 334, 48, 392, texSimon);
	sprites->Add(20010, 60, 334, 108, 392, texSimon);
	sprites->Add(20011, 120, 334, 167, 392, texSimon);

	//Sprite whip
	sprites->Add(10008, 0, 8, 18, 53, texWhip);
	sprites->Add(10009, 40, 2, 72, 38, texWhip);
	sprites->Add(10010, 94, 5, 142, 20, texWhip);

	//Sprite whip lv2
	sprites->Add(10011, 0, 66, 18, 114, texWhip);
	sprites->Add(10012, 40, 60, 72, 98, texWhip);
	sprites->Add(10013, 94, 70, 142, 82, texWhip);
	//Sprite whip lv3
	sprites->Add(10014, 94, 131, 173, 143, texWhip);
	//Map
	sprites->Add(10101, 0, 0, 1534, 350, texMap1);
	sprites->Add(10102, 0, 0, 3078, 376, texMap2);
	sprites->Add(10103, 3078, 0, 4094, 376, texMap2);
	sprites->Add(10104, 4094, 0, 5630, 376, texMap2);
	sprites->Add(10105, 3078, 376, 4094, 767, texMap2);


	//Brazier
	sprites->Add(10200, 0, 0, 30, 60, texBrazier);
	sprites->Add(10201, 32, 0, 60, 60, texBrazier);

	//Small item
	sprites->Add(10300, 0, 0, 15, 15, texItem); //heart
	sprites->Add(10301, 2, 40, 37, 55, texItem); //dagger
	sprites->Add(10302, 51, 0, 82, 32, texItem); //whip upgrade

	//Ghost
	sprites->Add(10400, 0, 0, 30, 62, texGhost);
	sprites->Add(10401, 32, 0, 60, 62, texGhost);

	//Panther
	sprites->Add(10500, 11, 1, 58, 31, texPanther);
	sprites->Add(10501, 68, 0, 128, 31, texPanther);
	sprites->Add(10503, 132, 1, 197, 31, texPanther);
	sprites->Add(10504, 202, 0, 260, 31, texPanther);
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
	animations->Add(402, ani);

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
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
	ani->Add(10102);
	animations->Add(1001, ani);

	ani = new CAnimation(100);
	ani->Add(10103);
	animations->Add(1002, ani);

	ani = new CAnimation(100);
	ani->Add(10104);
	animations->Add(1003, ani);

	ani = new CAnimation(100);
	ani->Add(10105);
	animations->Add(1004, ani);

	ani = new CAnimation(100);
	ani->Add(10200);
	ani->Add(10201);
	animations->Add(1100, ani);

	ani = new CAnimation(100);
	ani->Add(10300);
	animations->Add(1300, ani);

	ani = new CAnimation(100);
	ani->Add(10400);
	ani->Add(10401);
	animations->Add(1400, ani);

	ani = new CAnimation(100);
	ani->Add(10400);
	ani->Add(10401);
	animations->Add(1401, ani);

	ani = new CAnimation(100);
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	animations->Add(2000, ani);

	ani = new CAnimation(100);
	ani->Add(10301);
	animations->Add(2100, ani);

	ani = new CAnimation(100);
	ani->Add(10302);
	animations->Add(2200, ani);


	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(802, ani);


	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10014);
	animations->Add(803, ani);

	ani = new CAnimation(100);
	ani->Add(10500);
	animations->Add(3000, ani);

	ani = new CAnimation(100);
	ani->Add(10501);
	animations->Add(3100, ani);

	ani = new CAnimation(100);
	ani->Add(10501);
	ani->Add(10502);
	ani->Add(10503);
	animations->Add(3200, ani);

	ani = new CAnimation(100);
	ani->Add(10501);
	ani->Add(10502);
	ani->Add(10503);
	animations->Add(3300, ani);

	ani = new CAnimation(100);
	ani->Add(20004);
	animations->Add(4000, ani);

	ani = new CAnimation(100);
	ani->Add(20004);
	animations->Add(4001, ani);

	ani = new CAnimation(100);
	ani->Add(20006);
	animations->Add(4002, ani);

	ani = new CAnimation(100);
	ani->Add(20006);
	animations->Add(4003, ani);

	ani = new CAnimation(100);
	ani->Add(20005);
	ani->Add(20004);
	animations->Add(4004, ani);
	
	ani = new CAnimation(100);
	ani->Add(20005);
	ani->Add(20004);
	animations->Add(4005, ani);

	ani = new CAnimation(100);
	ani->Add(20005);
	ani->Add(20006);
	animations->Add(4006, ani);

	ani = new CAnimation(100);
	ani->Add(20005);
	ani->Add(20006);
	animations->Add(4007, ani);

	ani = new CAnimation(100);
	ani->Add(20009);
	ani->Add(20010);
	ani->Add(20011);
	animations->Add(4008, ani);

	ani = new CAnimation(100);
	ani->Add(20009);
	ani->Add(20010);
	ani->Add(20011);
	animations->Add(4009, ani);



	Simon::AddAnimation(400);		// idle right
	Simon::AddAnimation(401);		// idle left
	Simon::AddAnimation(402);		// walk right
	Simon::AddAnimation(403);		// walk left
	Simon::AddAnimation(404);       // sit
	Simon::AddAnimation(405);       // attack
	Simon::AddAnimation(406);		// jump

	map1 = new Map();
	Map::AddAnimation(1000);
	map2 = new Map();
	map3 = new Map();
	map4 = new Map();
	map5 = new Map();
	Whip::AddAnimation(801);

	Brazier *brazier1 = new Brazier(); // Khoi tao brazier
	Brazier *brazier2 = new Brazier();
	Brazier *brazier3 = new Brazier();	
	Brazier *brazier4 = new Brazier();
	Brazier *brazier5 = new Brazier();

	Heart* heart1 = new Heart();
	Heart* heart2 = new Heart();
	
	Dagger* dagger = new Dagger();

	WhipUpgrade* upgrade1 = new WhipUpgrade();
	WhipUpgrade* upgrade2 = new WhipUpgrade();

	Brazier::AddAnimation(1100);
	Map::AddAnimation(1001);
	Map::AddAnimation(1002);
	Map::AddAnimation(1003);
	Map::AddAnimation(1004);

	Heart::AddAnimation(1300);

	Ghost::AddAnimation(1400);
	Ghost::AddAnimation(1401);

	Simon::AddAnimation(2000);
	Dagger::AddAnimation(2100);
	WhipUpgrade::AddAnimation(2200);
	Whip::AddAnimation(802);
	Whip::AddAnimation(803);

	Panther::AddAnimation(3000);
	Panther::AddAnimation(3100);
	Panther::AddAnimation(3200);
	Panther::AddAnimation(3300);

	Simon::AddAnimation(4000);
	Simon::AddAnimation(4001);
	Simon::AddAnimation(4002);
	Simon::AddAnimation(4003);
	Simon::AddAnimation(4004);
	Simon::AddAnimation(4005);
	Simon::AddAnimation(4006);
	Simon::AddAnimation(4007);
	Simon::AddAnimation(4008);
	Simon::AddAnimation(4009);
	for (int i = 0; i < 48; i++)
	{
		Brick* brick = new Brick();
		brick->SetPosition(i * 29.0f, 301.0f);
		oj.push_back(brick);
	}
	map1->SetPosition(-40.0f, -20.0f);
	map2->SetPosition(1215.0f, -28.0f);
	map3->SetPosition(3980.0f, -28.0f);
	map4->SetPosition(4804.0f, -28.0f);
	map5->SetPosition(3980.0f, 280.0f);
	

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
	oj.push_back(heart1);
	oj.push_back(dagger);
	oj.push_back(upgrade1);
	oj.push_back(heart2);
	oj.push_back(upgrade2);
	for (int i = 0; i < 94; i++)
	{
		Brick* brick = new Brick();
		brick->SetPosition(1420 + i * 29.0f, 305.0f);
		oj.push_back(brick);
	}
	/*for (int i = 0; i < 2; i++)
	{
		Panther *panther = new Panther();
		if (i == 0)
		{
			panther->SetPosition(1900, 150);
		}
		if (i == 1)
		{

		}
		if (i == 2)
		{

		}
		enemy.push_back(panther);
	}*/
	/*for (int i = 0; i < 6; i++)
	{
		Ghost* ghost = new Ghost();
		if (i < 3)
		{
			ghost->SetPosition(1420 + i * 50.0f, 240.0f);
			ghost->Setstate(GHOST_STATE_WALKING_RIGHT);
			oj.push_back(ghost);
		}
		else if (i >= 3 && i < 6)
		{
			ghost->SetPosition(2100 - i * 50.0f, 240.0f);
			ghost->Setstate(GHOST_STATE_WALKING_LEFT);
			oj.push_back(ghost);
		}
	}*/
	StairOj* stair1 = new StairOj();
	stair1->SetPosition(2460.0f, 280.0f);
	stairoj.push_back(stair1);

	StairOj* stair2 = new StairOj();
	stair2->SetPosition(2560.0f, 100.0f);
	stairoj.push_back(stair2);

	simon = new Simon(oj);
	simon->SetPosition(0.0f, 240.0f);
	float x, y;
	simon->GetPosition(x, y);
	/*if (GetTickCount() - timecreateGhost > 1000)
	{
		if (x >= 1600 && x < 2200)
		{
			if (countGhost < 3)
			{
				timecreateGhost = GetTickCount();
				Ghost* ghost = new Ghost();
				int z;
				simon->GetDirect(z);
				if (z == 1)
				{
					countGhost++;
					ghost->SetState(GHOST_STATE_WALKING_LEFT);
				}
				else if (z == -1)
				{
					countGhost++;
					ghost->SetState(GHOST_STATE_WALKING_RIGHT);
				}
			}
		}
	}*/
	
	whip = new Whip(simon, oj);
	whip->SetPosition(x, y);

	
	
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	float cx, cy;
	simon->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 10;
	cy -= SCREEN_HEIGHT / 10;
	float x, y;
	simon->GetPosition(x, y);


	if (x == 0 || x < SCREEN_WIDTH / 10)
	{
		CGame::GetInstance()->SetCamPos(0.0f, 0.0f);
	}
	else if (x > 1533 - 640 - 64 && x < 1280)
	{
		CGame::GetInstance()->SetCamPos(1533 - 640 - 64 - 64, 0.0f);
	}
	else if (x == 1280 || (x < 1445 + 64 && x > 1280))
	{
		CGame::GetInstance()->SetCamPos(1445, 0.0f);
	}
	else if (x > 4200 - 640 - 64 && x < 4000)
	{
		CGame::GetInstance()->SetCamPos(4200 - 640 - 64 - 64, 0.0f);
	}
	else if (x == 4050 || (x > 4050 && x < 4050 + 64))
	{
		CGame::GetInstance()->SetCamPos(4050, 0.0f);
	}
	else CGame::GetInstance()->SetCamPos(cx, 0.0f);
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 0; i < oj.size(); i++)
	{
		coObjects.push_back(oj[i]);
	}
	for (int i = 0; i < stairoj.size(); i++)
	{
		oj[i]->Update(dt, &coObjects);
	}
	simon->Update(dt, &coObjects, stairoj);
	if (GetTickCount() - timecreateGhost > 2000)
	{
		if (x >= 1600 && x < 3000)
		{
			DWORD now = GetTickCount();
			timecreateGhost = now;
			if (countGhost < 3)
			{
				timecreateGhost = GetTickCount();
				Ghost* ghost = new Ghost();
				int z;
				simon->GetDirect(z);
				if (z == 1)
				{
					countGhost++;
					ghost->SetState(GHOST_STATE_WALKING_LEFT);
					ghost->SetPosition(4000, 240);
				}
				else if (z == -1)
				{
					countGhost++;
					ghost->SetState(GHOST_STATE_WALKING_RIGHT);
					ghost->SetPosition(1600, 240);
				}
				enemy.push_back(ghost);
			}
		}
	}
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Update(dt, &coObjects);
	}
	

	for (int i = 0; i < enemy.size(); i++)
	{
		coObjects.push_back(enemy[i]);
	}
	
	
	for (int i = 0; i < oj.size(); i++)
	{
		oj[i]->Update(dt, &coObjects);
	}
	
	whip->Update(dt, &coObjects, enemy, countGhost);
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
		map1->render(1000);
		map2->render(1001);
		map3->render(1002);
		map4->render(1003);
		map5->render(1004);

		for (int i = 0; i < stairoj.size(); i++)
		{
			stairoj[i]->Render();
		}
		for (int i = 0; i < oj.size(); i++)
		{
			oj[i]->Render();
		}
		for (int i = 0; i < enemy.size(); i++)
		{
			enemy[i]->Render();
		}
		simon->Render();
		whip->Render();
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