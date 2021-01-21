#include "Boss.h"

Boss::Boss(Simon *sm)
{
	this->simon = sm;
	hp = 12;
	isstarting = false;
	iscurving = false;
	isOP = false;
	allowstart = true;
	allowcurving = false;
	allowstraight = false;
	allowback = false;
	allowOP = false;
	this->SetState(BOSS_STATE_SLEEP);
}
void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (GetTickCount() - start_time > BOSS_START_TIME && isstarting == true)
	{
		start_time = 0;
		isstarting = false;
		allowcurving = true;
		originalX = x;
		originalY = y;
	}
	else if (GetTickCount() - start_time < BOSS_START_TIME)
	{
		vx = -0.1;
		vy = 0.1;
		x += dx;
		y += dy;
		allowstart = false;
	}
	if (GetTickCount() - curving_time > BOSS_CURVING_TIME && iscurving == true)
	{
		curving_time = 0;
		iscurving = false;
		allowstraight = true;
	}
	else if (GetTickCount() - curving_time < BOSS_CURVING_TIME)
	{
		if (nx > 0) vx = 0.3;
		else vx = -0.3;
		vy = 0.15;
		x += dx;
		y += dy;
		allowcurving = false;
	}
	if (GetTickCount() - back_time > BOSS_BACKING_TIME && isbacking == true)
	{
		back_time = 0;
		isbacking = false;
		allowOP = true;
	}
	else if (GetTickCount() - back_time < BOSS_BACKING_TIME)
	{
		if (nx > 0) vx = 0.3;
		else vx = -0.3;
		vy = -0.2;
		x += dx;
		y += dy;
		allowback = false;
	}
	if (GetTickCount() - OP_time > BOSS_OP_TIME && isOP == true)
	{
		OP_time = 0;
		isOP = false;
		StartWait();
	}
	else if (GetTickCount() - OP_time < BOSS_OP_TIME)
	{
		vx = -0.4;
		vy = 0.1;
		/*if (x < originalX || y < originalY)
		{
			vx = 0;
			vy = 0;
		}*/
		x += dx;
		y += dy;
		allowOP = false;
	}
	if (GetTickCount() - waitingtime > BOSS_WAITING_TIME && iswaiting == true)
	{
		waitingtime = 0;
		allowcurving = true;
		iswaiting = false;
	}
	else if (GetTickCount() - waitingtime < BOSS_WAITING_TIME)
	{
		vx = 0;
		vy = 0;
		/*if (x < originalX || y < originalY)
		{
			vx = 0;
			vy = 0;
		}*/
	}
	if (allowstraight == true)
	{
		vx = 0.2;
		x += dx;
	}
	if (x >= 6150)
	{
		allowstraight = false;
		allowback = true;
	}
	float x1, y1;
	this->simon->GetPosition(x1, y1);
	if (x1 > x) nx = 1;
	else nx = -1;
	if (x < x1 - 200 && allowstart == true)
	{
		Start();
		this->SetState(BOSS_STATE_WAKE);
		Sound::getInstance()->stop("backgroundmusic");
		Sound::getInstance()->play("backgroundmusic_boss", true, 0);
	}
	if (abs(x - x1) >= 100 && allowstart == false && allowcurving == true && allowstraight == false && allowback == false)
	{
		Startcurving();
	}
	if (allowstraight == false && allowcurving == false && allowstart == false && allowback == true)
	{
		Start_back();
	}
	if (allowstraight == false && allowcurving == false && allowstart == false && allowback == false && allowOP == true)
	{
		StartOP();
	}
	if (y > 300) y = 290;
}
void Boss::Render()
{
	int ani;
	if (visible == true)
	{
		if (issleep == true) ani = BOSS_ANI_SLEEP;
		else ani = BOSS_ANI_WAKE;
		animations[ani]->Render(x, y, alpha, scale);
		RenderBoundingBox();
	}
	
}
void Boss::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOSS_STATE_SLEEP:
		vx = 0;
		issleep = true;
		break;
	case BOSS_STATE_WAKE:
		issleep = false;
		break;
	}
}
void Boss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BOSS_STATE_WAKE)
	{
		left = x;
		top = y;
		right = left + BOSS_BBOX_WIDTH;
		bottom = top + BOSS_BBOX_HEIGHT;
	}
	else
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}
