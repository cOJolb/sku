#include "framework.h"
#include "player.h"
#include"obstacle.h"

C_player::C_player()
{
	
	pt = { 200, 200 }; // 이것들 저장어떻게 하지 ..
	prevPt = pt;
	collider = new C_collider(pt, { 20,20 });
	playerSpeed = 5;

	playerDashInfo.playerDashSpeed = 8;
	playerDashInfo.DashDelay = 34;
	playerDashInfo.DashTime = 34;
	playerDashInfo.DashCount = 0;
	playerDashInfo.DashTerm = 10;

	playerJumpPower = 20;
	playerDoubleJump = false;
	playerDashJump = false;
	DashJumpCount = 0;
	
	isLeft = false;
}

C_player::~C_player()
{
}

HRESULT C_player::init(vector2 _pt)
{
	pt = _pt;
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
	playerDash_Jump();
	//Jump();
	
	if (playerDashInfo.DashDelay >= playerDashInfo.DashTime / 2 ) Gravity();
	

	isLand();
	isClogged();
	collider->setPos(pt);
	ptUpdate();
	ani = ANIMATION->findAnimation(unitImageInfo.unitName + unitImageInfo.unitFoward + unitImageInfo.unitState);
	PLAYERDATA->savePlayerData(pt, collider);
}

void C_player::render()
{
	RECT rec = RectMakeCenter(pt, 20, 20);
	Rectangle(getMemDC(), rec.left, rec.top, rec.right, rec.bottom);
	
	IMAGE->findImage(unitImageInfo.unitName)->aniRender(getMemDC(), pt.x - IMAGE->findImage(unitImageInfo.unitName)->getFrameWidth()/2, pt.y - IMAGE->findImage(unitImageInfo.unitName)->getFrameHeight()/2, ani);
}

void C_player::playerMove()
{
	if (playerDashInfo.DashDelay >= playerDashInfo.DashTime/2)
	{
		bool goLeft = InputManager->isStayKeyDown(VK_LEFT);
		bool goRight = InputManager->isStayKeyDown(VK_RIGHT);
		if (InputManager->isOnceKeyDown(VK_LEFT)) ANIMATION->start(unitImageInfo.unitName + "LeftMove");
		
		if (InputManager->isOnceKeyDown(VK_RIGHT)) ANIMATION->start(unitImageInfo.unitName + "RightMove");
		
		if (goLeft && !goRight)
		{
			pt = vector2(pt.x - playerSpeed, pt.y);
			isLeft = true;
			unitImageInfo.unitFoward = "Left";
			unitImageInfo.unitState = "Move";
		}
		if (goRight && !goLeft)
		{
			pt = vector2(pt.x + playerSpeed, pt.y);
			isLeft = false;
			unitImageInfo.unitFoward = "Right";
			unitImageInfo.unitState = "Move";
		}
		if (!goLeft && !goRight && !isJump)
		{
			unitImageInfo.unitState = "Idle";
		}
	}
}

void C_player::playerJump()
{
	bool goJump = InputManager->isOnceKeyDown('C');
	if (!isJump) playerDoubleJump = true;
	if (goJump && !isJump)
	{
		playerDashJump = true;
		jumpPower = playerJumpPower;
	}
	else if (goJump && playerDoubleJump && isJump)
	{
		playerDashJump = true;
		jumpPower = playerJumpPower;
		playerDoubleJump = false;
	}
	if (jumpPower > 10) unitImageInfo.unitState = "Jump";
	if (jumpPower == 10 || playerDashInfo.DashDelay == playerDashInfo.DashTime / 2)
	{
		ANIMATION->start(unitImageInfo.unitName + "RightFall");
		ANIMATION->start(unitImageInfo.unitName + "LeftFall");
	}
	if ( isJump  && jumpPower <= 10 && playerDashInfo.DashDelay > playerDashInfo.DashTime / 2)  unitImageInfo.unitState = "Fall";
}

void C_player::playerDash()
{
	bool goDash = InputManager->isOnceKeyDown('Z');
	if (goDash && playerDashInfo.DashDelay >= playerDashInfo.DashTime && !playerDashInfo.isDash)
	{
		playerDashJump = false;
		jumpPower = 0;
		playerDashInfo.isDash = true;
		playerDashInfo.DashDelay = 0;
		playerDashInfo.DashFoward = isLeft;
		playerDashInfo.DashCount = playerDashInfo.DashTerm;
		ANIMATION->start(unitImageInfo.unitName + "RightDash");
		ANIMATION->start(unitImageInfo.unitName + "LeftDash");
	}

	else if (goDash && playerDashInfo.playerDoubleDash && playerDashInfo.DashDelay <= playerDashInfo.DashTime / 2)
	{
		playerDashJump = false;
		playerDashInfo.playerDoubleDash = false;
		playerDashInfo.isDash = true;
		playerDashInfo.DashDelay = 0;
		playerDashInfo.DashCount = playerDashInfo.DashTerm;
		ANIMATION->start(unitImageInfo.unitName + "RightDash");
		ANIMATION->start(unitImageInfo.unitName + "LeftDash");
	}

	playerDashMove();

	playerDashInfo.DashDelay++;
	if (playerDashInfo.DashDelay >= playerDashInfo.DashTime)
	{
		playerDashInfo.DashDelay = playerDashInfo.DashTime;
		playerDashInfo.playerDoubleDash = true;
		playerDashInfo.isDash = false;
	}
}

void C_player::playerDashMove()
{
	if (playerDashInfo.DashCount > 0 && !playerDashJump)
	{
		playerDashInfo.DashCount--;
		if (playerDashInfo.DashFoward)
		{
			pt.x -= playerDashInfo.playerDashSpeed;
			unitImageInfo.unitState = "Dash";

		}

		else if (!playerDashInfo.DashFoward)
		{
			pt.x += playerDashInfo.playerDashSpeed;
			unitImageInfo.unitState = "Dash";
		}
	}
}

void C_player::playerDash_Jump()
{
	if (playerDashInfo.DashDelay < playerDashInfo.DashTime / 2 && playerDashJump)
	{
		Gravity();
		playerDashInfo.DashCount = 0;
		//playerDashInfo.DashDelay = 0;
		DashJumpCount++;

		if (playerDashInfo.DashFoward)
		{
			pt.x -= playerDashInfo.playerDashSpeed;
			unitImageInfo.unitState = "Jump";
		}

		else if (!playerDashInfo.DashFoward)
		{
			pt.x += playerDashInfo.playerDashSpeed;
			unitImageInfo.unitState = "Jump";
		}

		if (DashJumpCount >= 10)
		{
			DashJumpCount = 0;
			playerDashJump = false;
			playerDashInfo.DashDelay = playerDashInfo.DashTime / 2;
		}
	}
}



void C_player::playerAtk()
{
	bool goAtk = InputManager->isOnceKeyDown('X');
	if (goAtk)
	{

	}
}

void C_player::playerSkillA()
{
}

void C_player::playerSkillS()
{
}
