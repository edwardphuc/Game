#pragma once
#include "GameObject.h"

#define BOSS_BBOX_WIDTH	    85
#define BOSS_BBOX_HEIGHT	45

#define BOSS_STATE_SLEEP	10000
#define BOSS_STATE_WAKE		10001

#define BOSS_ANI_SLEEP		46
class Boss :
    public CGameObject
{
private:
	bool issleep;
public:
	Boss();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

