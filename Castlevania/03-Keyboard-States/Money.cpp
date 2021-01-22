#include "Money.h"
Money::Money()
{
	visible = false;
	scale = 0.8;
	hp = 10;
}
void Money::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
void Money::Render()
{
	int ani;
	ani = ANI_MONEY;
	if (visible == true)
	{
		animations[ani]->Render(x, y, alpha, scale);
	}
	RenderBoundingBox();
}
void Money::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + BBOX_MONEY_WIDTH;
	bottom = top + BBOX_MONEY_HEIGHT;
}
void Money::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MONEY_STATE_ACTIVE:
		isactive = true;
		break;
	case MONEY_STATE_UNACTIVE:
		isactive = false;
		break;
	}
}