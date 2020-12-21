#include "Fishmen.h"

Fishmen::Fishmen(float X, float Y)
{
	x = X;
	y = Y;
	originalX = x;
	originalY = y;
	hp = 1;
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
		vy = vy + 0.0002f * dt;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;


	}
}
void Fishmen::Render()
{

}
void Fishmen::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
void Fishmen::SetState(int state)
{
	/*CGameObject::SetState(state);
	switch (state)
	{
	case FISH_STATE_WALKING_RIGHT:
		vx = GHOST_WALKING_SPEED;
		nx = 1;
		scale = 1;
		break;
	case FISH_STATE_WALKING_LEFT:
		vx = -GHOST_WALKING_SPEED;
		nx = -1;
		scale = -1;
		break;
	}*/
}

