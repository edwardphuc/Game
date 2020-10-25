#include "Dagger.h"

Dagger::Dagger()
{
	isactive = false;
	scale = 1;
}
void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}
void Dagger::Render()
{
	int ani;
	ani = ANI_DAGGER;
	if (isactive == true)
	{
		animations[ani]->Render(x, y, scale);
	}
	RenderBoundingBox();
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