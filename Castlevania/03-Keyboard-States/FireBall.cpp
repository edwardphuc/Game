#include "FireBall.h"

FireBall::FireBall(Simon *simon)
{
	isactive = false;
	isfree = false;
	this->simon = simon;
}
void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (this->CheckCollision(this->simon))
	{
		this->simon->SetHP(this->simon->GetHP() - 1);
		this->isfree = false;
	}
	if (isactive == false && isfree == true)
	{
		if (nx > 0) vx = FIRE_SPEED;
		else if (nx < 0) vx = -FIRE_SPEED;
		x += dx;
	}
}
void FireBall::Render()
{
	int ani;
	if (isactive == true || isfree == true)
	{
		ani = FIRE_ANI_ATTACK;
		if (nx > 0) scale = 1;
		else if (nx < 0) scale = -1;
		animations[ani]->Render(x, y, alpha, scale);
		RenderBoundingBox();
	}
	
}
void FireBall::Setstate(int state)
{
	CGameObject::SetState(state);
}
void FireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + BBOX_FIRE_WIDTH;
	bottom = top + BBOX_FIRE_HEIGHT;
}