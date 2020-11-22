#include "WhipUpgrade.h"
WhipUpgrade::WhipUpgrade()
{
	visible = false;
	scale = 1;
}
void WhipUpgrade::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
void WhipUpgrade::Render()
{
	int ani;
	ani = ANI_UPGRADE;
	if (visible == true)
	{
		animations[ani]->Render(x, y, scale);
	}
	RenderBoundingBox();
}
void WhipUpgrade::Setstate(int state)
{

}
void WhipUpgrade::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + BBOX_UPGRADE_WIDTH;
	bottom = top + BBOX_UPGRADE_HEIGHT;
}
