#include "Bat.h"

Bat::Bat()
{
	this->SetState(BAT_STATE_FLY_LEFT);
	hp = 1;
	ybackup = y;
	vy = BAT_FLYING_SPEED_Y;
}
void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (y - ybackup >= 20)
	{
		vy = -BAT_FLYING_SPEED_Y;
	}
	else if (y - ybackup <= -20)
	{
		vy = BAT_FLYING_SPEED_Y;
	}
	x += dx;
	y += dy;
}
void Bat::Render()
{

	int ani;
	if (visible == true)
	{
		if (vx < 0)
		{
			ani = BAT_ANI_FLY_LEFT;
			animations[ani]->Render(x, y, alpha, scale);
			RenderBoundingBox();
		}
	}
}
void Bat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}
void Bat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	
	case BAT_STATE_FLY_LEFT:
		vx = -BAT_FLYING_SPEED_X;
		nx = -1;
		scale = -1;
		break;
	}
}