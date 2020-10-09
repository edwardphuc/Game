#include "Simon.h"
D3DXMATRIX scale;

void Simon::Update(DWORD dt)
{
	CGameObject::Update(dt);

	// simple fall down
	vy = vy + SIMON_GRAVITY * dt;
	
	if (y > 100)
	{
		vy = 0;
		y = 100.0f;
		
	}
	
	// simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
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
		else if (isattacking == true)
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
			onground = false;
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
		onground = true;
		break;
	}
}

