#include "Brick.h"

void Brick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}
void Brick::Render()
{

	RenderBoundingBox();
}
void Brick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + BBOX_BRICK_WIDTH;
	bottom = top + BBOX_BRICK_HEIGHT;
}
