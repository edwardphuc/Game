#include "Whip.h"

Whip::Whip(Simon *sm)
{
	this->simon = sm;
	state = WHIP_STATE_UNACTIVE;
	scale = 1;
	isactive = false;
}

void Whip::Update(DWORD dt)
{

	int stt = simon->GetState();
	float x, y;
	int z;
	simon->GetPosition(x, y);
	simon->GetDirect(z);
	attack_start = GetTickCount();
	if (stt != SIMON_STATE_ATTACK)
	{
		CGameObject::SetPosition(x, y);
		attack_start = 0;
		state = WHIP_STATE_UNACTIVE;
	}
	if (stt == SIMON_STATE_ATTACK)
	{
		//int frame = animations[8]->GetCurrentFrame();
		unsigned int t1 = animations[8]->GetFrame(0)->GetTime();
		unsigned int t2 = animations[8]->GetFrame(1)->GetTime() + t1;
		unsigned int t3 = animations[8]->GetFrame(2)->GetTime() + t2;
		if (z == 1)
		{
			switch (animations[8]->GetCurrentFrame())
			{
			case 0:
				if (GetTickCount() - attack_start <= t1)
				{
					CGameObject::SetPosition(x - 13, y + 13);
				}
				break;
			case 1:
				if (GetTickCount() - attack_start <= t2)
				{
					CGameObject::SetPosition(x - 13, y + 13);
				}
				break;
			case 2:
				if (GetTickCount() - attack_start <= t3)
				{
					CGameObject::SetPosition(x + 60, y + 15);
				}
				break;
			}
		}

		else
		{
			switch (animations[8]->GetCurrentFrame())
			{
			case 0:
				if (GetTickCount() - attack_start <= t1)
				{
					CGameObject::SetPosition(x + 30, y + 13);
				}
				break;
			case 1:
				if (GetTickCount() - attack_start <= t2)
				{
					CGameObject::SetPosition(x + 30, y + 13);
				}
				break;
			case 2:
				if (GetTickCount() - attack_start <= t3)
				{
					CGameObject::SetPosition(x - 40, y + 15);
				}
				break;
			}
		}
	}
}
void Whip::Render()
{
	int ani1;
	ani1 = WHIP;
	if (state == WHIP_STATE_ACTIVE)
	{
		int z;
		simon->GetDirect(z);
		if (z == 1)
		{
			scale = 1;
		}
		else scale = -1;
		animations[ani1]->Render(x, y, scale);
	}

}
void Whip::setstate(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WHIP_STATE_ACTIVE:
		isactive = true;
		break;
	case WHIP_STATE_UNACTIVE:
		break;
	}
}

