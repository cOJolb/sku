#include "framework.h"
#include "object.h"
#include "fsm.h"
#include "state.h"
#include "obstacle.h"

#include "knightState.h"

C_object::C_object()
{
	isJump = false;
	prevPt = pt;
	landCollision = false;
	wallCollision = false;
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
	bool isDown = pt.y < RectY(futureRc);
	//bool isRight = prevPt.x < pt.x;
	//bool isLeft = prevPt.x > pt.x;
	//bool isDown = prevPt.y <= pt.y;
	//bool isUp = prevPt.y > pt.y;
	landCollision = RectInRegion(OBSTACLE->getTotalLand(), &futureRc);
	bool dontDown = RectInRegion(OBSTACLE->getTotalLand(), &futureRcB);
	if (landCollision && isDown )
	{
		isJump = false;
		jumpPower = GRAVITY;
		do
		{
			movetoUp(futureRc, 1);
			landCollision = RectInRegion(OBSTACLE->getTotalLand(), &futureRc);
		} while (landCollision);
		/*while (landCollision)
		{
			movetoUp(futureRc, 1);
		}*/
	}
	else isJump = true;

	//rc = futureRc;
	//pt = { RectX(rc), RectY(rc) };

}

//void C_object::isLand()
//{
//	for (int i = 0; i < OBSTACLE->getvLand().size(); i++)
//	{
//		bool inRangeX = (*OBSTACLE->getviLand(i))->getPt().x - (*OBSTACLE->getviLand(i))->getCollider()->getSize().x / 2 <= pt.x
//			&& pt.x <= (*OBSTACLE->getviLand(i))->getPt().x + (*OBSTACLE->getviLand(i))->getCollider()->getSize().x / 2;
//		bool inRangeY = (*OBSTACLE->getviLand(i))->getPt().y - (*OBSTACLE->getviLand(i))->getCollider()->getSize().y / 2 + GRAVITY >= pt.y + collider->getSize().y
//			&& pt.y + collider->getSize().y >= (*OBSTACLE->getviLand(i))->getPt().y - (*OBSTACLE->getviLand(i))->getCollider()->getSize().y / 2;
//		bool isDown = prevPt.y <= pt.y;
//
//		if (inRangeX && inRangeY && isDown)
//		{
//			pt.y = (*OBSTACLE->getviLand(i))->getPt().y - tileSize / 2 - collider->getSize().y;
//			isJump = false;
//			jumpPower = GRAVITY;
//			break;
//		}
//		else isJump = true;
//	}
//}

void C_object::isBump()
{
}

void C_object::isClogged()
{
	RECT testRc = RectMake(RectX(futureRc) - RectWidth(futureRc) / 4, futureRc.top - 5, RectWidth(futureRc) / 2, 5);
	bool isRight = pt.x < RectX(futureRc);
	bool isLeft = pt.x > RectX(futureRc);
	bool isUp = pt.y > RectY(futureRc);
	bool dontLeft = RectInRegion(OBSTACLE->getTotalLand(), &futureRcL);
	bool dontRight = RectInRegion(OBSTACLE->getTotalLand(), &futureRcL);
	bool dontUp = RectInRegion(OBSTACLE->getTotalLand(), &futureRcL);
	wallCollision = RectInRegion(OBSTACLE->getTotalWall(), &futureRc);
	bool testCollision = RectInRegion(OBSTACLE->getTotalWall(), &testRc);


	//if (isUp && isLeft && )
	if (wallCollision && isUp && !dontUp && testCollision )
	{
		//movetoDown(futureRc, 10);
		jumpPower = GRAVITY;
		do
		{
			movetoDown(futureRc, 1);
			wallCollision = RectInRegion(OBSTACLE->getTotalWall(), &futureRc);
		} while (wallCollision);
	}
	if (isLeft && wallCollision && !dontLeft)
	{
		
		//movetoRight(futureRc, 10);
		
		do
		{
			movetoRight(futureRc, 1);
			wallCollision = RectInRegion(OBSTACLE->getTotalWall(), &futureRc);
		} while (wallCollision);
		
	}
	
	if (isRight && wallCollision &&!dontRight)
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
	futureRcL = RectMakeCenter(RectX(futureRc) - 1, RectY(futureRc), RectWidth(futureRc), RectHeight(futureRc));
	futureRcT = RectMakeCenter(RectX(futureRc), RectY(futureRc) - 1, RectWidth(futureRc), RectHeight(futureRc));
	futureRcR = RectMakeCenter(RectX(futureRc) + 1, RectY(futureRc), RectWidth(futureRc), RectHeight(futureRc));
	futureRcB = RectMakeCenter(RectX(futureRc), RectY(futureRc) + 1, RectWidth(futureRc), RectHeight(futureRc));

}

void C_object::setUnitImageInfo(string _name, string _Foward, string _state)
{
	unitImageInfo.unitName = _name;
	unitImageInfo.unitFoward = _Foward;
	unitImageInfo.unitState = _state;
}

