#pragma once
#pragma once
#include "GameObject.h"
#include "Brazier.h"
#include "StairOj.h"
#define SIMON_WALKING_SPEED		0.05f
#define SIMON_WALKING_STAIR_SPEED		    0.025f 
#define SIMON_JUMP_SPEED_Y		0.45f
#define SIMON_JUMP_TIME             500
#define SIMON_GRAVITY			0.0015f
#define PULL_UP_SITTING			18.0f
#define PULL_UP_JUMPING			5.0f
#define GROUND					240.0f
#define AIR						170.0f
#define SIMON_ATTACK_TIME		300
#define SIMON_EAT_TIME          500
#define SIMON_DAMAGED_TIME		450
#define SIMON_UNTOUCHABLE_TIME	2800
#define SIMON_DIE_DEFLECT_SPEED	0.5f
#define SIMON_DIE_TIME			2000

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
#define SIMON_STATE_DIE							1100

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
#define SIMON_ANI_DAMAGED_RIGHT			37
#define SIMON_ANI_DAMAGED_LEFT			38
#define	SIMON_ANI_DIE					39

//BBox
#define SIMON_STAND_BBOX_WIDTH		58
#define SIMON_STAND_BBOX_HEIGHT		62
#define SIMON_SIT_BBOX_WIDTH		56
#define SIMON_SIT_BBOX_HEIGHT		48

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
	bool isdamaged = false;
	bool isuntouchable = false;
	bool isdied = false;
	bool enable_reset = true;
	bool getpullup = false;
	int soluongdao;
	float originalY;
	DWORD waitingtime = 0;
	DWORD waitingtimeatt = 0;
	DWORD attacktime = 0;
	DWORD attack_start;
	DWORD sitattack_start;
	DWORD changecolor_start;
	DWORD damaged_start;
	DWORD untouchable_start;
	DWORD dietime_start;
	DWORD jump_start;
	DWORD sit_start;
	vector<LPGAMEOBJECT> oj;
	int whiplv;
	int stairnx;
	int allowstair = 0;
	int dem = 0;
	bool allowsit;
public:
	Simon(vector<LPGAMEOBJECT> oj);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT> stairoj, vector<LPGAMEOBJECT> enemy);
	void Render();
	void SetState(int state);
	//void GetState(int x) { x = this->state; }
	DWORD Getwaitingtime() { return this->waitingtime;}
	DWORD Getwaitingtimeatt() { return this->waitingtimeatt; }
	bool Getjump() { return this->isjumping; }
	bool Getmovingallow() { return this->movingallow; };
	bool Getsittingstate() { return this->issitting; }
	bool Getattackingstate() { return this->isattacking; }
	bool Getsitattackstate() { return this->issitattack; }
	int Getallowstair() { return this->allowstair; }
	int Getstairdirect() { return this->stairnx; }
	int Getsoluongdao() { return this->soluongdao; }
	bool Getonstair() { return this->isonstair; }
	bool GetAllowsit() { return this->allowsit; }
	bool GetDamaged() { return this->isdamaged; }
	void Setonstair(bool x) { this->isonstair = x; }
	bool Getchangecolor() { return this->ischangecolor; }
	void SetPullUp(bool a) { this->getpullup = a; }
	void GetWhiplv(int& x) { x = this->whiplv; }
	bool GetUntouchable() { return this->isuntouchable; }
	void Setsoluongdao(int x) { this->soluongdao = x; }
	void StartAttack();
	void StartSitAttack();
	void StartJump() { isjumping = true; jump_start = GetTickCount(); allowsit = false; }
	void StartChangeColor() { ischangecolor = true; changecolor_start = GetTickCount(); vx = 0; }
	void StartIsDamaged() { isdamaged = true; damaged_start = GetTickCount();}
	void StartUntouchable() { isuntouchable = true; untouchable_start = GetTickCount(); }
	void StartDieTime() { isdied = true; dietime_start = GetTickCount(); this->SetHP(this->GetHP() - 1); isuntouchable = false; isdamaged = false; }
	void StartSit() { issitting = true; sit_start = GetTickCount(); }
	void FixPositionStair();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void resettodefault();
};

