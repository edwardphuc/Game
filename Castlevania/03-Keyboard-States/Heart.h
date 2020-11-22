#pragma once
#include "GameObject.h"
#define GRAVITY   0.00005f
#define ANI_HEART 14

#define BBOX_HEART_WIDTH   27
#define BBOX_HEART_HEIGHT  27

#define HEART_STATE_ACTIVE 1001
#define HEART_STATE_UNACTIVE 1002
class Heart : public CGameObject
{
private:
	bool isactive;
public:
	Heart();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Setstate(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

