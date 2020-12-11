#pragma once
#include "GameObject.h"
#include "Simon.h"

#define PANTHER_RUN_SPEED	0.02f
#define PANTHER_ANI_SIT		22
#define PANTHER_ANI_IDLE	23
#define PANTHER_ANI_RUN_RIGHT	24
#define PANTHER_ANI_RUN_LEFT	25

#define PANTHER_STATE_SIT	5000
#define PANTHER_STATE_IDLE	5001
#define PANTHER_STATE_RUN_RIGHT 5002
#define PANTHER_STATE_RUN_LEFT	5003
class Panther: public CGameObject
{
private:
	bool issitting;
	bool runtosimon = false;
	Simon* simon;
public:
	Panther(Simon *sm);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void StandUp();
	void RuntoSimon();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

