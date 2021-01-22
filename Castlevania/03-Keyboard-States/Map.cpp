#include "Map.h"

void Map:: Render()
{
}	
void Map::render(int id)
{
	int ani;
	if (id == 1000)
	{
		ani = MAP1;
		animations[ani]->Render(x, y, alpha, 0.95);
	}
	else if (id == 1001)
	{
		ani = MAP2;
		animations[ani]->Render(x, y, alpha, 0.85);
	}
	else if (id == 1002)
	{
		ani = MAP3;
		animations[ani]->Render(x, y, alpha, 0.85);
	}
	else if (id == 1003)
	{
		ani = MAP4;
		animations[ani]->Render(x, y, alpha, 0.85);
	}
	else if (id == 1004)
	{
		ani = MAP5;
		animations[ani]->Render(x, y, alpha, 1);
	}
	else if (id == 1005)
	{
		ani = INTRO;
		animations[ani]->Render(x, y, alpha, 1.25);
	}
}
void Map::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}
