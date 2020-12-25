#include "Dagger.h"

Dagger::Dagger()
{
	visible = false;
	scale = 1.3;
	hp = 10;
}
void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy = vy + GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		y += dy;
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
void Dagger::Render()
{
	int ani;
	ani = ANI_DAGGER;
	if (visible == true)
	{
		animations[ani]->Render(x, y, alpha, scale);
		RenderBoundingBox();
	}
}
void Dagger::Setstate(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case DAGGER_STATE_ACTIVE:
		isactive = true;
		break;
	case DAGGER_STATE_UNACTIVE:
		isactive = false;
		break;
	}
}
void Dagger::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + BBOX_DAGGER_WIDTH;
	bottom = top + BBOX_DAGGER_HEIGHT;
}