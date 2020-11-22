#include "Ghost.h"
#include "Brazier.h"
Ghost::Ghost()
{
	
}
void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
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

		for (UINT i = 0; i < coEventsResult.size(); i++)
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
		}
	}
	if (x < 0)
	{
		x = 10;
		vx = -vx;
		scale = 1;
	}
	if (x > 1280)
	{
		x = 1270;
		vx = -vx;
		scale = -1;
	}
	
}
void Ghost::Render()
{
	int ani;
	if (vx > 0) ani = GHOST_ANI_WALKING_RIGHT;
	else ani = GHOST_ANI_WALKING_LEFT;
	animations[ani]->Render(x, y, scale);
	//RenderBoundingBox();
}

void Ghost::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + GHOST_BBOX_WIDTH;
	bottom = top + GHOST_BBOX_HEIGHT;

}
void Ghost::Setstate(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GHOST_STATE_WALKING_RIGHT:
		vx = GHOST_WALKING_SPEED;
		nx = 1;
		scale = 1;
		break;
	case GHOST_STATE_WALKING_LEFT:
		vx = -GHOST_WALKING_SPEED;
		nx = -1;
		scale = -1;
		break;
	}

}