#include "Map.h"

void Map:: Render()
{
	int ani;
	ani = MAP;
	animations[ani]->Render(x, y, 0.95);
}	
void Map::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}
