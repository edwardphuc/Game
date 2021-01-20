#pragma once
#include "GameObject.h"
#include "Simon.h"

#define AXE_STATE_UNACTIVE	11000
#define AXE_STATE_ACTIVE	11001
#define ANI_AXE_ACTIVE	47
#define ANI_AXE_ATTACK	48

#define AXE_BBOX_WIDTH	31
#define AXE_BBOX_HEIGHT	27
#define AXE_SPEED_X 0.25f
#define AXE_SPEED_Y 0.65f
#define AXE_GRAVITY 0.0015f

class AxeWP : public CGameObject
{
private:
	DWORD attack_start;
	bool isactive;
	Simon* simon;
	bool isallow = true;
	bool isfree = false; 
	bool isallowdirect = true;
public:
    AxeWP(Simon* sm, vector<LPGAMEOBJECT> oj);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT> enemy, int& countGhost, int& countBat, int& countFish);
	void Render();
	void StartAttack();
	void SetState(int state);
	bool Getallow() { return this->isallow; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

