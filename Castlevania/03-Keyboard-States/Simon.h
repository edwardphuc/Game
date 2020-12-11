#pragma once
#pragma once
#include "GameObject.h"
#include "Brazier.h"
#include "StairOj.h"
#define SIMON_WALKING_SPEED		0.08f
#define SIMON_WALKING_STAIR_SPEED		    0.025f 
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_GRAVITY			0.002f
#define PULL_UP_SITTING			18.0f
#define PULL_UP_JUMPING			5.0f
#define GROUND					240.0f
#define AIR						170.0f
#define SIMON_ATTACK_TIME		300
#define SIMON_EAT_TIME          500

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_SIT				400
#define SIMON_STATE_ATTACK			500
#define SIMON_STATE_ONSTAIR_IDLE	600
#define SIMON_STATE_WALKING_UP_STAIR_RIGHT	700
#define SIMON_STATE_WALKING_UP_STAIR_LEFT	800
#define SIMON_STATE_WALKING_DOWN_STAIR_RIGHT	900
#define SIMON_STATE_WALKING_DOWN_STAIR_LEFT     1000

#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1
#define SIMON_ANI_WALKING_RIGHT		2
#define SIMON_ANI_WALKING_LEFT		3
#define SIMON_ANI_SIT				4
#define SIMON_ANI_ATTACK			5
#define SIMON_ANI_JUMP				6
#define SIMON_ANI_SIT_ATTACK		17
#define SIMON_ANI_UP_STAIR_IDLE_RIGHT 26
#define SIMON_ANI_UP_STAIR_IDLE_LEFT  27
#define SIMON_ANI_DOWN_STAIR_IDLE_RIGHT 28
#define SIMON_ANI_DOWN_STAIR_IDLE_LEFT  29
#define SIMON_ANI_WALKING_UP_STAIR_RIGHT 30
#define SIMON_ANI_WALKING_UP_STAIR_LEFT	 31
#define SIMON_ANI_WALKING_DOWN_STAIR_RIGHT 32
#define SIMON_ANI_WALKING_DOWN_STAIR_LEFT  33
#define SIMON_ANI_EAT_RIGHT				34
#define SIMON_ANI_EAT_LEFT				35


//BBox
#define SIMON_STAND_BBOX_WIDTH		58
#define SIMON_STAND_BBOX_HEIGHT		60
#define SIMON_SIT_BBOX_WIDTH		56
#define SIMON_SIT_BBOX_HEIGHT		42

class Simon : public CGameObject
{
private:
	bool issitting = false;
	bool isattacking = false;
	bool isjumping = false;
	bool onground = false;
	bool movingallow = false;
	bool issitattack = false;
	bool isonstair;
	bool ischangecolor = false;
	DWORD waitingtime = 0;
	DWORD waitingtimeatt = 0;
	DWORD attacktime = 0;
	DWORD attack_start;
	DWORD sitattack_start;
	DWORD changecolor_start;
	vector<LPGAMEOBJECT> oj;
	int whiplv;
	int stairnx;
	int allowstair = 0;
public:
	Simon(vector<LPGAMEOBJECT> oj);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT> stairoj);
	void Render();
	void SetState(int state);
	//void GetState(int x) { x = this->state; }
	DWORD Getwaitingtime() { return this->waitingtime;}
	DWORD Getwaitingtimeatt() { return this->waitingtimeatt; }
	bool Getmovingallow() { return this->movingallow; };
	bool Getsittingstate() { return this->issitting; }
	bool Getattackingstate() { return this->isattacking; }
	bool Getsitattackstate() { return this->issitattack; }
	int Getallowstair() { return this->allowstair; }
	int Getstairdirect() { return this->stairnx; }
	bool Getonstair() { return this->isonstair; }
	void Setonstair(bool x) { this->isonstair = x; }
	bool Getchangecolor() { return this->ischangecolor; }
	void GetWhiplv(int& x) { x = this->whiplv; }
	void StartAttack();
	void StartSitAttack();
	void StartChangeColor() { ischangecolor = true; changecolor_start = GetTickCount(); vx = 0; }
	void FixPositionStair();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

