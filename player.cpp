#include "framework.h"
#include "player.h"
#include"obstacle.h"
#include "littlebone.h"
#include"clown.h"
C_player::C_player()
{
	C_skul* CurSkul = new C_littlebone;
	C_skul* nextSkul = new C_clown;
	vskul.push_back(CurSkul);
	vskul.push_back(nextSkul);

	viskul = vskul.begin();
	skulInfo = (*viskul)->getskulInfo();
	setUnitImageInfo((*viskul)->getUnitName(), "Left", "Idle");

	pt = { 200, 200 }; // 이것들 저장어떻게 하지 ..
	prevPt = pt;
	collider = new C_collider(pt, skulInfo.playerSize);
	rc = RectMakeCenter(collider->getPos(), collider->getSize().x, collider->getSize().y);
	futureRc = RectMakeCenter(collider->getPos(), collider->getSize().x, collider->getSize().y);
	futureRcLTRB();

	DashCount = 0;
	isLeft = false;
	isDash = false;
	playerDoubleJump = false;
	playerDashJump = false;
	DashJumpCount = 0;
	DashDelay = 0;
	isAtk = false;
	atkCount = 0;
	
	//ANIMATION->start(unitImageInfo.unitName + "LeftIdle");
	//ANIMATION->start(unitImageInfo.unitName + unitImageInfo.unitFoward + unitImageInfo.unitState);
	//ani = ANIMATION->findAnimation(unitImageInfo.unitName + unitImageInfo.unitFoward + unitImageInfo.unitState);
}

C_player::~C_player()
{
}

HRESULT C_player::init()
{
	//pt = _pt;
	ANIMATION->start(unitImageInfo.unitName + "LeftIdle");
	ANIMATION->start(unitImageInfo.unitName + "RightIdle");
	return S_OK;
}

void C_player::release()
{
}

void C_player::update()
{
	
	changeSkul();
	playerMove();
	playerJump();
	playerDash();
	playerDash_Jump();
	//Jump();
	playerAtk();

	if (DashDelay >= skulInfo.DashTime / 2) Gravity();
	isLand();
	isClogged();
	//if (DashDelay >= skulInfo.DashTime / 2) Gravity();
	
	collider->setPos(pt);
	ptUpdate();
	ani = ANIMATION->findAnimation(unitImageInfo.unitName + unitImageInfo.unitFoward + unitImageInfo.unitState);
	PLAYERDATA->savePlayerData(pt, collider);
	rc = RectMakeCenter(collider->getPos(), collider->getSize().x, collider->getSize().y);
	
}

void C_player::render()
{
	RECT rec = RectMakeCenter(pt, 20, 20);
	Rectangle(getCVOSDC(), rec.left, rec.top, rec.right, rec.bottom);
	
	IMAGE->findImage(unitImageInfo.unitName)->aniRender(getCVOSDC(), pt.x - IMAGE->findImage(unitImageInfo.unitName)->getFrameWidth()/2, pt.y - IMAGE->findImage(unitImageInfo.unitName)->getFrameHeight()/2, ani);
}

void C_player::playerMove()
{
	if (DashDelay >= skulInfo.DashTime/2 && !isAtk)
	{
		bool goLeft = InputManager->isStayKeyDown(VK_LEFT);
		bool goRight = InputManager->isStayKeyDown(VK_RIGHT);
		if (InputManager->isOnceKeyDown(VK_LEFT)) ANIMATION->start(unitImageInfo.unitName + "LeftMove");
		
		if (InputManager->isOnceKeyDown(VK_RIGHT)) ANIMATION->start(unitImageInfo.unitName + "RightMove");
		
		if (goLeft && !goRight )
		{
			//pt = vector2(pt.x - skulInfo.playerSpeed, pt.y);
			movetoLeft(futureRc, skulInfo.playerSpeed);
			isLeft = true;
			unitImageInfo.unitFoward = "Left";
			unitImageInfo.unitState = "Move";
		}
		if (goRight && !goLeft )
		{
			//pt = vector2(pt.x + skulInfo.playerSpeed, pt.y);
			movetoRight(futureRc, skulInfo.playerSpeed);
			isLeft = false;
			unitImageInfo.unitFoward = "Right";
			unitImageInfo.unitState = "Move";
		}
		if (!goLeft && !goRight && !isJump && !isAtk)
		{
			unitImageInfo.unitState = "Idle";
		}
	}
}

void C_player::playerJump()
{
	bool goJump = InputManager->isOnceKeyDown('C');
	if (!isJump) playerDoubleJump = true;
	if (goJump && !isJump && !isAtk)
	{
		playerDashJump = true;
		jumpPower = skulInfo.playerJumpPower;
	}
	else if (goJump && playerDoubleJump && isJump && !isAtk)
	{
		playerDashJump = true;
		jumpPower = skulInfo.playerJumpPower;
		playerDoubleJump = false;
	}
	if (jumpPower > 10 && !isAtk) unitImageInfo.unitState = "Jump";
	if (jumpPower == 10 || DashDelay == skulInfo.DashTime / 2 && !isAtk)
	{
		ANIMATION->start(unitImageInfo.unitName + "RightFall");
		ANIMATION->start(unitImageInfo.unitName + "LeftFall");
	}
	if ( isJump  && jumpPower <= 10 && DashDelay > skulInfo.DashTime / 2 &&!isAtk)  unitImageInfo.unitState = "Fall";
}

void C_player::playerDash()
{
	bool goDash = InputManager->isOnceKeyDown('Z');
	if (goDash && DashDelay >= skulInfo.DashTime && !isDash && !isAtk)
	{
		playerDashJump = false;
		jumpPower = 0;
		isDash = true;
		DashDelay = 0;
		DashFoward = isLeft;
		DashCount = skulInfo.DashTerm;
		ANIMATION->start(unitImageInfo.unitName + "RightDash");
		ANIMATION->start(unitImageInfo.unitName + "LeftDash");
	}

	else if (goDash && playerDoubleDash && DashDelay <= skulInfo.DashTime / 2 &&!isAtk)
	{
		playerDashJump = false;
		playerDoubleDash = false;
		isDash = true;
		DashDelay = 0;
		DashCount = skulInfo.DashTerm;
		ANIMATION->start(unitImageInfo.unitName + "RightDash");
		ANIMATION->start(unitImageInfo.unitName + "LeftDash");
	}

	(*viskul)->playerDashMove(futureRc, DashCount, playerDashJump, DashFoward, skulInfo.playerDashSpeed);
	if (DashCount > 0 && !playerDashJump && !isAtk)
	{
		unitImageInfo.unitState = "Dash";
	}
	DashDelay++;
	if (DashDelay >= skulInfo.DashTime)
	{
		DashDelay = skulInfo.DashTime;
		playerDoubleDash = true;
		isDash = false;
	}
}
//
//void C_player::playerDashMove()
//{
//	if (playerDashInfo.DashCount > 0 && !playerDashJump)
//	{
//		playerDashInfo.DashCount--;
//		if (playerDashInfo.DashFoward)
//		{
//			pt.x -= playerDashInfo.playerDashSpeed;
//			unitImageInfo.unitState = "Dash";
//
//		}
//
//		else if (!playerDashInfo.DashFoward)
//		{
//			pt.x += playerDashInfo.playerDashSpeed;
//			unitImageInfo.unitState = "Dash";
//		}
//	}
//}

void C_player::playerDash_Jump()
{
	if (DashDelay < skulInfo.DashTime / 2 && playerDashJump)
	{
		Gravity();
		DashCount = 0;
		//playerDashInfo.DashDelay = 0;
		DashJumpCount++;

		if (DashFoward)
		{
			//pt.x -= skulInfo.playerDashSpeed;
			movetoLeft(futureRc, skulInfo.playerDashSpeed);
			unitImageInfo.unitState = "Jump";
		}

		else if (!DashFoward)
		{
			//pt.x += skulInfo.playerDashSpeed;
			movetoRight(futureRc, skulInfo.playerDashSpeed);
			unitImageInfo.unitState = "Jump";
		}

		if (DashJumpCount >= 10)
		{
			DashJumpCount = 0;
			playerDashJump = false;
			DashDelay = skulInfo.DashTime / 2;
		}
	}
}

void C_player::playerAtk()
{
	atkCount++;
	if (InputManager->isOnceKeyDown('X') && !isDash && !isJump)
	{
		atkCount = 0;
		ANIMATION->start(unitImageInfo.unitName + "LeftAtkMotion1");
		ANIMATION->start(unitImageInfo.unitName + "RightAtkMotion1");
		isAtk = true;
		if (isLeft)
		{
			unitImageInfo.unitFoward = "Left";
		}
		else unitImageInfo.unitFoward = "Right";
		unitImageInfo.unitState = "AtkMotion1";
		(*viskul)->playerAttack(pt, isLeft);
	}
	if (atkCount >= 50)
	{
		atkCount = 50;
		isAtk = false;
	}
}

void C_player::changeSkul()
{
	if (InputManager->isOnceKeyDown(VK_SPACE))
	{
		if (viskul == vskul.begin()) viskul = vskul.begin() + 1;
		else viskul = vskul.begin();
		skulInfo = (*viskul)->getskulInfo();
		setUnitImageInfo((*viskul)->getUnitName(), "Left", "Idle");
		ANIMATION->start(unitImageInfo.unitName + "LeftIdle");
		ANIMATION->start(unitImageInfo.unitName + "RightIdle");
		ITEM->Equip(this);
	}
}
