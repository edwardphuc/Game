#include "Simon.h"
#include <algorithm>
#include "Brazier.h"
#include <iostream>
using namespace std;

Simon::Simon()
{
	state = SIMON_STATE_IDLE;
}
void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	// simple fall down
	vy = vy + SIMON_GRAVITY * dt;

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
		//for (UINT i = 0; i < coEventsResult.size(); i++)
		//{
		//	LPCOLLISIONEVENT e = coEventsResult[i];

		//	if (dynamic_cast<Brazier*>(e->obj)) // if e->obj is Goomba 
		//	{
		//		Brazier* brazier = dynamic_cast<Brazier*>(e->obj);
		//		// jump on top >> kill Goomba and deflect a bit 
		//		if (e->ny > 0)
		//		{
		//			x += dx;
		//			y += dy;
		//		}
		//		else if (e->nx != 0)
		//		{
		//			x += dx;
		//			y += dy;
		//		}
		//	}
		//}
		
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

	if (vx > 0 && x > 1280 && x < 1420) x = 1420;
	if (x > 1280 && x < 1420) x = 1440;
	if (x > 4000 && x < 4050) x = 4050;
	if (vx != 0 && (x < 1280 || x >= 1420 || x >= 4050)) x += dx;


	if (vx < 0 && x < 0) x = 0;
	/*if (issitting == true)
	{
		y = y + PULL_UP_SITTING;
	}*/
	

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::Render()
{
	int ani;
	if (vx == 0)
	{
		if (issitting == true)
		{
			ani = SIMON_ANI_SIT;
			issitting = false;
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
		else if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
		else ani = SIMON_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = SIMON_ANI_WALKING_RIGHT;

	else ani = SIMON_ANI_WALKING_LEFT;
	
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
		isattacking = true;
		vx = 0;
		vy = 0;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	}
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

