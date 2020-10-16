#pragma once
#include "GameObject.h"

#define WHIP 8

#define WHIP_IDLE 1100
class Whip : public CGameObject
{
public:
	void Render();
	void setstate(int state);
};

