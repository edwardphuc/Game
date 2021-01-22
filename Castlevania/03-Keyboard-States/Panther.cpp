#include "Panther.h"
#include <algorithm>
#include "debug.h"

Panther::Panther(Simon *sm)
{
	this->simon = sm;
	this->SetState(PANTHER_STATE_SIT);
	visible = true;
	hp = 1;
	allowjump = true;
}
void Panther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (x >= 3880)
	{
		this->SetVisible(false);
	}
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	
	if (coEvents.size() == 0)
	{
		y += dy;
		vy = vy + 0.0002f * dt;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;
		
		
	}
	float x1, y1;
	simon->GetPosition(x1, y1);
	if (x - x1 > 300 && x - x1 < 360 && y1 < 300)
	{
		this->StandUp();
	}
	else if (x - x1 < 300 && isrunparabol == false && y1 < 300)
	{
		runtosimon = true;
	}
	if (runtosimon == true)
	{
		this->RuntoSimon();
	}
	if (id == 0)
	{
		if (x <= 2600 && y <= 265)
		{
			isrunparabol = true;
			this->RunParabol();
		}
		if (y > 265)
		{
			allowjump = true;
			isrunparabol = false;
			SetState(PANTHER_STATE_RUN_RIGHT);
			x += dx;
		}
	}
	if (id == 1)
	{
		if (x <= 2720 && y <= 160)
		{
			isrunparabol = true;
			this->RunParabol();
		}
		if (y > 160)
		{
			allowjump = true;
			isrunparabol = false;
			SetState(PANTHER_STATE_RUN_RIGHT);
			x += dx;
		}
	}
	if (id == 2)
	{
		if (x <= 3000  && y <= 265)
		{
			isrunparabol = true;
			this->RunParabolForLastPanther();
		}
		if (y > 265)
		{
			allowjump = true;
			isrunparabol = false;
			SetState(PANTHER_STATE_RUN_RIGHT);
			x += dx;
		}
	}
	
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Panther::StandUp()
{
	SetState(PANTHER_STATE_IDLE);
}
void Panther::RuntoSimon()
{
	SetState(PANTHER_STATE_RUN_LEFT);
	x += dx;
}
void Panther::RunParabol()
{
	runtosimon = false;
	if (y < 170 && y >= 80 && allowjump == true)
	{
		vy = -0.15f;
		allowjump = false;
	}
	else if (y < 80) vy = 0.08f;
	vx = -0.175f;
	x += dx;
	y += dy;
}
void Panther::RunParabolForLastPanther()
{
	runtosimon = false;
	if (y < 170 && y >= 157 && allowjump == true)
	{
		vy = -0.15f;
		allowjump = false;
	}
	else if (y < 157) vy = 0.08f;
	vx = -0.175f;
	x += dx;
	y += dy;
}
void Panther::Render()
{
	int ani;
	int direct = this->GetState();
	if (visible == true)
	{
		if (direct == PANTHER_STATE_RUN_RIGHT) ani = PANTHER_ANI_RUN_RIGHT;
		else if(direct == PANTHER_STATE_RUN_LEFT) ani = PANTHER_ANI_RUN_LEFT;
		else if (direct == PANTHER_STATE_SIT) ani = PANTHER_ANI_SIT;
		else ani = PANTHER_ANI_IDLE;
		animations[ani]->Render(x, y, alpha, scale);
		RenderBoundingBox();
	}
	
}

void Panther::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + PANTHER_BBOX_WIDTH;
	bottom = top + PANTHER_BBOX_HEIGHT;

}
void Panther::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PANTHER_STATE_SIT:
		vx = 0;
		nx = -1;
		scale = -1;
		break;
	case PANTHER_STATE_IDLE:
		vx = 0;
		nx = -1;
		scale = -1;
		break;
	case PANTHER_STATE_RUN_RIGHT:
		vx = PANTHER_RUN_SPEED;
		nx = 1;
		scale = 1;
		break;
	case PANTHER_STATE_RUN_LEFT:
		vx = -PANTHER_RUN_SPEED;
		nx = -1;
		scale = -1;
		break;
	}

}