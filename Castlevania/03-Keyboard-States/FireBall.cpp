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
	if (this->CheckCollision(this->simon) && (this->Getactive() == true || this->Getfree() == true))
	{
		if (this->simon->GetUntouchable() == false)
		{
			if (nx > 0)
			{
				this->simon->SetDirect(-1);
			}
			else if (nx < 0)
			{
				this->simon->SetDirect(1);
			}
			this->simon->StartIsDamaged();
			this->simon->StartUntouchable();
			this->simon->SetHP(this->simon->GetHP() - 1);
		}
		this->isfree = false;
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