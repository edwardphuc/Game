#pragma once
#include "GameObject.h"

#define BAT_BBOX_WIDTH 33
#define BAT_BBOX_HEIGHT	34
#define BAT_ANI_FLY_LEFT		40

#define BAT_STATE_FLY_LEFT		1234
#define BAT_FLYING_SPEED_X	0.1f
#define BAT_FLYING_SPEED_Y	0.05f

class Bat :public CGameObject
{
private:
	float ybackup;
public:
	Bat();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Setybackup(float y1) { ybackup = y1; }
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

