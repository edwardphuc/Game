#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Game.h"
#include "Brazier.h"
#define WHIP_STATE_ACTIVE 4000
#define WHIP_STATE_UNACTIVE 4100
#define WHIP 8


//BBOX
#define WHIP_F1_BBOX_WIDTH			18
#define WHIP_F1_BBOX_HEIGHT			53
#define WHIP_F2_BBOX_WIDTH			34
#define WHIP_F2_BBOX_HEIGHT			36
#define WHIP_F3_BBOX_WIDTH			50
#define WHIP_F3_BBOX_HEIGHT			14

class Whip : public CGameObject
{
	DWORD attack_start;
	bool isactive;
	Simon* simon;
	vector<LPGAMEOBJECT> oj;
public:
	Whip(Simon *sm, vector<LPGAMEOBJECT> oj);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void StartAttack();
	bool Getactivestate() { return this->isactive; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

