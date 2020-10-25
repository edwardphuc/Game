#pragma once
#include "GameObject.h"

#define ANI_HEART 14

#define BBOX_HEART_WIDTH   15
#define BBOX_HEART_HEIGHT  15

#define HEART_STATE_ACTIVE 1000
#define HEART_STATE_UNACTIVE 1001
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

