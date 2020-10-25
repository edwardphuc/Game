#include "Heart.h"

Heart::Heart()
{
	isactive = false;
	scale = 1;
}
void Heart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}
void Heart::Render()
{
	int ani;
	ani = ANI_HEART;
	if (isactive == true)
	{
		animations[ani]->Render(x, y, scale);
	}
	RenderBoundingBox();
}
void Heart::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + BBOX_HEART_WIDTH;
	bottom = top + BBOX_HEART_HEIGHT;
}
void Heart::Setstate(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case HEART_STATE_ACTIVE:
		isactive = true;
		break;
	case HEART_STATE_UNACTIVE:
		isactive = false;
		break;
	}
}