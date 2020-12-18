#include "Fishmen.h"

Fishmen::Fishmen()
{
	originalX = x;
	originalY = y;
	hp = 1;
}
void Fishmen::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}
void Fishmen::Render()
{

}
void Fishmen::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}
void Fishmen::SetState(int state)
{
}

