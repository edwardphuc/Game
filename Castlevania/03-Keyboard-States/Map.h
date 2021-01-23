#pragma once
#include "GameObject.h"

#define MAP1		7
#define MAP2        10
#define MAP3		11
#define MAP4        12
#define MAP5		13
#define INTRO		53


class Map: public CGameObject
{
public:
	void Render();
	void render(int id);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

