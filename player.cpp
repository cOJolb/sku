#include "framework.h"
#include "player.h"
#include"obstacle.h"

C_player::C_player()
{
	ani = ANIMATION->findAnimation("skulRightMove");
	pt = { 200, 200 };
	
	collider = new C_collider(pt, { 16,16 });
	//rc = RectMakeCenter(pt, 20, 20);
	
	ANIMATION->start("skulRightMove");

	playerSpeed = 5;
	playerDashSpeed = 45;
	playerDoubleJump = false;
	DashDelay = 34;
	DashTime = 34;
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
	for (int i = 0; i < OBSTACLE->getvObstacle().size(); i++)
	{
		float tileLeft = (*OBSTACLE->getviObstacle(i))->getPt().x - (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().x / 2;
		float tileRight = (*OBSTACLE->getviObstacle(i))->getPt().x + (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().x / 2;
		float tileTop = (*OBSTACLE->getviObstacle(i))->getPt().y - (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().y / 2;
		float tileBottom = (*OBSTACLE->getviObstacle(i))->getPt().y + (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().y / 2;

		bool collision = isCollision((*OBSTACLE->getviObstacle(i))->getCollider(), collider);
		if (tileLeft <= pt.x + 8 && pt.y >tileTop && pt.y <tileBottom)
		{
			pt.x = tileLeft - 8;
		}
		
	}
	ptUpdate();
	collider->setPos(pt);
}

void C_player::render()
{
	IMAGE->findImage("skul")->aniRender(getMemDC(), pt.x - IMAGE->findImage("skul")->getFrameWidth()/2, pt.y - IMAGE->findImage("skul")->getFrameHeight()/2, ani);
}

void C_player::playerMove()
{
	if (DashDelay >= DashTime/2)
	{
		bool goLeft = InputManager->isStayKeyDown(VK_LEFT);
		bool goRight = InputManager->isStayKeyDown(VK_RIGHT);
		if (goLeft && !goRight)
		{
			pt = vector2(pt.x - playerSpeed, pt.y);
			isLeft = true;
		}
		if (goRight && !goLeft)
		{
			pt = vector2(pt.x + playerSpeed, pt.y);
			isLeft = false;
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
		if (DashFoward)
			pt.x -= playerDashSpeed;
		else if (!DashFoward)
			pt.x += playerDashSpeed;
	}
	else if (goDash && playerDoubleDash && DashDelay <= DashTime / 2)
	{
		if (DashFoward)
			pt.x -= playerDashSpeed;
		else if (!DashFoward)
			pt.x += playerDashSpeed;

		playerDoubleDash = false;
		isDash = true;
		DashDelay = 0;
	}
	DashDelay++;
	if (DashDelay >= DashTime)
	{
		DashDelay = DashTime;
		playerDoubleDash = true;
		isDash = false;
	}
}
