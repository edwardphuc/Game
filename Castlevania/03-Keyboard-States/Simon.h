#pragma once
#pragma once
#include "GameObject.h"
#define SIMON_WALKING_SPEED		0.1f
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_GRAVITY			0.002f
#define PULL_UP_SITTING			18.0f
#define PULL_UP_JUMPING			5.0f
#define GROUND					100.0f
#define AIR						50.0f

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


class Simon : public CGameObject
{
private:
	bool issitting = false;
	bool isattacking = false;
	bool isjumping = false;
	DWORD waitingtime = 0;
public:

	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	DWORD Getwaitingtime() { return this->waitingtime;}
	bool Getsittingstate() { return this->issitting; }
};

