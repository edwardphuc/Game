#pragma once
#include "GameObject.h"
#include "Simon.h"

#define BOSS_START_TIME		1000
#define BOSS_CURVING_TIME	600
#define BOSS_BACKING_TIME	600
#define BOSS_OP_TIME		600
#define BOSS_WAITING_TIME	1500
#define BOSS_BBOX_WIDTH	    85
#define BOSS_BBOX_HEIGHT	45

#define BOSS_STATE_SLEEP	10000
#define BOSS_STATE_WAKE		10001

#define BOSS_ANI_SLEEP		46
#define BOSS_ANI_WAKE		51
class Boss :
    public CGameObject
{
private:
	float originalX, originalY;
	DWORD start_time;
	DWORD curving_time;
	DWORD back_time;
	DWORD OP_time;
	DWORD waitingtime;
	bool issleep;
	bool isstarting;
	bool iscurving;
	bool isbacking;
	bool isOP;
	Simon* simon;
	bool allowstart;
	bool allowcurving;
	bool allowstraight;
	bool allowback;
	bool allowOP;     //OP:Original Position
	bool iswaiting = false;
public:
	Boss(Simon* sm);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Start() { start_time = GetTickCount(); isstarting = true; }
	void Startcurving() { curving_time = GetTickCount(); iscurving = true; }
	void Start_back() { back_time = GetTickCount(); isbacking = true; }
	void StartOP() { OP_time = GetTickCount(); isOP = true; }
	void StartWait() { waitingtime = GetTickCount(); iswaiting = true; }
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

