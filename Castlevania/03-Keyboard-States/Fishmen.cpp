#include "Fishmen.h"
#include "Brick.h"
Fishmen::Fishmen(float X, float Y, FireBall *fire, Simon* simon)
{
	x = X;
	y = Y;
	originalX = x;
	originalY = y;
	hp = 12;
	vy = -FISH_FLY_SPEED;
	isfly = true;
	isattacking = false;
	this->fire = fire;
	this->simon = simon;
}
void Fishmen::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;


	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Brick*>(e->obj)) 
			{
				if(isfly != false)
				{
					y += dy;
				}
				if (isfly == false)
				{
					x += dx;
					vx = -vx;
				}
			}
			if (dynamic_cast<Fishmen*>(e->obj))
			{
				x += dx;
			}
		}
	}
	
	if (isfly == false)
	{
		vy = vy + FISH_GRAVITY * dt;
		float x1, y1;
		this->simon->GetPosition(x1, y1);
		if (this->fire->Getactive() == false  && this->fire->Getfree() == false)
		{
			this->fire->SetPosition(x, y);
			this->fire->SetDirect(nx);
		}
		else if (this->fire->Getactive() == true && this->fire->Getfree() == false)
		{
			if (nx > 0)
			{
				this->fire->SetPosition(x + 40, y + 25);
			}
			if (nx < 0)
			{
				this->fire->SetPosition(x - 15, y + 25);
			}
		}
		int z;
		this->simon->GetDirect(z);
		
		if (abs(x - x1) <= 100 && isattacking == false && this->fire->Getfree() == false)
		{
			if ((z < 0 && nx > 0 && x > x1) || (z > 0 && nx < 0 && x < x1))
			{
				this->SetState(FISH_STATE_ATTACK);
				this->StartAttack();
				this->fire->StartAttack();
			}
			
		}
		if (GetTickCount() - attack_start > FISH_ATTACK_TIME)
		{
			attack_start = 0;
			isattacking = false;
			if (nx > 0)
			{
				this->SetState(FISH_STATE_WALKING_RIGHT);
			}
			else if (nx < 0)
			{
				this->SetState(FISH_STATE_WALKING_LEFT);
			}
			this->fire->Setfree(true);
			this->fire->Setactive(false);
		}
		if (abs(x - originalX) >= 50)
		{
			if (vx > 0)
			{
				this->SetState(FISH_STATE_WALKING_LEFT);
			}
			else if (vx < 0)
			{
				this->SetState(FISH_STATE_WALKING_RIGHT);
			}

		}
	}

	if (originalY - y > 200) isfly = false;
	
	/*if (vx < 0 && x < 5645)
	{
		this->SetState(FISH_STATE_WALKING_RIGHT);
	}*/
	
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Fishmen::StartAttack()
{
	isattacking = true;
	attack_start = GetTickCount();
}
void Fishmen::Render()
{
	int ani;
	if (visible == true)
	{
		if (isattacking == true) ani = FISH_ANI_ATTACK;
		else if (vx > 0) ani = FISH_ANI_WALKING_RIGHT;
		else if (vx < 0) ani = FISH_ANI_WALKING_LEFT;
		else ani = FISH_ANI_IDLE;
		animations[ani]->Render(x, y, alpha, scale);
		RenderBoundingBox();
	}
}
void Fishmen::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 30;
	bottom = y + 70;
}
void Fishmen::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FISH_STATE_WALKING_RIGHT:
		vx = FISH_WALKING_SPEED;
		nx = 1;
		scale = 1;
		break;
	case FISH_STATE_WALKING_LEFT:
		vx = -FISH_WALKING_SPEED;
		nx = -1;
		scale = -1;
		break;
	case FISH_STATE_FLY_RIGHT:
		vy = -FISH_FLY_SPEED;
		nx = 1;
		scale = 1;
		break;
	case FISH_STATE_FLY_LEFT:
		vy = -FISH_FLY_SPEED;
		nx = -1;
		scale = -1;
		break;
	case FISH_STATE_ATTACK:
		vx = 0;
		break;
	}
}

