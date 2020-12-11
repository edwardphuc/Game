#include "DaggerWP.h"
#include <algorithm>

DaggerWP::DaggerWP(Simon* sm, vector<LPGAMEOBJECT> oj)
{
	this->simon = sm;
	
	state = DAGGER_STATE_UNACTIVE;
	scale = 1;
}
void DaggerWP::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT> enemy, int& countGhost)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (isactive == true)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}
	float x1, y1;
	int z;
	simon->GetPosition(x1, y1);
	simon->GetDirect(z);
	if (GetTickCount() - attack_start > SIMON_ATTACK_TIME)
	{
		this->attack_start = 0;
		isactive = false;
	}
	if (isactive != false)
	{
		if (z == 1)
		{

			
			if (GetTickCount() - attack_start > 240 )
			{
				this->SetPosition(x1 + 60, y1 + 15);
				isfree = true;
			}

		}
		else if (z == -1)
		{

			if (GetTickCount() - attack_start > 240)
			{
				this->SetPosition(x1 - 45, y1 + 15);
				isfree = true;
			}
		}
	}
	else if (isactive == false && isfree == false)
	{
		this->SetPosition(x1, y1);
	}
	else if (isfree == true && isactive == false)
	{
		if (z == 1 && isallowdirect == true)
		{
			x += 0.5 * dt;
		}
		else if (z == -1 && isallowdirect == true) x += -0.5 * dt;
	}

	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy[i]->GetInvisible() == true)
			if (this->CheckCollision(enemy[i]))
			{
				this->isallow = true;
				this->isallowdirect = true;
				enemy[i]->SetHP(enemy[i]->GetHP() - 1);
				if (enemy[i]->GetHP() == false)
				{
					countGhost--;
					enemy.erase(enemy.begin() + i);
					this->isactive = false;
					this->isfree = false;
				}
			}
	}
}
void DaggerWP::StartAttack()
{
	this->attack_start = GetTickCount();
	isactive = true;
	isallow = false;
	animations[36]->reset();
}
void DaggerWP::Render()
{
	int ani;
	if (isactive == true || isfree == true)
	{
		int z;
		simon->GetDirect(z);
		if (z == 1)
		{
			scale = 1;
		}
		else scale = -1;
		ani = DAGGERWP_ANI;
		animations[ani]->Render(x, y, scale);
		RenderBoundingBox();
	}

}
void DaggerWP::SetState(int state)
{
	CGameObject::SetState(state);
	int z;
	switch (state)
	{
	case DAGGER_STATE_ACTIVE:
		break;
	case DAGGER_STATE_UNACTIVE:
		isactive = false;
		break;
	}
}
void DaggerWP::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + BBOX_DAGGER_WIDTH;
	bottom = top + BBOX_DAGGER_HEIGHT;
}