#pragma once
#include "GameObject.h"

#define GHOST_ANI_WALKING_RIGHT            15
#define GHOST_ANI_WALKING_LEFT             16
#define GHOST_BBOX_WIDTH     30
#define GHOST_BBOX_HEIGHT	 60

#define GHOST_STATE_WALKING_RIGHT 3000
#define GHOST_STATE_WALKING_LEFT 3100
#define GHOST_WALKING_SPEED		0.2f


class Ghost :public CGameObject
{
public:
	Ghost();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Setstate(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

