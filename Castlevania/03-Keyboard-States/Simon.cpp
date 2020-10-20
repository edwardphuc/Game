#include "Simon.h"
#include <algorithm>
#include "Brazier.h"

Simon::Simon()
{
	state = SIMON_STATE_IDLE;
}
void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	// simple fall down
	vy = vy + SIMON_GRAVITY * dt;


		x += dx;
		y += dy;
		if (y < AIR)
		{
			waitingtime = 1;
		}
		if (y > GROUND)
		{
			vy = 0;
			y = GROUND;
			waitingtime = 0;
		}

		// simple screen edge collision!!!
		if (vx > 0 && x > 1280 && x < 1510) x = 1510;
		if (x > 1280 && x < 1510) x = 1510;
		if (vx > 0 && x >= 1510) x += dx;


		if (vx < 0 && x < 0) x = 0;
		if (issitting == true)
		{
			y = y + PULL_UP_SITTING;
		}
	
	
}

void Simon::Render()
{
	int ani;
	if (vx == 0)
	{
		if (issitting == true)
		{
			ani = SIMON_ANI_SIT;
			issitting = false;
		}
		else if (isjumping == true)
		{
			ani = SIMON_ANI_JUMP;
			isjumping = false;
		}
		else if(isattacking == true)
		{
			ani = SIMON_ANI_ATTACK;
			isattacking = false;
		}
		else if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
		else ani = SIMON_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = SIMON_ANI_WALKING_RIGHT;

	else ani = SIMON_ANI_WALKING_LEFT;
	
	animations[ani]->Render(x, y, scale);
	RenderBoundingBox();
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
			isjumping = true;
			break;
	case SIMON_STATE_SIT:
		issitting = true;
		vx = 0;
		break;
	case SIMON_STATE_ATTACK:
		isattacking = true;
		vx = 0;
		vy = 0;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	}
}

void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (state == SIMON_STATE_SIT)
	{
		right = x + SIMON_SIT_BBOX_WIDTH;
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
	}
	else
	{
		right = x + SIMON_STAND_BBOX_WIDTH;
		bottom = y + SIMON_STAND_BBOX_HEIGHT;
	}
}

