#include "Ghost.h"
Ghost::Ghost()
{
	
}
void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
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
	x = x + dx;
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