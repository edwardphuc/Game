#include "Panther.h"
#include <algorithm>

Panther::Panther(Simon *sm)
{
	state = PANTHER_STATE_SIT;
	this->simon = sm;
	visible = true;
	hp = 1;
}
void Panther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vy = vy + 0.0002f * dt;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		y += dy;
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
	if (x - x1 > 300 && x - x1 < 360)
	{
		this->StandUp();
	}
	else if (x - x1 < 300)
	{
		runtosimon = true;
	}
	if (runtosimon == true)
	{
		this->RuntoSimon();
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Panther::StandUp()
{
	this->SetState(PANTHER_STATE_IDLE);
}
void Panther::RuntoSimon()
{
	this->SetState(PANTHER_STATE_RUN_LEFT);
	x += dx;
}
void Panther::Render()
{
	int ani;
	if (visible == true)
	{
		if (state == PANTHER_STATE_RUN_RIGHT) ani = PANTHER_ANI_RUN_RIGHT;
		else if(state == PANTHER_STATE_RUN_LEFT) ani = PANTHER_ANI_RUN_LEFT;
		else if (state == PANTHER_STATE_SIT) ani = PANTHER_ANI_SIT;
		else ani = PANTHER_ANI_IDLE;
	}
	animations[ani]->Render(x, y, scale);
	RenderBoundingBox();
}

void Panther::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (state == PANTHER_STATE_SIT)
	{
		right = x + 60;
		bottom = y + 30;
	}
	else
	{
		right = x + 60;
		bottom = y + 30;
	}

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