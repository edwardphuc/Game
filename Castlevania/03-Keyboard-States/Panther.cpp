#include "Panther.h"

#include "Ghost.h"
#include "Brazier.h"
Panther::Panther()
{
	state = PANTHER_STATE_SIT;
}
void Panther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	x += dx;
	y += dy;
	if (coEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		/*for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Brazier*>(e->obj) || dynamic_cast<Ghost*>(e->obj))
			{

				if (e->ny != 0)
				{
					x += dx;

				}
				else if (e->nx != 0)
				{
					x += dx;

				}
			}
		}*/
	}
	if (x < 1420)
	{
		x = 1420;
		vx = -vx;
		scale = 1;
	}
	if (x > 2200)
	{
		x = 2200;
		vx = -vx;
		scale = -1;
	}

}
void Panther::Render()
{
	int ani;
	if (visible == true)
	{
		if (vx > 0) ani = PANTHER_ANI_RUN_RIGHT;
		else if(vx < 0) ani = PANTHER_ANI_RUN_LEFT;
		else if (vx == 0)
		{
			if (issitting == true) ani = PANTHER_ANI_SIT;
			else ani = PANTHER_ANI_IDLE;
		}
		animations[ani]->Render(x, y, scale);
		RenderBoundingBox();
	}
}

void Panther::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (visible == true)
	{
		left = x;
		top = y;
		right = left + GHOST_BBOX_WIDTH;
		bottom = top + GHOST_BBOX_HEIGHT;
	}

}
void Panther::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PANTHER_STATE_SIT:
		issitting = true;
		vx = 0;
		vy = 0;
		nx = -1;
		scale = -1;
		break;
	case PANTHER_STATE_IDLE:
		vx = 0;
		nx = -1;
		scale = -1;
		break;
	case PANTHER_STATE_RUN_RIGHT:
		vx = PANTHER_RUN_SPEED;
		nx = 1;
		scale = 1;
		break;
	case PANTHER_STATE_RUN_LEFT:
		vx = -PANTHER_RUN_SPEED;
		nx = -1;
		scale = -1;
		break;
	}

}