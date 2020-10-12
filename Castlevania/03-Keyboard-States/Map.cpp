#include "Map.h"

void Map:: Render()
{
	int ani;
	ani = MAP;
	animations[ani]->Render(x, y, 2.2);
}	
