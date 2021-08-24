#include "framework.h"
#include "object.h"
#include "fsm.h"
#include "state.h"
#include "obstacle.h"
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

void C_object::AI_init(C_object* _object)
{
	ai = new C_fsm(_object);
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

	if (fDist < fSize)
	{
		// x 축으로 겹친다.
		fDist = abs(_left->getPos().y - _right->getPos().y);
		fSize = _left->getSize().y / 2.f + _right->getSize().y / 2.f;

		if (fDist < fSize)
		{
			// y축으로 겹친다.
			return true;
		}
	}

	return false;
}

void C_object::Gravity()
{
	if (jumpPower > 0) jumpPower--;
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


void C_object::isWall()
{
	for (int i = 0; i < OBSTACLE->getvObstacle().size(); i++)
	{
		float tileLeft = (*OBSTACLE->getviObstacle(i))->getPt().x - (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().x / 2;
		float tileRight = (*OBSTACLE->getviObstacle(i))->getPt().x + (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().x / 2;
		float tileTop = (*OBSTACLE->getviObstacle(i))->getPt().y - (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().y / 2;
		float tileBottom = (*OBSTACLE->getviObstacle(i))->getPt().y + (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().y / 2;

		bool collision = isCollision((*OBSTACLE->getviObstacle(i))->getCollider(), collider);
		bool inRangeX = pt.x > tileLeft - collider->getSize().x / 2 && pt.x < tileRight + collider->getSize().x / 2;
		bool inRangeY = pt.y > tileTop - collider->getSize().y / 2 && pt.y < tileBottom + collider->getSize().y / 2;
		bool isLeft = prevPt.x < pt.x;
		bool isUp = prevPt.y > pt.y;
		if (collision && isLeft && inRangeY)
		{
			pt.x = tileLeft - collider->getSize().x / 2;
		}

		if (collision && inRangeX && isUp)
		{
			pt.y = tileBottom + collider->getSize().y / 2;
		}
	}
}
