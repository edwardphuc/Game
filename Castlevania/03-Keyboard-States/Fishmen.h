#pragma once
#include "GameObject.h"

#define FISH_ANI_WALKING_RIGHT	41
#define FISH_ANI_WALKING_LEFT	42
#define FISH_ANI_ATTACK			43

#define FISH_STATE_WALKING_RIGHT	1235
#define FISH_STATE_WALKING_LEFT	    1236
#define FISH_STATE_ATTACK			1237
#define FISH_STATE_JUMP			1238
class Fishmen :
    public CGameObject
{
private:
	float originalX;
	float originalY;
public:
	Fishmen();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

