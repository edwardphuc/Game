#include "Boss.h"

Boss::Boss()
{
	hp = 25;
	this->SetState(BOSS_STATE_SLEEP);
}
void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}
void Boss::Render()
{
	int ani;
	if (issleep == true) ani = BOSS_ANI_SLEEP;
	animations[ani]->Render(x, y, alpha, scale);
	RenderBoundingBox();
}
void Boss::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOSS_STATE_SLEEP:
		vx = 0;
		issleep = true;
		break;
	case BOSS_STATE_WAKE:
		break;
	}
}
void Boss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BOSS_BBOX_WIDTH;
	bottom = y + BOSS_BBOX_HEIGHT;
}
