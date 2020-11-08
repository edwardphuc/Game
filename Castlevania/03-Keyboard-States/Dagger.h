#pragma once
#include "GameObject.h"

#define ANI_DAGGER 17

#define BBOX_DAGGER_WIDTH   38
#define BBOX_DAGGER_HEIGHT  18

#define DAGGER_STATE_ACTIVE   1000
#define DAGGER_STATE_UNACTIVE 1100
class Dagger: public CGameObject
{
private:
	bool isactive;
public:
	Dagger();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Setstate(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

