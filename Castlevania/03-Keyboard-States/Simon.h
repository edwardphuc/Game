#pragma once
#pragma once
#include "GameObject.h"
#include "Brazier.h"
#define SIMON_WALKING_SPEED		0.15f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_GRAVITY			0.002f
#define PULL_UP_SITTING			18.0f
#define PULL_UP_JUMPING			5.0f
#define GROUND					240.0f
#define AIR						170.0f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_SIT				400
#define SIMON_STATE_ATTACK			500

#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1
#define SIMON_ANI_WALKING_RIGHT		2
#define SIMON_ANI_WALKING_LEFT		3
#define SIMON_ANI_SIT				4
#define SIMON_ANI_ATTACK			5
#define SIMON_ANI_JUMP				6


//BBox
#define SIMON_STAND_BBOX_WIDTH		55
#define SIMON_STAND_BBOX_HEIGHT		60
#define SIMON_SIT_BBOX_WIDTH		56
#define SIMON_SIT_BBOX_HEIGHT		42

class Simon : public CGameObject
{
private:
	bool issitting = false;
	bool isattacking = false;
	bool isjumping = false;
	DWORD waitingtime = 0;
	DWORD attacktime = 0;
public:
	Simon();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	//void GetState(int x) { x = this->state; }
	DWORD Getwaitingtime() { return this->waitingtime;}
	bool Getsittingstate() { return this->issitting; }
	bool Getattackingstate() { return this->isattacking; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

