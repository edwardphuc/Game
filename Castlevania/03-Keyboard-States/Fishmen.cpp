#include "Fishmen.h"
#include "Brick.h"
Fishmen::Fishmen(float X, float Y)
{
	x = X;
	y = Y;
	originalX = x;
	originalY = y;
	hp = 12;
	vy = -FISH_FLY_SPEED;
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
				if (isfly != true)
				{
					if (nx > 0)
					{
						state = FISH_STATE_WALKING_RIGHT;
					}
					else if (nx < 0)
					{
						state = FISH_STATE_WALKING_LEFT;
					}
				}
			}
		}
	}
	
	if (isfly == false)
	{
		vy = vy + FISH_GRAVITY * dt;
	}

	if (originalY - y > 200) isfly = false;
	if (abs(x - originalX) >= 150) vx = -vx;
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Fishmen::Render()
{
	int ani;
	if (visible == true)
	{
		if (vx > 0) ani = FISH_ANI_WALKING_RIGHT;
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
		vx = FISH_WALKING_SPEED;
		nx = -1;
		scale = -1;
		break;
	case FISH_STATE_FLY_RIGHT:
		isfly = true;
		vy = -FISH_FLY_SPEED;
		scale = 1;
		break;
	case FISH_STATE_FLY_LEFT:
		isfly = true;
		vy = -FISH_FLY_SPEED;
		scale = -1;
		break;
	}
}

