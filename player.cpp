#include "framework.h"
#include "player.h"
#include"obstacle.h"

C_player::C_player()
{
	
	pt = { 200, 200 }; // 이것들 저장어떻게 하지 ..
	prevPt = pt;
	collider = new C_collider(pt, { 20,20 });
	playerSpeed = 5;
	playerDashSpeed = 30;
	DashDelay = 34;
	DashTime = 34;

	playerDoubleJump = false;

	DashCount = 0;
	isLeft = false;
}

C_player::~C_player()
{
}

HRESULT C_player::init()
{
	return S_OK;
}

void C_player::release()
{
}

void C_player::update()
{
	playerMove();
	playerJump();
	playerDash();
	if (DashDelay > DashTime /2) Gravity();
	isLand();
	isClogged();
	collider->setPos(pt);
	ptUpdate();
	ani = ANIMATION->findAnimation(unitName + unitFoward + unitState);
}

void C_player::render()
{
	RECT rec = RectMakeCenter(pt, 20, 20);
	Rectangle(getMemDC(), rec.left, rec.top, rec.right, rec.bottom);
	
	
	IMAGE->findImage(unitName)->aniRender(getMemDC(), pt.x - IMAGE->findImage(unitName)->getFrameWidth()/2, pt.y - IMAGE->findImage(unitName)->getFrameHeight()/2, ani);
}

void C_player::playerMove()
{
	if (DashDelay >= DashTime/2)
	{
		bool goLeft = InputManager->isStayKeyDown(VK_LEFT);
		bool goRight = InputManager->isStayKeyDown(VK_RIGHT);
		if (InputManager->isOnceKeyDown(VK_LEFT)) ANIMATION->start(unitName + "LeftMove");
		
		if (InputManager->isOnceKeyDown(VK_RIGHT)) ANIMATION->start(unitName + "RightMove");
		
		if (goLeft && !goRight)
		{
			pt = vector2(pt.x - playerSpeed, pt.y);
			isLeft = true;
			unitFoward = "Left";
			unitState = "Move";
		}
		if (goRight && !goLeft)
		{
			pt = vector2(pt.x + playerSpeed, pt.y);
			isLeft = false;
			unitFoward = "Right";
			unitState = "Move";
		}
		if (!goLeft && !goRight && !isJump)
		{
			unitState = "Idle";
		}
	}
}

void C_player::playerJump()
{
	bool goJump = InputManager->isOnceKeyDown('C');
	if (!isJump) playerDoubleJump = true;
	if (goJump && !isJump )
	{
		jumpPower = 25;
	}
	else if (goJump && playerDoubleJump && isJump)
	{
		jumpPower = 25;
		playerDoubleJump = false;
	}
	if (jumpPower > 10) unitState = "Jump";
	if (jumpPower == 10 || DashDelay == DashTime / 2)
	{
		ANIMATION->start(unitName + "RightFall");
		ANIMATION->start(unitName + "LeftFall");
	}
	if ( isJump  && jumpPower <= 10 && DashDelay > DashTime / 2)  unitState = "Fall";
}

void C_player::playerDash()
{
	bool goDash = InputManager->isOnceKeyDown('Z');
	
	if (goDash && DashDelay >= DashTime && !isDash)
	{
		jumpPower = 0;
		isDash = true;
		DashDelay = 0;
		DashFoward = isLeft;
		DashCount = 3;
	}

	else if (goDash && playerDoubleDash && DashDelay <= DashTime / 2)
	{
		playerDoubleDash = false;
		isDash = true;
		DashDelay = 0;
		DashCount = 3;
	}

	if (DashCount > 0)
	{
		DashCount--;
		if (DashFoward)
		{
			pt.x -= playerDashSpeed;
			unitState = "Dash";
		}

		else if (!DashFoward)
		{
			pt.x += playerDashSpeed;
			unitState = "Dash";
		}
	}

	DashDelay++;
	if (DashDelay >= DashTime)
	{
		DashDelay = DashTime;
		playerDoubleDash = true;
		isDash = false;
	}
}
