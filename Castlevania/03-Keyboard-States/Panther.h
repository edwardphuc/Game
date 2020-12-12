#pragma once
#include "GameObject.h"
#include "Simon.h"

#define PANTHER_RUN_SPEED	0.08f

#define PANTHER_ANI_SIT		22
#define PANTHER_ANI_IDLE	23
#define PANTHER_ANI_RUN_RIGHT	24
#define PANTHER_ANI_RUN_LEFT	25

#define PANTHER_STATE_SIT	6000
#define PANTHER_STATE_IDLE	6001
#define PANTHER_STATE_RUN_RIGHT 6002
#define PANTHER_STATE_RUN_LEFT	6003
class Panther: public CGameObject
{
private:
	bool issitting;
	bool runtosimon = false;
	bool allowjump;
	bool isrunparabol = false;
	Simon* simon;
public:
	Panther(Simon *sm);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT> stairoj);
	void Render();
	void SetState(int state);
	void StandUp();
	void RuntoSimon();
	void RunParabol();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

