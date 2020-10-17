#pragma once
#include "GameObject.h"
#include "Simon.h"
#define WHIP_STATE_ACTIVE 1100
#define WHIP_STATE_UNACTIVE 1200
#define WHIP 8

class Whip : public CGameObject
{
	DWORD attack_start;
	bool isactive;
	Simon* simon;
public:
	Whip();
	Whip(Simon *sm);
	void Update(DWORD dt);
	void Render();
	void setstate(int state);
	bool Getactivestate() { return this->isactive; }
};

