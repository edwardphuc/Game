#pragma once
#include "GameObject.h"


#define BBOX_BRICK_WIDTH 29
#define BBOX_BRICK_HEIGHT 20
class Brick : public CGameObject
{
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};



