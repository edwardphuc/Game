#include "Brazier.h"
Brazier::Brazier()
{
	state = BRAZIER_STATE_ACTIVE;
	
}
void Brazier::Render()
{
	int ani;
	if (state == BRAZIER_STATE_ACTIVE)
	{
		ani = BRAZIER;
		animations[ani]->Render(x, y, 1);
	}
	
	RenderBoundingBox();
}
void Brazier::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BRAZIER_BBOX_WIDTH;
	bottom = y + BRAZIER_BBOX_HEIGHT;
}

void Brazier::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRAZIER_STATE_ACTIVE:
		isappearing = true;
		break;
	case BRAZIER_STATE_UNACTIVE:
		isappearing = false;
		break;
	}
}
