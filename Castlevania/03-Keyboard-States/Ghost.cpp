#include "Ghost.h"
#include "Brazier.h"
Ghost::Ghost()
{
	visible = true;
	hp = 4;
}
void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	x += dx;
	y += dy;
	if(coEvents.size() != 0)
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
	if (x < 1420 )
	{
		x = 1420;
		this->SetState(GHOST_STATE_WALKING_RIGHT);
	}
	else if (x > 4000 )
	{
		x = 4000;
		this->SetState(GHOST_STATE_WALKING_LEFT);
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Ghost::Render()
{
	int ani;
	if (visible == true)
	{
		if (vx != 0)
		{
			if (state == GHOST_STATE_WALKING_RIGHT) ani = GHOST_ANI_WALKING_RIGHT;
			else if (state == GHOST_STATE_WALKING_LEFT) ani = GHOST_ANI_WALKING_LEFT;
			animations[ani]->Render(x, y, scale);
			RenderBoundingBox();
		}
	}
}

void Ghost::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (visible == true)
	{
		left = x;
		top = y;
		right = left + GHOST_BBOX_WIDTH;
		bottom = top + GHOST_BBOX_HEIGHT;
	}

}
void Ghost::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	/*case GHOST_STATE_IDLE:
		vx = 0;
		nx = 1;
		scale = 1;
		break;*/
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