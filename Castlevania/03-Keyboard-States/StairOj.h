#pragma once
#include "GameObject.h"

#define STAIR_BBOX_WIDTH	10
#define STAIR_BBOX_HEIGHT	10
class StairOj :public CGameObject
{
public:
	StairOj();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

