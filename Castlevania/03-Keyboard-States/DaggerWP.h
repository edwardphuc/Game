#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Dagger.h"

#define DAGGERWP_ANI 36;
class DaggerWP :public CGameObject
{
	DWORD attack_start;
	bool isactive;
	Simon* simon;
	bool isallow = true;
	bool isfree = false;
	bool isallowdirect = true;
public:
	DaggerWP(Simon* sm, vector<LPGAMEOBJECT> oj);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT> enemy, int& countGhost);
	void Render();
	void SetState(int state);
	void StartAttack();
	bool Getallow() { return this->isallow; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

