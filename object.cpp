#include "framework.h"
#include "object.h"
#include "fsm.h"
#include "state.h"
#include "obstacle.h"

#include "knightState.h"
#include "BigEntState.h"
#include "BigknightState.h"

C_object::C_object()
{
	isJump = false;
	prevPt = pt;
	landCollision = false;
	wallCollision = false;
	floorCollision = false;
	ani = new animation;
	objectImage = new image;

	frameX = 0;
	frameY = 0;
	maxFrameX = 0;
	startFrameX = 0;
	isStart = true;
	frameType = FRAME_TYPE::LOOP;

	delay = 0;
	damage = 0;
	ap = 250;

	Bump = CreateRectRgn(0, 0, 0, 0);
	hrgnRc = CreateRectRgn(1,1,1,1);
	rc = RectMake(0,0, 0, 0);
	lpRect = &rc;
	testRc = RectMake(0, 0, 0, 0);
	testLP = &testRc;
	/*tile = { 0,0,0,0 };
	NONEtile = false;*/
	//searchList.push_back(0);
}

C_object::~C_object()
{
	SAFE_DELETE(ai);
	//Safe_Delete_Vector(vAi);
}

HRESULT C_object::init()
{
	return S_OK;
}

void C_object::release()
{
}

void C_object::update()
{

}

void C_object::render()
{
}

void C_object::AI_init(C_object* _object, UNIT_TYPE _type)
{
	ai = new C_fsm(_object);
	switch (_type)
	{
	case UNIT_TYPE::PLAYER:
		break;
	case UNIT_TYPE::KNIGHT:
		ai->AddState(new knight_Idle);
		ai->AddState(new knight_Trace);
		ai->AddState(new knight_Atk);
		ai->AddState(new knight_Die);
		ai->AddState(new knight_Damage);
		ai->SetState(STATE_TYPE::IDLE);
		break;
	case UNIT_TYPE::BIGENT:
		ai->AddState(new BigEnt_Idle);
		ai->AddState(new BigEnt_Trace);
		ai->AddState(new BigEnt_Atk);
		ai->AddState(new BigEnt_Die);
		ai->AddState(new BigEnt_Damage);
		ai->SetState(STATE_TYPE::IDLE);
	case UNIT_TYPE::BIGKNIGHT:
		ai->AddState(new Bigknight_Idle);
		ai->AddState(new Bigknight_Trace);
		ai->AddState(new Bigknight_Atk);
		ai->AddState(new Bigknight_Die);
		ai->AddState(new Bigknight_Damage);
		ai->SetState(STATE_TYPE::IDLE);
	default:
		break;
	}
}


void C_object::AI_update()
{
	ai->update();
}

STATE_TYPE C_object::getstate()
{
	STATE_TYPE st = ai->getState()->GetStateType();
	return st;
}

void C_object::setState(STATE_TYPE _type)
{
	ai->ChangeState(_type);
}

bool C_object::isCollision(C_collider* _left, C_collider* _right)
{
	float fDist = abs(_left->getPos().x - _right->getPos().x);
	float fSize = _left->getSize().x / 2.f + _right->getSize().x / 2.f;

	if (fDist <= fSize)
	{
		// x 축으로 겹친다.
		fDist = abs(_left->getPos().y - _right->getPos().y);
		fSize = _left->getSize().y / 2.f + _right->getSize().y / 2.f;

		if (fDist <= fSize)
		{
			// y축으로 겹친다.
			return true;
		}
	}

	return false;
}

void C_object::setFrameMaxMin(int _min, int _max)
{
	startFrameX = _min;
	maxFrameX = IMAGE->findImage(unitImageInfo.unitName + unitImageInfo.unitState)->getMaxFrameX() - _max;
}



bool C_object::isCollision(RECT _left, RECT _right)
{
	int leftSize = _left.right - _left.left;
	int rightSize = _right.right - _right.left;

	int leftPt = _left.left + leftSize / 2;
	int rightPt = _right.left + rightSize / 2;

	float fDist = abs(leftPt - rightPt);
	float fSize = leftSize / 2.f + rightSize / 2.f;

	if (fDist <= fSize)
	{
		leftSize = _left.bottom - _left.top;
		rightSize = _right.bottom - _right.top;
		leftPt = _left.top + leftSize / 2;
		rightPt = _right.top + rightSize / 2;

		fDist = abs(leftPt - rightPt);
		fSize = leftSize / 2.f + rightSize / 2.f;

		if (fDist <= fSize)
		{
			// y축으로 겹친다.
			return true;
		}
	}

	return false;
}

void C_object::Gravity()
{
	if (jumpPower > 0) jumpPower = jumpPower - 0.5;
	else if (jumpPower <= 0) jumpPower = 0;
	/*pt.y -= jumpPower;
	pt.y += GRAVITY;*/
	movetoUp(futureRc, jumpPower);
	movetoDown(futureRc, GRAVITY);
}

void C_object::isLand()
{
	/*RECT bottomRc = RectMake(RectX(futureRc), futureRc.bottom-1, 1, 1);
	RECT testRc = RectMakeCenter(pt.x, pt.y + collider->getSize().y/2 -1, collider->getSize().x, 1);
	RECT testRc2 = RectMakeCenter(pt.x, pt.y-9, collider->getSize().x,1);*/

	bool isDown = pt.y < RectY(futureRc);

	landCollision = RectInRegion(OBSTACLE->getTotalLand(), &futureRc);
	bool dontDown = RectInRegion(OBSTACLE->getTotalLand(), &futureRcB);
	//bool testBool = RectInRegion(OBSTACLE->getTotalLand(), &testRc2);
	//bool testBool2 = RectInRegion(OBSTACLE->getTotalLand(), &bottomRc);
	if (/*landCollision &&*/ isDown &&dontDown /*&& !testBool */ )
	{
		isJump = false;
		jumpPower = GRAVITY;
		do
		{
			movetoUp(futureRc, 1);
			RECT test = RectMakeCenter(pt.x, futureRc.bottom-1,1, 1);
			landCollision = RectInRegion(OBSTACLE->getTotalLand(), &test);
		} while (landCollision);

	}
	else isJump = true;
}

void C_object::isBump()
{
	wallCollision = RectInRegion(OBSTACLE->getTotalWall(), &futureRc);
	CombineRgn(Bump, Bump, Bump, RGN_XOR);
	CombineRgn(hrgnRc, hrgnRc, hrgnRc, RGN_XOR);
	if (wallCollision)
	{
		CombineRgn(hrgnRc, CreateRectRgn(0,0,GameSizeX,GameSizeY), CreateRectRgn(futureRc.left, futureRc.top, futureRc.right, futureRc.bottom), RGN_AND);
		CombineRgn(Bump, hrgnRc, OBSTACLE->getTotalWall(), RGN_AND);
		getOut = RectInRegion(Bump, &futureRc);
	}
	GetRgnBox(Bump, lpRect);
	RECT* temp = lpRect;
	GetRgnBox(hrgnRc, testLP);


	bool isRight = pt.x < RectX(futureRc);
	bool isLeft = pt.x > RectX(futureRc);
	bool isUp = pt.y > RectY(futureRc);
	bool isDown = pt.y < RectY(futureRc);

	if (isDown && getOut)
	{
		/*do
		{*/
			RECT temp;
			isJump = false;
			movetoUp(futureRc, RectHeight(*lpRect));
		//	getOut = IntersectRect(&temp, lpRect, &futureRc);
		//} while (getOut);
	}
	if (isRight && getOut)
	{
		do
		{
			RECT temp;
			movetoLeft(futureRc, 1);
			getOut = IntersectRect(&temp,lpRect, &futureRc);
		} while (getOut);
	}
	
	if (isLeft && getOut)
	{
		do
		{
			RECT temp;
			movetoRight(futureRc, 1);
			getOut = IntersectRect(&temp, lpRect, &futureRc);
		} while (getOut);
	}
	if (isUp && getOut)
	{
		do
		{
			RECT temp;
			movetoDown(futureRc, 1);
			getOut = IntersectRect(&temp, lpRect, &futureRc);
		} while (getOut);
	}
}

void C_object::isClogged()
{

	//RECT bottomRc = RectMake(RectX(futureRc), futureRc.bottom, 1, 1);
	//RECT testRc = RectMakeCenter(pt.x, pt.y + collider->getSize().y / 2 - 1, collider->getSize().x, 1);
	//RECT testRc2 = RectMakeCenter(pt.x, pt.y - 9, collider->getSize().x, 1);
	//bool isDown = pt.y < RectY(futureRc);
	//landCollision = RectInRegion(OBSTACLE->getTotalWall(), &futureRc);
	//bool dontDown = RectInRegion(OBSTACLE->getTotalWall(), &futureRcB);
	//bool testBool = RectInRegion(OBSTACLE->getTotalWall(), &testRc2);


	bool isRight = pt.x < RectX(futureRc);
	bool isLeft = pt.x > RectX(futureRc);
	bool isUp = pt.y > RectY(futureRc);
	//bool isDown = pt.y < RectY(futureRc);
	//bool dontDown = RectInRegion(OBSTACLE->getTotalWall(), &futureRcB);
	bool dontLeft = RectInRegion(OBSTACLE->getTotalWall(), &futureRcL);
	bool dontRight = RectInRegion(OBSTACLE->getTotalWall(), &futureRcR);
	bool dontUp = RectInRegion(OBSTACLE->getTotalWall(), &futureRcT);
	bool LeftBump = RectInRegion(OBSTACLE->getTotalWall(), &futureRL);
	bool RightBump = RectInRegion(OBSTACLE->getTotalWall(), &futureRR);
	bool UpBump = RectInRegion(OBSTACLE->getTotalWall(), &futureRT);
	wallCollision = RectInRegion(OBSTACLE->getTotalWall(), &futureRc);
	floorCollision = RectInRegion(OBSTACLE->getTotalFloor(), &futureRc);

	
	if (floorCollision)
	{
		do
		{
			movetoUp(futureRc, 1);
			floorCollision = RectInRegion(OBSTACLE->getTotalFloor(), &futureRc);
		} while (floorCollision);
	}

	if (wallCollision && isUp && dontUp)
	{

		jumpPower = GRAVITY;
		do
		{
			movetoDown(futureRc, 1);
			wallCollision = RectInRegion(OBSTACLE->getTotalWall(), &futureRc);
		} while (wallCollision);
	}
	
	if (isLeft && wallCollision && dontLeft)
	{
		do
		{
			movetoRight(futureRc, 1);
			wallCollision = RectInRegion(OBSTACLE->getTotalWall(), &futureRc);
		} while (wallCollision);

	}

	if (isRight && wallCollision && dontRight)
	{

		//movetoLeft(futureRc, 10);

		do
		{
			movetoLeft(futureRc, 1);
			wallCollision = RectInRegion(OBSTACLE->getTotalWall(), &futureRc);
		} while (wallCollision);
	}




	rc = futureRc;
	pt = { RectX(rc), RectY(rc) };

	futureRcLTRB();
	//bool isUp = prevPt.y > pt.y;
	//bool isRight = prevPt.x < pt.x;
	//bool isLeft = prevPt.x > pt.x;

	//bool collision = RectInRegion(OBSTACLE->getTotalWall(), &rc);
	//
	//if (collision)
	//{
	//	//pt.y =500;
	//	jumpPower = GRAVITY;
	//}
	//if (collision)
	//{
	//	//pt.x = 500;
	//}

	
}
//void C_object::isClogged()
//{
//	bool isUp = prevPt.y > pt.y;
//	bool isRight = prevPt.x < pt.x;
//	bool isLeft = prevPt.x > pt.x;
//	for (int i = 0; i < OBSTACLE->getvWall().size(); i++)
//	{
//		RECT tile = RectMakeCenter((*OBSTACLE->getviWall(i))->getPt(), (*OBSTACLE->getviWall(i))->getCollider()->getSize().x, (*OBSTACLE->getviWall(i))->getCollider()->getSize().y);
//		bool collision = isCollision((*OBSTACLE->getviWall(i))->getCollider(), collider);
//		bool RangeX = prevPt.x - collider->getSize().x / 2 < tile.right && prevPt.x + collider->getSize().x / 2 > tile.left;
//		bool RangeY = prevPt.y - collider->getSize().y / 2 < tile.bottom && prevPt.y + collider->getSize().y / 2 > tile.top;
//
//		bool test1 = prevPt.y + tileSize / 2 > tile.bottom;
//		bool test3 = prevPt.x - tileSize / 2 > tile.left;
//		bool test4 = prevPt.x + tileSize / 2 < tile.right;
//		if (isUp && collision && RangeX && test1)
//		{
//			pt.y = (*OBSTACLE->getviWall(i))->getPt().y + tileSize / 2 + collider->getSize().y;
//			jumpPower = GRAVITY;
//		}
//		if (collision && isRight && RangeY && test4)
//		{
//			pt.x = (*OBSTACLE->getviWall(i))->getPt().x - tileSize / 2 - collider->getSize().x / 2;
//		}
//		if (collision && isLeft && RangeY && test3)
//		{
//			pt.x = (*OBSTACLE->getviWall(i))->getPt().x + tileSize / 2 + collider->getSize().x / 2;
//		}
//	}
//}

void C_object::isWall()
{
	
}

void C_object::futureRcLTRB()
{
	futureRcL = RectMakeCenter(futureRc.left-1, RectY(futureRc), 1, 1);
	futureRcT = RectMakeCenter(RectX(futureRc), futureRc.top-1, 1, 1);
	futureRcR = RectMakeCenter(futureRc.right+1, RectY(futureRc), 1, 1);
	futureRcB = RectMakeCenter(RectX(futureRc), futureRc.bottom+1, 1, 1);
	futureRL = RectMakeCenter(RectX(futureRc) - 1, RectY(futureRc), RectWidth(futureRc), RectHeight(futureRc));
	futureRT = RectMakeCenter(RectX(futureRc), RectY(futureRc) - 1, RectWidth(futureRc), RectHeight(futureRc));
	futureRR = RectMakeCenter(RectX(futureRc) + 1, RectY(futureRc), RectWidth(futureRc), RectHeight(futureRc));
	futureRB = RectMakeCenter(RectX(futureRc), RectY(futureRc) + 1, RectWidth(futureRc), RectHeight(futureRc));

}

void C_object::setUnitImageInfo(string _name, string _Foward, string _state)
{
	unitImageInfo.unitName = _name;
	unitImageInfo.unitFoward = _Foward;
	unitImageInfo.unitState = _state;
}

