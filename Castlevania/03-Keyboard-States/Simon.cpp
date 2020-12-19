#include "Simon.h"
#include <algorithm>
#include "Ghost.h"
#include <iostream>

using namespace std;

Simon::Simon(vector<LPGAMEOBJECT> oj)
{
	isonstair = false;
	whiplv = 1;
	for (int i = 0; i < oj.size(); i++)
	{
		if (i >= 53 && i <= 57)
		{
			this->oj.push_back(oj[i]);
		}
	}
	state = SIMON_STATE_IDLE;
	soluongdao = 3;
	hp = 2;
}
void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT> stairoj, vector<LPGAMEOBJECT> enemy)
{
	CGameObject::Update(dt);
	// simple fall down
	/*if(isonStair == false)*/
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	for (int i = 0; i < stairoj.size(); i++)
	{
		float sx, sy;
		stairoj[i]->GetPosition(sx, sy);
		if (this->CheckCollision(stairoj[i]))
		{
			allowstair = 1;
			stairnx = 1;
			if (this->x > sx + 10 || this->y > sy + 20) allowstair = 0;
			if (nx > 0 && i == 1)
			{
				isonstair = false;
			}
		}
	}
	if (GetTickCount() - jump_start > SIMON_JUMP_TIME)
	{
		jump_start = 0;
	}
	else
	{
		if (GetTickCount() - jump_start < SIMON_JUMP_TIME)
		{
			if (waitingtime == 0) waitingtime = 1;
		}
	}
	if (GetTickCount() - attack_start > SIMON_ATTACK_TIME)
	{
		attack_start = 0;
		isattacking = false;
	}
	if (GetTickCount() - sitattack_start > SIMON_ATTACK_TIME)
	{
		sitattack_start = 0;
		issitattack = false;
	}
	if (GetTickCount() - changecolor_start > SIMON_EAT_TIME)
	{
		changecolor_start = 0;
		ischangecolor = false;

	}
	if (GetTickCount() - damaged_start > SIMON_DAMAGED_TIME)
	{
		damaged_start = 0;
		isdamaged = false;
	}
    else
	{
		if (GetTickCount() - damaged_start < (SIMON_DAMAGED_TIME / 2))
		{
			if (nx > 0)
			{
				vx = -0.05f;
			}
			else { vx = 0.05f; }
			dx = vx * dt;
			x += dx;
			vy = -0.05f;
			y += dy;

		}
		else if (GetTickCount() - damaged_start >= 250)
		{
			dx = vx * dt;
			x += dx;
			if (y >= 235 && this->GetState() != SIMON_STATE_DIE)
			{
				SetState(SIMON_STATE_IDLE);
			}
		}
	}
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		isuntouchable = false;
		alpha = 255;
	}
	else
	{
		if (GetTickCount() - untouchable_start < SIMON_UNTOUCHABLE_TIME)
		{
			if (this->GetState() != SIMON_STATE_DIE)
				alpha = 150;
		}
	}
	if (this->GetHP() == 0)
	{
		this->SetState(SIMON_STATE_DIE);
		this->StartDieTime();
	}
	if ((this->GetHP() <= 0) && (GetTickCount() - dietime_start > SIMON_DIE_TIME))
	{

	}
	else if ((this->GetHP() <= 0) && (GetTickCount() - dietime_start < SIMON_DIE_TIME))
	{
		alpha = 255;
		waitingtimeatt = 1;
		this->SetVisible(true);
	}
	if (isonstair == false)
	{
		vy = vy + SIMON_GRAVITY * dt;
		


		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// block 
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;
			waitingtime = 0;






			/*for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<Ghost *>(e->obj))
				{

					this->StartIsDamaged();
				}
			}*/

		}
	}
	else if (isonstair == true)
	{
		x += dx * 0.5;
		y += dy * 1.52;
	}

	

	for (int i = 0; i < this->oj.size(); i++)
	{
		if (this->oj[i]->GetInvisible() == true)  // xet va cham cho cac vat the hien ra tren man hinh
			if (this->CheckCollision(this->oj[i]))
			{
				if (i >= 0 && i <= 4)
				{
					this->oj[i]->SetVisible(false);
					this->StartChangeColor();
					if (i == 1) // dao
					{
						soluongdao++;
					}
				}
				if (i == 2 || i == 4)
				{
					whiplv++;
				}
			}
	}
	
	for (int i = 0; i < enemy.size(); i++)
	{
		float x1, y1;
		enemy[i]->GetPosition(x1, y1);
		if (abs(this->y - y1) <= 50)
		if (enemy[i]->GetInvisible() == true)
		{
			if (this->CheckCollision(enemy[i]))
			{
				int z;
				enemy[i]->GetDirect(z);
				if (this->GetUntouchable() == false)
				{
					if (z > 0)
					{
						nx = -1;
					}
					else if (z < 0)
					{
						nx = 1;
					}
					this->StartIsDamaged();
					this->StartUntouchable();
					this->SetHP(this->GetHP() - 1);
				}
				
				
			}
		}
	}
	
	
	/*if ((y >= AIR && y <= GROUND))
	{
		waitingtime = 1;
		
	}
	if (y > GROUND)
	{
		waitingtime = 0;
	}*/
	if (y > 258 && issitting == false)
	{
		y = 240.0f;
	}
	// simple screen edge collision!!!

	if (vx < 0 && x > 1280 && x < 1420)
	{
		x = 1450;
	}
	else if (x > 1280 && x < 1420)
	{
		x = 1440;
		y = -60; vy = 0.02f;
	}
	if (x > 4000 && x < 4050 && vx > 0 && y <=82)
	{
		x = 4050;
		y = 78;
	}
	else if (x > 4000 && x < 4050 )
	{
		x = 4050;
	}
	if (x > 3990 && y >= 240 && x < 4050)
	{
		x = 3980;
	}
	if (vx != 0 && (x < 1280 || x >= 1420 || x >= 4050)) x += dx;


	if (vx < 0 && x < 0) x = 0;
	if (issitting == true)
	{
		y = y - 2;
	}
	/*if (animations[SIMON_ANI_ATTACK]->GetCurrentFrame() == 0)
	{
		waitingtimeatt = 1;
		movingallow = true;
	}
	if (animations[SIMON_ANI_ATTACK]->GetCurrentFrame() == 2)
	{
		isattacking = false;
		waitingtimeatt = 0;
		movingallow = false;
		animations[SIMON_ANI_ATTACK]->reset();
	}*/
	
	
	/*if (autowalking != 0)
	{
		vx = 0;
		vy = 0;
		if (nx > 0)
		{
			x += SIMON_AUTO_WALKING_STAIR_SPEED;
			if (isOnStair)
			{
				y += -SIMON_AUTO_WALKING_STAIR_SPEED;
			}
		}
		else if (nx < 0)
		{
			x -= SIMON_AUTO_WALKING_STAIR_SPEED;
			if (isOnStair)
			{
				y += -SIMON_AUTO_WALKING_STAIR_SPEED;
			}
		}
	}*/
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::Render()
{
	int ani;
	if (this->GetInvisible() == true)
	{
		if (isdied == true) {
			ani = SIMON_ANI_DIE;
			if (GetTickCount() - dietime_start < SIMON_DIE_TIME / 2)
			{
				animations[ani]->GetFrame(0)->GetSprite()->Draw(x, y, alpha, scale);
			}
			else if (GetTickCount() - dietime_start > SIMON_DIE_TIME / 2 && GetTickCount() - dietime_start < SIMON_DIE_TIME)
			{
				animations[ani]->GetFrame(1)->GetSprite()->Draw(x, y, alpha, scale);
			}
			
		}
		else {
			if (isdamaged == true)
			{
				if (nx > 0) ani = SIMON_ANI_DAMAGED_RIGHT;
				else if (nx < 0) ani = SIMON_ANI_DAMAGED_LEFT;
			}
			else if (vx == 0)
			{
				if (ischangecolor == true)
				{
					if (nx > 0)
					{
						ani = SIMON_ANI_EAT_RIGHT;
						scale = 1;
					}
					if (nx < 0)
					{
						ani = SIMON_ANI_EAT_LEFT;
						scale = -1;
					}
				}
				else if (issitting == true)
				{
					if (issitattack == true)
					{
						ani = SIMON_ANI_SIT_ATTACK;
					}
					else
					{
						ani = SIMON_ANI_SIT;
						issitting = false;
					}
				}
				else if (isjumping == true)
				{
					ani = SIMON_ANI_JUMP;
					isjumping = false;
				}
				else if (isattacking == true)
				{
					ani = SIMON_ANI_ATTACK;
				}
				else if (isonstair == true)
				{
					if (stairnx == 1)
					{
						if (nx > 0) ani = SIMON_ANI_UP_STAIR_IDLE_RIGHT;
						if (nx < 0)
						{
							ani = SIMON_ANI_DOWN_STAIR_IDLE_LEFT;
							scale = -1;
						}
					}
					else if (stairnx == -1)
					{
						if (nx > 0) ani = SIMON_ANI_DOWN_STAIR_IDLE_RIGHT;
						if (nx < 0)
						{
							ani = SIMON_ANI_UP_STAIR_IDLE_LEFT;
							scale = 1;
						}
					}
				}
				else if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
				else ani = SIMON_ANI_IDLE_LEFT;

			}
			else if (vx > 0)
			{
				if (isonstair == false) ani = SIMON_ANI_WALKING_RIGHT;
				else if (isonstair == true)
				{
					if (stairnx == 1)  ani = SIMON_ANI_WALKING_UP_STAIR_RIGHT;
					else if (stairnx == -1) ani = SIMON_ANI_WALKING_DOWN_STAIR_RIGHT;
				}
			}

			else if (vx < 0)
			{
				if (isonstair == false) ani = SIMON_ANI_WALKING_LEFT;
				else if (isonstair == true)
				{
					if (stairnx == -1) ani = SIMON_ANI_WALKING_UP_STAIR_LEFT;
					else if (stairnx == 1) ani = SIMON_ANI_WALKING_DOWN_STAIR_LEFT;
				}
			}
			animations[ani]->Render(x, y, alpha, scale);
			RenderBoundingBox();
		}
		
	}
	
	
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		scale = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		scale = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_SIT:
		issitting = true;
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_ATTACK:
		vx = 0;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_ONSTAIR_IDLE:
		vx = 0;
		vy = 0;
		break;
	case SIMON_STATE_WALKING_UP_STAIR_RIGHT:
		vx = SIMON_WALKING_STAIR_SPEED;
		vy = -SIMON_WALKING_STAIR_SPEED;
		nx = 1;
		scale = 1;
		break;
	case SIMON_STATE_WALKING_UP_STAIR_LEFT:
		vx = -SIMON_WALKING_STAIR_SPEED;
		vy = -SIMON_WALKING_STAIR_SPEED;
		nx = -1;
		scale = -1;
		break;
	case SIMON_STATE_WALKING_DOWN_STAIR_RIGHT:
		vx = SIMON_WALKING_STAIR_SPEED;
		vy = SIMON_WALKING_STAIR_SPEED;
		nx = 1;
		scale = 1;
		break;
	case SIMON_STATE_WALKING_DOWN_STAIR_LEFT:
		vx = -SIMON_WALKING_STAIR_SPEED;
		vy = SIMON_WALKING_STAIR_SPEED;
		nx = -1;
		scale = -1;
		break;
	}
}
void Simon::StartAttack()
{
	isattacking = true;
	attack_start = GetTickCount();
	animations[SIMON_ANI_ATTACK]->reset();
}
void Simon::StartSitAttack()
{
	issitattack = true;
	sitattack_start = GetTickCount();
	animations[SIMON_ANI_SIT_ATTACK]->reset();
}
void Simon::FixPositionStair()
{

}
void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (this->GetState() == SIMON_STATE_SIT)
	{
		right = x + SIMON_SIT_BBOX_WIDTH;
		bottom = y + SIMON_SIT_BBOX_HEIGHT;

	}
	/*else if (isdied == true)
	{
		right = x + 54;
		bottom = y + 44;
	}*/
	else
	{
		right = x + SIMON_STAND_BBOX_WIDTH;
		bottom = y + SIMON_STAND_BBOX_HEIGHT;
	}
}

