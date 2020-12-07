#pragma once
#include "GameObject.h"

#define STAIR_BBOX_WIDTH	20
#define STAIR_BBOX_HEIGHT	20
class StairOj :public CGameObject
{
public:
	StairOj();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

