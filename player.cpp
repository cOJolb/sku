#include "framework.h"
#include "player.h"
#include"obstacle.h"
#include "littlebone.h"
#include"clown.h"
#include"warrior.h"
C_player::C_player()
{
	curSkul = new C_littlebone;
	//nextSkul = new C_clown;
	nextSkul = nullptr;
	tempSkul = nullptr;
	//vskul.push_back(curSkul);
	//vskul.push_back(nextSkul);

	//viskul = vskul.begin();
	//skulInfo = (*viskul)->getskulInfo();
	skulInfo = curSkul->getskulInfo();
	//setUnitImageInfo((*viskul)->getUnitName(), "Left", "Idle");
	setUnitImageInfo(curSkul->getUnitName(), "Left", "Idle");

	pt = { 200, 200 }; // 이것들 저장어떻게 하지 ..
	prevPt = pt;
	collider = new C_collider(pt, skulInfo.playerSize);
	rc = RectMakeCenter(collider->getPos(), collider->getSize().x, collider->getSize().y);
	futureRc = RectMakeCenter(pt, collider->getSize().x, collider->getSize().y);
	futureRcLTRB();

	DashCount = 0;
	isLeft = false;
	isDash = false;
	playerDoubleJump = false;
	playerDashJump = false;
	DashJumpCount = 0;
	DashDelay = 0;
	isAtk = false;
	isAtk2 = false;
	atkReady = true;
	atkCount = 0;
	jumpAtkCount = 0;
	skill1Count = 0;
	skill2Count = 0;
	ap = 250;
	
	maxHp = 100;
	hp = 100;

	ani = ANIMATION->findAnimation(unitImageInfo.unitName + unitImageInfo.unitFoward + unitImageInfo.unitState);
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
	ANIMATION->start(curSkul->getUnitName() + "LeftIdle");
	ANIMATION->start(curSkul->getUnitName() + "RightIdle");
	return S_OK;
}

void C_player::release()
{
}

void C_player::update()
{
	futureRc = RectMakeCenter(pt, collider->getSize().x, collider->getSize().y);
	changeSkul();
	playerMove();
	playerJump();
	playerDash();
	playerDash_Jump();
	playerAtk();
	playerJumpAtk();
	playerSkill1();
	playerSkill2();
	curSkul->update(pt,futureRc,isLeft,skulInfo);

	if (DashDelay >= skulInfo.DashTime / 2) Gravity();
	isLand();
	isClogged();
	
	collider->setPos(pt);

	ani = ANIMATION->findAnimation(unitImageInfo.unitName + unitImageInfo.unitFoward + unitImageInfo.unitState);

	rc = RectMakeCenter(collider->getPos(), collider->getSize().x, collider->getSize().y);

	if (ap < 250) { ap += 10; }
	else if (ap > 250) { ap = 250; }
}

void C_player::render()
{
	ani = ANIMATION->findAnimation(unitImageInfo.unitName + unitImageInfo.unitFoward + unitImageInfo.unitState);
	IMAGE->findImage(unitImageInfo.unitName)->aniRenderCenterAlpha(getCVOSDC(), pt.x , pt.y, ani, ap);
}

void C_player::playerMove()
{
	if (DashDelay >= skulInfo.DashTime/2 && !isAtk && !DontMove && !skillA)
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
			if (!isJumpAtk)
			{
				unitImageInfo.unitFoward = "Left";
				unitImageInfo.unitState = "Move";
			}
		}
		if (goRight && !goLeft )
		{
			//pt = vector2(pt.x + skulInfo.playerSpeed, pt.y);
			movetoRight(futureRc, skulInfo.playerSpeed);
			isLeft = false;
			if (!isJumpAtk)
			{
				unitImageInfo.unitFoward = "Right";
				unitImageInfo.unitState = "Move";
			}
		}
		if (!goLeft && !goRight && !isJump && !isAtk && !isJumpAtk &&!DontMove)
		{
			unitImageInfo.unitState = "Idle";
		}
	}
}

void C_player::playerJump()
{
	bool goJump = InputManager->isOnceKeyDown('C');
	bool goJumpstay = InputManager->isStayKeyDown('C');
	bool pushDown = InputManager->isStayKeyDown(VK_DOWN);
	RECT checkRc = RectMakeCenter(pt.x, pt.y + 2, collider->getSize().x, collider->getSize().y);
	bool landCollision = RectInRegion(OBSTACLE->getTotalLand(), &checkRc);
	bool WallCollision = RectInRegion(OBSTACLE->getTotalWall(), &checkRc);
	if (!isJump) playerDoubleJump = true;
	if (goJumpstay && pushDown && landCollision && !WallCollision && !DontMove && !skillA)
	{
		pt.y += 20;
		//pt.y += 80;
		//isDownJump = true;
	}
	else if (goJump && !isJump && !isAtk && !DontMove)
	{
		playerDashJump = true;
		jumpPower = skulInfo.playerJumpPower;
	}
	else if (goJump && playerDoubleJump && isJump && !isAtk && !DontMove)
	{
		playerDashJump = true;
		jumpPower = skulInfo.playerJumpPower;
		playerDoubleJump = false;
	}
	if (jumpPower > 10 && !isAtk && !isJumpAtk) unitImageInfo.unitState = "Jump";
	if (jumpPower == 10 || DashDelay == skulInfo.DashTime / 2 && !isAtk && !isJumpAtk && !isSkulChange)
	{
		ANIMATION->start(unitImageInfo.unitName + "RightFall");
		ANIMATION->start(unitImageInfo.unitName + "LeftFall");
	}
	if ( isJump  && jumpPower <= 10 && DashDelay > skulInfo.DashTime / 2 &&!isAtk && !isJumpAtk && !isSkulChange)  unitImageInfo.unitState = "Fall";
}


void C_player::playerDash()
{
	bool goDash = InputManager->isOnceKeyDown('Z');
	if (goDash && DashDelay >= skulInfo.DashTime && !isDash && !isAtk && !isJumpAtk && !DontMove && !skillA)
	{
		playerDashJump = false;
		jumpPower = 0;
		isDash = true;
		DashDelay = 0;
		DashFoward = isLeft;
		DashCount = skulInfo.DashTerm;
		ANIMATION->start(unitImageInfo.unitName + "RightDash");
		ANIMATION->start(unitImageInfo.unitName + "LeftDash");
		//if(DashFoward) {}
		//else { EFFECT->play(unitImageInfo.unitName + "RightDashEffect", pt.x, pt.y + collider->getSize().y/2); }
	}

	else if (goDash && playerDoubleDash && DashDelay <= skulInfo.DashTime / 2 &&!isAtk && !isJumpAtk && !DontMove && skulInfo.canDoubleDash)
	{
		playerDashJump = false;
		playerDoubleDash = false;
		isDash = true;
		DashDelay = 0;
		DashCount = skulInfo.DashTerm;
		ANIMATION->start(unitImageInfo.unitName + "RightDash");
		ANIMATION->start(unitImageInfo.unitName + "LeftDash");
		if (DashFoward) {}
		else { EFFECT->play(unitImageInfo.unitName + "RightDashEffect", pt.x, pt.y + collider->getSize().y / 2); }
	}

	//(*viskul)->playerDashMove(futureRc, DashCount, playerDashJump, DashFoward, skulInfo.playerDashSpeed);
	//curSkul->playerDashMove(futureRc, DashCount, playerDashJump, DashFoward, skulInfo.playerDashSpeed);

	if (DashCount > 0 && !playerDashJump)
	{
		DashCount--;
		curSkul->playerDashMove(futureRc, DashFoward, skulInfo);
	
	}


	if (DashCount > 0 && !playerDashJump && !isAtk && !isJumpAtk)
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


void C_player::playerDash_Jump()
{
	if (DashDelay < skulInfo.DashTime / 2 && playerDashJump && !DontMove)
	{
		Gravity();
		DashCount = 0;
		DashJumpCount++;

		if (DashFoward)
		{
			movetoLeft(futureRc, skulInfo.playerDashSpeed);
			unitImageInfo.unitState = "Jump";
		}

		else if (!DashFoward)
		{
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
	jumpAtkCount++;
	if (InputManager->isOnceKeyDown('X') && !isDash && !DontMove)
	{
		if (!isJump)
		{
			if (isAtk)
			{
				isAtk2 = true;
			}
			if (!isAtk && !isAtk2)
			{
				atkReady = false;
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
				curSkul->PlayAtkA();
			}
		}
		else if (isJump && !isJumpAtk)
		{
			jumpAtkCount = 0;
			ANIMATION->start(unitImageInfo.unitName + "LeftJumpAtk");
			ANIMATION->start(unitImageInfo.unitName + "RightJumpAtk");
			isJumpAtk = true;
			if (isLeft)
			{
				unitImageInfo.unitFoward = "Left";
			}
			else unitImageInfo.unitFoward = "Right";

			unitImageInfo.unitState = "JumpAtk";
			DontMove = curSkul->PlayJumpAtk();
		}
	}
	else if (!isJump && !DontMove) { isJumpAtk = false; }

	if (jumpAtkCount >= skulInfo.jumpAtkDelay && isJumpAtk)
	{
		jumpAtkCount = skulInfo.jumpAtkDelay;
		isJumpAtk = false;
		DontMove = false;
	}


	if (!isAtk2 && atkCount >= skulInfo.atkDelay) { isAtk = false; }

	if (isAtk2 && atkCount == skulInfo.atkDelay )
	{
		ANIMATION->start(unitImageInfo.unitName + "LeftAtkMotion2");
		ANIMATION->start(unitImageInfo.unitName + "RightAtkMotion2");
		if (isLeft)
		{
			unitImageInfo.unitFoward = "Left";
		}
		else unitImageInfo.unitFoward = "Right";
		unitImageInfo.unitState = "AtkMotion2";
		curSkul->PlayAtkB();
	}
	if (atkCount >= skulInfo.atkDelay*2)
	{ 
		isAtk = false;
		isAtk2 = false;
	}
}

void C_player::playerJumpAtk()
{
}

void C_player::playerSkill1()
{
	skill1Count++;
	if (skill1Count >= skulInfo.skill1CoolTime) { skill1Count = skulInfo.skill1CoolTime; }
	if (InputManager->isStayKeyDown('A') && !isDash && !isJump && skill1Count >=skulInfo.skill1CoolTime && !DontMove)
	{
		skill1Count = 0;
		skillA = true;
		ANIMATION->start(unitImageInfo.unitName + "LeftSkill1");
		ANIMATION->start(unitImageInfo.unitName + "RightSkill1");
		if (isLeft)
		{
			unitImageInfo.unitFoward = "Left";
		}
		else unitImageInfo.unitFoward = "Right";

		unitImageInfo.unitState = "Skill1";
		DontMove = curSkul->PlaySkillA();
	}
	
	if (skill1Count >= skulInfo.skill1Delay && skillA)
	{
		DontMove = false;
		skillA = false;
	}
}

void C_player::playerSkill2()
{
	skill2Count++;
	if (skill2Count >= skulInfo.skill2CoolTime) { skill2Count = skulInfo.skill2CoolTime; }
	if (InputManager->isStayKeyDown('S') && !isDash && !isJump && skill2Count >= skulInfo.skill2CoolTime && !DontMove)
	{
		skill2Count = 0;
		skillB = true;
		ANIMATION->start(unitImageInfo.unitName + "LeftIdle");
		ANIMATION->start(unitImageInfo.unitName + "RightIdle");
		if (isLeft)
		{
			unitImageInfo.unitFoward = "Left";
		}
		else unitImageInfo.unitFoward = "Right";

		unitImageInfo.unitState = "Idle";
		DontMove = curSkul->PlaySkillB();
	}

	if (skill2Count >= skulInfo.skill2Delay && skillB)
	{
		DontMove = false;
		skillB = false;
	}
}

void C_player::changeSkul()
{
	changeCount++;
	if (changeCount >= skulInfo.changeCoolTime) { changeCount = skulInfo.changeCoolTime; }
	if (InputManager->isOnceKeyDown(VK_SPACE) && !DontMove && changeCount >= skulInfo.changeCoolTime)
	{
		if (nextSkul != nullptr)
		{
			changeCount = 0;
			tempSkul = curSkul;
			curSkul = nullptr;
			curSkul = nextSkul;
			nextSkul = tempSkul;
			skulInfo = curSkul->getskulInfo();
			unitImageInfo.unitName = curSkul->getUnitName();

			ANIMATION->start(curSkul->getUnitName() + "LeftIdle");
			ANIMATION->start(curSkul->getUnitName() + "RightIdle");
			ANIMATION->start(curSkul->getUnitName() + "LeftChange");
			ANIMATION->start(curSkul->getUnitName() + "RightChange");

			unitImageInfo.unitState = "Change";
			ITEM->Equip(this);

			DontMove = curSkul->PlayChange();
			isSkulChange = true;
		}
	}
	if (isSkulChange && changeCount >= skulInfo.changeDelay)
	{
		DontMove = false;
		isSkulChange = false;
	}
	
}



float C_player::getSkillACoolTime()
{
	double D_maxCool = skulInfo.skill1CoolTime;
	double D_count = skill1Count;
	double D_Height = 36;
	float NowCool = D_Height / D_maxCool * D_count;
	return NowCool;
}

float C_player::getSkillBCoolTime()
{
	double D_maxCool = skulInfo.skill2CoolTime;
	double D_count = skill2Count;
	double D_Height = 36;
	float NowCool = D_Height / D_maxCool * D_count;
	return NowCool;
}

float C_player::getChangeCoolTime()
{
	double D_maxCool = skulInfo.changeCoolTime;
	double D_count = changeCount;
	double D_Height = 36;
	float NowCool = D_Height / D_maxCool * D_count;
	return NowCool;
}

void C_player::setCurSkul(SKUL_TYPE _type)
{
	switch (_type)
	{
	case SKUL_TYPE::SKUL:
		curSkul = new C_littlebone;
		break;
	case SKUL_TYPE::CLOWN:
		curSkul = new C_clown;
		break;
	case SKUL_TYPE::WARRIOR:
		curSkul = new C_warrior;
		break;
	default:
		break;
	}
	skulInfo = curSkul->getskulInfo();
	setUnitImageInfo(curSkul->getUnitName(), "Left", "Idle");
	ANIMATION->start(curSkul->getUnitName() + "LeftIdle");
	ANIMATION->start(curSkul->getUnitName() + "RightIdle");
}

void C_player::setNextSkul(SKUL_TYPE _type)
{
	switch (_type)
	{
	case SKUL_TYPE::SKUL:
		nextSkul = new C_littlebone;
		break;
	case SKUL_TYPE::CLOWN:
		nextSkul = new C_clown;
		break;
	case SKUL_TYPE::WARRIOR:
		nextSkul = new C_warrior;
		break;
	default:
		break;
	}
}
