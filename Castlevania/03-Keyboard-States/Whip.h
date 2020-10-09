#pragma once
#include "GameObject.h"
class Whip : public CGameObject
{
public:
	Whip();
	void update();
	void render();
	void setstate(int state) { this->state = state; }
};

