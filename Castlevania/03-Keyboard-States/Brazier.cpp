#include "Brazier.h"
void Brazier::Render()
{
	int ani;
	ani = BRAZIER;
	animations[ani]->Render(x, y, 1);
}