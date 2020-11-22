#pragma once
#include "GameObject.h"
#define GRAVITY   0.000025f
#define ANI_UPGRADE	19

#define BBOX_UPGRADE_WIDTH   31
#define BBOX_UPGRADE_HEIGHT  32

class WhipUpgrade : public CGameObject
{
private:
	bool isactive;
public:
	WhipUpgrade();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Setstate(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

