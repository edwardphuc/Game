#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Game.h"
#include "Brazier.h"

#define WHIP_STATE_ACTIVE 4000
#define WHIP_STATE_UNACTIVE 4100
#define WHIP 8
#define WHIP_LV2 20
#define WHIP_LV3 21


//BBOX
#define WHIP_F1_BBOX_WIDTH			18
#define WHIP_F1_BBOX_HEIGHT			49
#define WHIP_F2_BBOX_WIDTH			30
#define WHIP_F2_BBOX_HEIGHT			37
#define WHIP_F3_BBOX_WIDTH			47
#define WHIP_F3_BBOX_HEIGHT			14

#define WHIP_LV2_F2_BBOX_WIDTH		33
#define WHIP_LV3_F3_BBOX_WIDTH		80

class Whip : public CGameObject
{
	DWORD attack_start;
	bool isactive;
	Simon* simon;
	vector<LPGAMEOBJECT> oj;
	int lv;
public:
	Whip(Simon *sm, vector<LPGAMEOBJECT> oj);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT> enemy, int &countGhost, int &countBat);
	void Render();
	void SetState(int state);
	void StartAttack();
	bool Getactivestate() { return this->isactive; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

