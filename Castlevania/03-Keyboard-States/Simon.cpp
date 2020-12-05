#include "Simon.h"
#include <algorithm>
#include "Brazier.h"
#include <iostream>
using namespace std;

Simon::Simon(vector<LPGAMEOBJECT> oj)
{
	isonstair = false;
	whiplv = 1;
	for (int i = 0; i < oj.size(); i++)
	{
		if (i >= 53 && i <= 57)
		{
			this->oj.push_back(oj[i]);
		}
	}
	state = SIMON_STATE_IDLE;
}
void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT> stairoj)
{
	CGameObject::Update(dt);
	// simple fall down
	/*if(isonStair == false)*/
	/*for (int i = 0; i < stairoj.size(); i++)
	{
		if (this->CheckCollision(stairoj[i]))
		{
			if (i % 2 == 0)
			{
				this->isonstair = true;
			}
			else if (i % 2 != 0)
			{
				this->isonstair = false;
			}
		}
	}*/
	/*if (isonstair == false)
	{*/
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);


		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// block 
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;







			//Brazier
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<Brazier*>(e->obj))
				{

					if (e->ny != 0)
					{
						x += dx;
						y += dy;
					}
					else if (e->nx != 0)
					{
						x += dx;
						y += dy;
					}
				}
			}

		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	/*}*/
	/*else*/ if (isonstair == true)
	{
		x += dx;
		y += dy;
	}
	else vy = vy + SIMON_GRAVITY * dt;

	

	for (int i = 0; i < this->oj.size(); i++)
	{
		if (this->oj[i]->GetInvisible() == true)  // xet va cham cho cac vat the hien ra tren man hinh
			if (this->CheckCollision(this->oj[i]))
			{
				if (i >= 0 && i <= 4)
				{
					this->oj[i]->SetVisible(false);
				}
				if (i == 2 || i == 4)
				{
					whiplv++;
				}
			}
	}
	
	if ((y >= AIR && y <= GROUND))
	{
		waitingtime = 1;
		
	}
	if (y > GROUND)
	{
		waitingtime = 0;
	}
	if (y > 258 && issitting == false)
	{
		y = 240.0f;
	}
	// simple screen edge collision!!!

	if (vx > 0 && x > 1280 && x < 1420) x = 1450;
	if (x > 1280 && x < 1420) x = 1440;
	if (x > 4000 && x < 4050) x = 4050;
	if (vx != 0 && (x < 1280 || x >= 1420 || x >= 4050)) x += dx;


	if (vx < 0 && x < 0) x = 0;
	if (issitting == true)
	{
		y = y - 2;
	}
	/*if (animations[SIMON_ANI_ATTACK]->GetCurrentFrame() == 0)
	{
		waitingtimeatt = 1;
		movingallow = true;
	}
	if (animations[SIMON_ANI_ATTACK]->GetCurrentFrame() == 2)
	{
		isattacking = false;
		waitingtimeatt = 0;
		movingallow = false;
		animations[SIMON_ANI_ATTACK]->reset();
	}*/
	if (GetTickCount() - attack_start > SIMON_ATTACK_TIME)
	{
		attack_start = 0;
		isattacking = false;
	}
	if (GetTickCount() - sitattack_start > SIMON_ATTACK_TIME)
	{
		sitattack_start = 0;
		issitattack = false;
	}
	/*if (autowalking != 0)
	{
		vx = 0;
		vy = 0;
		if (nx > 0)
		{
			x += SIMON_AUTO_WALKING_STAIR_SPEED;
			if (isOnStair)
			{
				y += -SIMON_AUTO_WALKING_STAIR_SPEED;
			}
		}
		else if (nx < 0)
		{
			x -= SIMON_AUTO_WALKING_STAIR_SPEED;
			if (isOnStair)
			{
				y += -SIMON_AUTO_WALKING_STAIR_SPEED;
			}
		}
	}*/
	
}

void Simon::Render()
{
	int ani;
	if (vx == 0)
	{
		if (issitting == true)
		{
			if (issitattack == true)
			{
				ani = SIMON_ANI_SIT_ATTACK;
			}
			else
			{
				ani = SIMON_ANI_SIT;
				issitting = false;
			}
		}
		else if (isjumping == true)
		{
			ani = SIMON_ANI_JUMP;
			isjumping = false;
		}
		else if(isattacking == true)
		{
			ani = SIMON_ANI_ATTACK;
		}
		else if (isonstair == true)
		{
			if (stair == 1)
			{
				if(nx > 0) ani = SIMON_ANI_UP_STAIR_IDLE_RIGHT;
				if(nx < 0) ani = SIMON_ANI_UP_STAIR_IDLE_LEFT;
			}
			else if (stair == -1)
			{
				if (nx > 0) ani = SIMON_ANI_DOWN_STAIR_IDLE_RIGHT;
				if (nx < 0) ani = SIMON_ANI_DOWN_STAIR_IDLE_LEFT;
			}
		}
		else if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
		else ani = SIMON_ANI_IDLE_LEFT;
	
	}
	else if (vx > 0)
	{
		if(isonstair == false) ani = SIMON_ANI_WALKING_RIGHT;
		else if (isonstair == true)
		{
			if (stair == 1)
			{
				ani = SIMON_ANI_WALKING_UP_STAIR_RIGHT;
			}
			else if (stair == -1)
			{
				ani = SIMON_ANI_WALKING_DOWN_STAIR_RIGHT;
			}
		}
	}

	else if (vx < 0)
	{
		if (isonstair == false) ani = SIMON_ANI_WALKING_LEFT;
		else if (isonstair == true)
		{
			if (stair == 1)
			{
				ani = SIMON_ANI_WALKING_UP_STAIR_LEFT;
			}
			else if (stair == -1)
			{
				ani = SIMON_ANI_WALKING_DOWN_STAIR_LEFT;
			}
		}
	}

		
	
	animations[ani]->Render(x, y, scale);
	RenderBoundingBox();
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		scale = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		scale = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
		isjumping = true;
		break;
	case SIMON_STATE_SIT:
		issitting = true;
		vx = 0;
		break;
	case SIMON_STATE_ATTACK:
		vx = 0;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_ONSTAIR_IDLE:
		vx = 0;
		vy = 0;
		break;
	case SIMON_STATE_WALKING_UP_STAIR_RIGHT:
		vx = SIMON_WALKING_STAIR_SPEED;
		vy = -SIMON_WALKING_STAIR_SPEED;
		break;
	case SIMON_STATE_WALKING_UP_STAIR_LEFT:
		vx = -SIMON_WALKING_STAIR_SPEED;
		vy = -SIMON_WALKING_STAIR_SPEED;
		break;
	case SIMON_STATE_WALKING_DOWN_STAIR_RIGHT:
		vx = SIMON_WALKING_STAIR_SPEED;
		vy = SIMON_WALKING_STAIR_SPEED;
		break;
	case SIMON_STATE_WALKING_DOWN_STAIR_LEFT:
		vx = -SIMON_WALKING_STAIR_SPEED;
		vy = SIMON_WALKING_STAIR_SPEED;
		break;
	}
}
void Simon::StartAttack()
{
	isattacking = true;
	attack_start = GetTickCount();
	animations[SIMON_ANI_ATTACK]->reset();
}
void Simon::StartSitAttack()
{
	issitattack = true;
	sitattack_start = GetTickCount();
	animations[SIMON_ANI_SIT_ATTACK]->reset();
}
void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (state == SIMON_STATE_SIT)
	{
		right = x + SIMON_SIT_BBOX_WIDTH;
		bottom = y + SIMON_SIT_BBOX_HEIGHT;

	}
	else
	{
		right = x + SIMON_STAND_BBOX_WIDTH;
		bottom = y + SIMON_STAND_BBOX_HEIGHT;
	}
}

