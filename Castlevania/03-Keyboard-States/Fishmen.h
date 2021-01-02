#pragma once
#include "GameObject.h"
#include "FireBall.h"
#include "Simon.h"

#define FISH_ATTACK_TIME		400
#define FISH_ANI_IDLE			41
#define FISH_ANI_WALKING_RIGHT	42
#define FISH_ANI_WALKING_LEFT	43
#define FISH_ANI_ATTACK			44

#define FISH_STATE_WALKING_RIGHT	1235
#define FISH_STATE_WALKING_LEFT	    1236
#define FISH_STATE_ATTACK			1237
#define FISH_STATE_JUMP			1238
#define FISH_STATE_FLY_RIGHT			1239
#define FISH_STATE_FLY_LEFT		1240

#define FISH_WALKING_SPEED		0.05f
#define FISH_FLY_SPEED			0.4f
#define FISH_GRAVITY			0.002f
class Fishmen :
    public CGameObject
{
private:
	float originalX;
	float originalY;
	bool isfly;
	FireBall* fire;
	Simon* simon;
	bool isattacking;
	DWORD attack_start;
public:
	Fishmen(float X, float Y, FireBall *fire, Simon* simon);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void StartAttack();
};

