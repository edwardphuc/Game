#include "Whip.h"
#include <algorithm>
#include "Brazier.h"
#include <iostream>
using namespace std;
Whip::Whip(Simon *sm, vector<LPGAMEOBJECT> oj)
{
	this->simon = sm;
	lv = 1;
	for (int i = 0; i < oj.size(); i++)
	{
		if ((i >= 48 && i <= 57))
		{
			this->oj.push_back(oj[i]);
		}
	}
	state = WHIP_STATE_UNACTIVE;
	scale = 1;
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT> enemy, int &countGhost)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (isactive == true)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}
	int stt = simon->GetState();
	float x1, y1;
	int z;
	int wp;
	this->simon->GetWhiplv(wp);
	lv = wp;
	simon->GetPosition(x1, y1);
	simon->GetDirect(z);
	if (GetTickCount() - attack_start > SIMON_ATTACK_TIME)
	{
			this->attack_start = 0;
			isactive = false;
	}
	if (isactive != false)
	{
		if (z == 1)
		{
			
			if (GetTickCount() - attack_start <= 120)
			{
				this->SetPosition(x1 - 13, y1 + 13);
			}
			else if (GetTickCount() -  attack_start <= 240)
			{
				this->SetPosition(x1 - 10, y1 + 10);
			}
			else if (GetTickCount() - attack_start <= 360)
			{
				this->SetPosition(x1 + 60, y1 + 15);
			}

		}
		else if (z == -1)
		{

			if (GetTickCount() - attack_start <= 120)
			{
				this->SetPosition(x1 + 35, y1 + 12);
			}
			else if (GetTickCount() - attack_start <= 240)
			{
				this->SetPosition(x1 + 30, y1 + 12);
			}
			else if (GetTickCount() - attack_start <= 360)
			{
				this->SetPosition(x1 - 45, y1 + 15);
			}
		}
	}
	else if(isactive == false)
	{
		this->SetPosition(x1, y1);
	}



	/*for (int i = 0; i < enemy.size(); i++)
	{
		this->enemy.push_back(enemy[i]);
	}*/
	
	for (int i = 0; i < this->oj.size(); i++)
	{
		if(this->oj[i]->GetHP() > 0)  // xet va cham cho cac vat the hien ra tren man hinh
			if (this->CheckCollision(this->oj[i]))
			{
				if (i >= 0 && i <= 4)
				{
					float x2, y2;
					this->oj[i]->GetPosition(x2, y2);           // danh vao den thi den mat, item hien ra
					this->oj[i + 5]->SetPosition(x2, y2);
					this->oj[i]->SetHP(this->oj[i]->GetHP() -1);
					if(this->oj[i]->GetHP() == 0) this->oj[i + 5]->SetVisible(true);
				}
			}
	}

	for (int i = 0; i < enemy.size(); i++)
	{
		if (enemy[i]->GetInvisible() == true)
			if (this->CheckCollision(enemy[i]))
			{
				enemy[i]->SetHP(enemy[i]->GetHP()-1);
				if (enemy[i]->GetHP() == false)
				{
					countGhost--;
					enemy.erase(enemy.begin() + i);
				}
			}
	}
	
	/*if(coEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny=0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Brazier*>(e->obj))
			{
				Brazier* brazier = dynamic_cast<Brazier*>(e->obj);

				
				if (brazier->GetState() != BRAZIER_STATE_UNACTIVE)
				{
					brazier->SetState(BRAZIER_STATE_UNACTIVE);
	
				}
			}
		}
		
	}*/
	
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Whip::StartAttack()
{
	this->attack_start = GetTickCount();
	isactive = true;
	animations[WHIP]->reset();
}
void Whip::Render()
{
	int ani1;
	if (isactive == true)
	{
		int z;
		simon->GetDirect(z);
		int wp;
		this->simon->GetWhiplv(wp);
		lv = wp;
		if (z == 1)
		{
			scale = 1;
		}
		else scale = -1;
		if (lv == 1)
		{
			ani1 = WHIP;
		}
		if (lv == 2)
		{
			ani1 = WHIP_LV2;
		}
		if (lv == 3)
		{
			ani1 = WHIP_LV3;
		}
		animations[ani1]->Render(x, y, scale);
		RenderBoundingBox();
	}
	
}
void Whip::SetState(int state)
{
	CGameObject::SetState(state);
	int z;
	switch (state)
	{
	case WHIP_STATE_ACTIVE:
		break;
	case WHIP_STATE_UNACTIVE:
		isactive = false;
		break;
	}
}
void Whip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isactive == true)
	{
		if (lv == 1)
		{
			int frame = animations[WHIP]->GetCurrentFrame();
			left = x;
			top = y;
			switch (frame)
			{
			case 0:
			{
				right = left + WHIP_F1_BBOX_WIDTH;
				bottom = top + WHIP_F1_BBOX_HEIGHT;
				break;
			}
			case 1:
			{
				right = left + WHIP_F2_BBOX_WIDTH;
				bottom = top + WHIP_F2_BBOX_HEIGHT;
				break;
			}
			case 2:
			{
				right = left + WHIP_F3_BBOX_WIDTH;
				bottom = top + WHIP_F3_BBOX_HEIGHT;
				break;
			}
			default:
				right = left;
				bottom = top;
				break;
			}
		}
		else if (lv == 2)
		{
			int frame = animations[WHIP_LV2]->GetCurrentFrame();
			left = x;
			top = y;
			switch (frame)
			{
			case 0:
			{
				right = left + WHIP_F1_BBOX_WIDTH;
				bottom = top + WHIP_F1_BBOX_HEIGHT;
				break;
			}
			case 1:
			{
				right = left + WHIP_LV2_F2_BBOX_WIDTH;
				bottom = top + WHIP_F2_BBOX_HEIGHT;
				break;
			}
			case 2:
			{
				right = left + WHIP_F3_BBOX_WIDTH;
				bottom = top + WHIP_F3_BBOX_HEIGHT;
				break;
			}
			default:
				right = left;
				bottom = top;
				break;
			}
		}
		if (lv == 3)
		{
			int frame = animations[WHIP_LV3]->GetCurrentFrame();
			left = x;
			top = y;
			switch (frame)
			{
			case 0:
			{
				right = left + WHIP_F1_BBOX_WIDTH;
				bottom = top + WHIP_F1_BBOX_HEIGHT;
				break;
			}
			case 1:
			{
				right = left + WHIP_LV2_F2_BBOX_WIDTH;
				bottom = top + WHIP_F2_BBOX_HEIGHT;
				break;
			}
			case 2:
			{
				right = left + WHIP_LV3_F3_BBOX_WIDTH;
				bottom = top + WHIP_F3_BBOX_HEIGHT;
				break;
			}
			default:
				right = left;
				bottom = top;
				break;
			}
		}

	}
}

