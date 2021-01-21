#include "AxeWP.h"
#include "Ghost.h"
#include "Bat.h"
#include "Fishmen.h"
#include "Sound.h"

AxeWP::AxeWP(Simon* sm, vector<LPGAMEOBJECT> oj)
{
	this->simon = sm;

	state = AXE_STATE_UNACTIVE;
	isactive = false;
}
void AxeWP::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT> enemy, int& countGhost, int& countBat, int& countFish)
{
	CGameObject::Update(dt);
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


			if (GetTickCount() - attack_start <= 120)
			{
				this->SetPosition(x1 - 10, y1 + 15);
			}
			else if (GetTickCount() - attack_start <= 240)
			{
				this->SetPosition(x1 - 5, y1 + 15);
			}
			else if (GetTickCount() - attack_start <= 360)
			{
				this->SetPosition(x1 + 55, y1 - 10);
				isfree = true;
			}

		}
		else if (z == -1)
		{

			if (GetTickCount() - attack_start <= 120)
			{
				this->SetPosition(x1 +35, y1 + 15);
			}
			else if (GetTickCount() - attack_start <= 240)
			{
				this->SetPosition(x1 +30, y1 + 15);
			}
			else if (GetTickCount() - attack_start <= 360)
			{
				this->SetPosition(x1 -2, y1 + 10);
				isfree = true;
			}
		}
		nx = z;
		
	}
	else if ((isactive == false && isfree == false))
	{
		this->SetPosition(x1, y1);
		nx = z;
	}
	else if (isfree == true && isactive == false)
	{
		vy += AXE_GRAVITY * dt;
		y += dy;
		x += dx;
	}
	if (y> 305)
	{
		this->SetPosition(x1, y1);
		this->isallow = true;
		this->isfree = false;
		this->isactive = false;
	}

	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy[i]->GetInvisible() == true && this->isfree == true)
			if (this->CheckCollision(enemy[i]))
			{
				this->isallow = true;
				/*this->isallowdirect = true;*/
				enemy[i]->SetHP(enemy[i]->GetHP() - 1);
				if (enemy[i]->GetHP() <= 0)
				{
					if (enemy[i]->GetState() == GHOST_STATE_WALKING_LEFT || enemy[i]->GetState() == GHOST_STATE_WALKING_RIGHT) countGhost--;
					if (enemy[i]->GetState() == BAT_STATE_FLY_LEFT) countBat--;
					if (enemy[i]->GetState() == FISH_STATE_WALKING_LEFT || enemy[i]->GetState() == FISH_STATE_WALKING_RIGHT) countFish--;
					enemy.erase(enemy.begin() + i);

				}
				this->isactive = false;
				this->isfree = false;
				Sound::getInstance()->play("hit", false, 1);
			}
	}
}

void AxeWP::Render()
{
	int ani;
	if (isactive == true && isfree == false)
	{
		if (nx == 1)
		{
			scale = -1;
		}
		else scale = 1;
		ani = ANI_AXE_ACTIVE;
		animations[ani]->Render(x, y, alpha, scale);
		RenderBoundingBox();
	}
	else if (isactive == false && isfree == true)
	{
		if (nx == 1)
		{
			scale = -1;
		}
		else scale = 1;
		ani = ANI_AXE_ATTACK;
		animations[ani]->Render(x, y, alpha, scale);
		RenderBoundingBox();
	}
}
void AxeWP::StartAttack()
{
	this->attack_start = GetTickCount();
	isactive = true;
	isallow = false;
	vx = AXE_SPEED_X * nx;
	vy = -AXE_SPEED_Y;
	animations[48]->reset();
	animations[47]->reset();
	Sound::getInstance()->play("Axe", false, 1);
}
void AxeWP::SetState(int state)
{
	CGameObject::SetState(state);
	int z;
	switch (state)
	{
	case AXE_STATE_ACTIVE:
		break;
	case AXE_STATE_UNACTIVE:
		isactive = false;
		break;
	}
}
void AxeWP::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + AXE_BBOX_WIDTH;
	bottom = top + AXE_BBOX_HEIGHT;
}