#include "StairOj.h"
StairOj::StairOj()
{
	visible = false;
}
void StairOj::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}
void StairOj::Render()
{
	RenderBoundingBox();
}

void StairOj::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + STAIR_BBOX_WIDTH;
	bottom = top + STAIR_BBOX_HEIGHT;
}
