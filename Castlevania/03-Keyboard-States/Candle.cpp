#include "Candle.h"
Candle::Candle()
{
	hp = 1;
}
void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}
void Candle::Render()
{
	int ani;
	if (visible == true)
	{
		ani = ANI_CANDLE;
		animations[ani]->Render(x, y, alpha, 1);
		RenderBoundingBox();
	}

}
void Candle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CANDLE_BBOX_WIDTH;
	bottom = y + CANDLE_BBOX_HEIGHT;
}

