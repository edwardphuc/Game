#pragma once
#include "GameObject.h"

#define ANI_MONEY	53
#define BBOX_MONEY_WIDTH   30
#define BBOX_MONEY_HEIGHT  29
#define MONEY_STATE_ACTIVE	980
#define MONEY_STATE_UNACTIVE  981
#define GRAVITY   0.00002f
class Money :
    public CGameObject
{
private:
	bool isactive;
public:
	Money();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

