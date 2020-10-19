#pragma once
#include "GameObject.h"
#define BRAZIER 9
#define BRAZIER_STATE_ACTIVE 2000
#define BRAZIER_STATE_UNACTIVE 2500
//BBOX
#define BRAZIER_BBOX_WIDTH   30
#define BRAZIER_BBOX_HEIGHT	 60

class Brazier: public CGameObject
{
private:
	bool isappearing = true;
public:
	    void Render();
		void GetBoundingBox(float& left, float& top, float& right, float& bottom);
		void SetState(int state);
};

