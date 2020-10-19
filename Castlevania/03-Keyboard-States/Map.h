#pragma once
#include "GameObject.h"

#define MAP		7
class Map: public CGameObject
{
public:
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

