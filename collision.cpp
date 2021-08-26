#include "framework.h"
#include "collision.h"
#include "collider.h"
#include "object.h"
#include "obstacle.h"
#include "enemy.h"
C_collision::C_collision()
{
}

C_collision::~C_collision()
{
}

bool C_collision::isCollision(RECT _left, RECT _right)
{
	int leftSize = _left.right - _left.left;
	int rightSize = _right.right - _right.left;

	int leftPt = _left.left + leftSize / 2;
	int rightPt = _right.left + rightSize / 2;

	float fDist = abs(leftPt - rightPt);
	float fSize = leftSize / 2.f + rightSize / 2.f;

	if (fDist < fSize)
	{
		leftSize = _left.bottom - _left.top;
		rightSize = _right.bottom - _right.top;
		leftPt = _left.top + leftSize / 2;
		rightPt = _right.top + rightSize / 2;

		fDist = abs(leftPt - rightPt);
		fSize = leftSize / 2.f + rightSize / 2.f;

		if (fDist < fSize)
		{
			// y축으로 겹친다.
			return true;
		}
	}
	return false;
}

bool C_collision::isCollision(C_collider* _left, C_collider* _right)
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

bool C_collision::tileCollision(C_obstacle* _tile, C_object* _unit)
{
	RECT rec;
	if (_tile->getMovable())
	{
	}
	return false;
}

void C_collision::stageCollision()
{
	for (int i = 0; i < ENEMY->getvEnemy().size(); i++)
	{
		bool PlayertoMonster = isCollision((*ENEMY->getviEnemy(i))->getCollider(), PLAYERDATA->getPlayerData().playerCollider);
		if (PlayertoMonster)
		{
			ENEMY->eraserEnemy(i);
		}
	}
}
