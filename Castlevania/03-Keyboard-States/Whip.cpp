#include "Whip.h"



void update()
{

}

void Whip::Render()
{
	int ani1;
	if (vx == 0) ani1 = WHIP;
	animations[ani1]->Render(x, y, 1);
	
	
	
}
void Whip::setstate(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WHIP_IDLE:
		vx = 0;
		vy = 0;
		break;
	}
}

