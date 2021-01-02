#pragma once
#include "GameObject.h"
#include "Simon.h"

#define FIRE_ANI_ATTACK		45
#define FIRE_SPEED			0.2f

#define BBOX_FIRE_WIDTH		14
#define BBOX_FIRE_HEIGHT	10
class FireBall :public CGameObject
{
private: 
	bool isactive;
	bool isfree;
	Simon* simon;
public:
	FireBall(Simon* simon);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Setstate(int state);
	bool Getactive() { return this->isactive; }
	bool Getfree() { return this->isfree; }
	void Setactive(bool active) {
		this->isactive = active;
	}
	void Setfree(bool free) { this->isfree = free; }
	void StartAttack() { isactive = true; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

