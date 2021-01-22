#pragma once
#include "GameObject.h"

#define ANI_CANDLE	52
#define CANDLE_BBOX_WIDTH	16
#define CANDLE_BBOX_HEIGHT	31

class Candle :
    public CGameObject
{
public:
	Candle();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

