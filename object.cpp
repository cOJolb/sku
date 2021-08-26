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

//void C_object::Jump()
//{
//	if (jumpPower > 0) jumpPower = jumpPower - 0.5;
//	else if (jumpPower <= 0) jumpPower = 0;
//	pt.y -= jumpPower;
//}

void C_object::Gravity()
{
	if (jumpPower > 0) jumpPower = jumpPower - 0.5;
	else if (jumpPower <= 0) jumpPower = 0;
	pt.y -= jumpPower;
	pt.y += GRAVITY;
}

void C_object::isLand()
{
	for (int i = 0; i < OBSTACLE->getvObstacle().size(); i++)
	{
		bool inRangeX = (*OBSTACLE->getviObstacle(i))->getPt().x - (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().x / 2 <= pt.x
			&& pt.x <= (*OBSTACLE->getviObstacle(i))->getPt().x + (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().x / 2;
		bool inRangeY = (*OBSTACLE->getviObstacle(i))->getPt().y - (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().y / 2 + GRAVITY >= pt.y + collider->getSize().y
			&& pt.y + collider->getSize().y >= (*OBSTACLE->getviObstacle(i))->getPt().y - (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().y / 2;
		bool isDown = prevPt.y <= pt.y;
		if (inRangeX && inRangeY && isDown)
		{
			pt.y = (*OBSTACLE->getviObstacle(i))->getPt().y - 18 - collider->getSize().y;
			isJump = false;
			break;
		}
		else isJump = true;
	}
}

void C_object::isBump()
{
}

void C_object::isClogged()
{
	for (int i = 0; i < OBSTACLE->getvObstacle().size(); i++)
	{
		RECT tile = RectMakeCenter((*OBSTACLE->getviObstacle(i))->getPt(), (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().x, (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().y);
		RECT unit = RectMakeCenter(pt, collider->getSize().x, collider->getSize().y);
		RECT prevUnit = RectMakeCenter(prevPt, collider->getSize().x, collider->getSize().y);
		bool collision = isCollision((*OBSTACLE->getviObstacle(i))->getCollider(), collider);
		bool inRangeX = prevUnit.left < tile.right && prevUnit.right > tile.left;
		bool inRangeY = prevUnit.top < tile.bottom && prevUnit.bottom > tile.top;
		bool test1 = prevUnit.bottom > tile.bottom;
		bool test2 = prevUnit.top < tile.top;
		bool test3 = prevUnit.left > tile.left;
		bool test4 = prevUnit.right < tile.right;
		bool isUp = prevPt.y > pt.y;
		bool isLeft = prevPt.x > pt.x;
		bool isDown = prevPt.y < pt.y;
		bool isRight = prevPt.x < pt.x;
		
		if (collision && inRangeX  && test1 && isUp )
		{
			unit.top = tile.bottom;
			unit.bottom = unit.top + collider->getSize().y;
			jumpPower = GRAVITY;
		}
		else if (collision && inRangeY  && test4  && isRight )
		{
			unit.right = tile.left;
			unit.left = unit.right - collider->getSize().x;
		}
		else if (collision && inRangeY  && test3 && isLeft)
		{
			unit.left = tile.right;
			unit.right = unit.left + collider->getSize().x;
		}
		pt = { RectX(unit), RectY(unit) };
	}
}


void C_object::isWall()
{
	
}
