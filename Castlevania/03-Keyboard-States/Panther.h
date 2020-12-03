#pragma once
#include "GameObject.h"

#define PANTHER_RUN_SPEED	0.2f
#define PANTHER_ANI_SIT		22
#define PANTHER_ANI_IDLE	23
#define PANTHER_ANI_RUN_RIGHT	24
#define PANTHER_ANI_RUN_LEFT	25

#define PANTHER_STATE_SIT	4000
#define PANTHER_STATE_IDLE	4001
#define PANTHER_STATE_RUN_RIGHT	4002
#define PANTHER_STATE_RUN_LEFT	4003
class Panther: public CGameObject
{
private:
	bool issitting;
public:
	Panther();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

