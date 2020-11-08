#include "Whip.h"
#include <algorithm>
#include "Brazier.h"

Whip::Whip(Simon *sm)
{
	this->simon = sm;
	state = WHIP_STATE_UNACTIVE;
	scale = 1;
	isactive = false;
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (state == WHIP_STATE_ACTIVE)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}
	
	int stt = simon->GetState();
	float x, y;
	int z;
	simon->GetPosition(x, y);
	simon->GetDirect(z);
	attack_start = GetTickCount();

	if (stt == SIMON_STATE_ATTACK)
	{
		int frame = animations[8]->GetCurrentFrame();
		unsigned int t1 = animations[8]->GetFrame(0)->GetTime();
		unsigned int t2 = animations[8]->GetFrame(1)->GetTime() + t1;
		unsigned int t3 = animations[8]->GetFrame(2)->GetTime() + t2;
		if (z == 1)
		{
			switch (frame)
			{
			case 0:
				if (GetTickCount() - attack_start <= t1)
				{
					CGameObject::SetPosition(x - 13, y + 13);
				}
				break;
			case 1:
				if (GetTickCount() - attack_start <= t2)
				{
					CGameObject::SetPosition(x - 13, y + 13);
				}
				break;
			case 2:
				if (GetTickCount() - attack_start <= t3)
				{
					CGameObject::SetPosition(x + 60, y + 15);
				}
				animations[8]->reset();
				break;
			}
		}

		else
		{
			switch (animations[8]->GetCurrentFrame())
			{
			case 0:
				if (GetTickCount() - attack_start <= t1)
				{
					CGameObject::SetPosition(x + 30, y + 10);
				}
				break;
			case 1:
				if (GetTickCount() - attack_start <= t2)
				{
					CGameObject::SetPosition(x + 30, y + 10);
				}
				break;
			case 2:
				if (GetTickCount() - attack_start <= t3)
				{
					CGameObject::SetPosition(x - 40, y + 15);
				}
				animations[8]->reset();
				break;
			}
		}
		
	}
	else
	{
		SetPosition(x, y);
		attack_start = 0;
		state = WHIP_STATE_UNACTIVE;
	}
	
	if(coEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny=0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Brazier*>(e->obj)) // if e->obj is Goomba 
			{
				Brazier* brazier = dynamic_cast<Brazier*>(e->obj);

				if (brazier->GetState() != BRAZIER_STATE_UNACTIVE)
				{
					brazier->SetState(BRAZIER_STATE_UNACTIVE);
					//simon->SetPosition(0, 0);
				}
			}
		}
		
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Whip::Render()
{
	int ani1;
	ani1 = WHIP;
	if (state == WHIP_STATE_ACTIVE)
	{
		int z;
		simon->GetDirect(z);
		if (z == 1)
		{
			scale = 1;
		}
		else scale = -1;
		animations[ani1]->Render(x, y, scale);
	}
	RenderBoundingBox();
}
void Whip::SetState(int state)
{
	CGameObject::SetState(state);
	int z;
	simon->GetDirect(z);
	switch (state)
	{
	case WHIP_STATE_ACTIVE:
		isactive = true;
		break;
	case WHIP_STATE_UNACTIVE:
		isactive = false;
		break;
	}
}
void Whip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == WHIP_STATE_ACTIVE)
	{
		int frame = animations[WHIP]->GetCurrentFrame();
		left = x;
		top = y;
		switch (frame)
		{
		case 0:
		{
			right = left - WHIP_F1_BBOX_WIDTH;
			bottom = top + WHIP_F1_BBOX_HEIGHT;
			break;
		}
		case 1:
		{
			right = left + WHIP_F2_BBOX_WIDTH;
			bottom = top + WHIP_F2_BBOX_HEIGHT;
			break;
		}
		case 2:
		{
			right = left + WHIP_F3_BBOX_WIDTH;
			bottom = top + WHIP_F3_BBOX_HEIGHT;
			break;
		}
		default:
			right = left;
			bottom = top;
			break;
		}

	}
}

