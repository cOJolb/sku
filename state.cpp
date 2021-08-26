#include "framework.h"
#include "state.h"
#include "object.h"
#include "obstacle.h"
C_state::C_state()
{
	count = 0;
	movetime = 0;
	Foward = false;
	prevFoward = false;
}

C_state::~C_state()
{
}

bool C_state::inRange(int _range, vector2 _pt)
{
	if (UTIL::getDistance(object->getPt(), _pt) < _range)
	{
		return true;
	}
	else return false;
}

bool C_state::isLeft(vector2 _pt)
{
	if (object->getPt().x - _pt.x >= 0)
	{
		return true;
	}
	else return false;
}

bool C_state::onLand(vector2 _pt)
{
	for (int i = 0; i < OBSTACLE->getvObstacle().size(); i++)
	{
		bool inRangeX = (*OBSTACLE->getviObstacle(i))->getPt().x - (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().x / 2 <= _pt.x
			&& _pt.x <= (*OBSTACLE->getviObstacle(i))->getPt().x + (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().x / 2;
		bool inRangeY = (*OBSTACLE->getviObstacle(i))->getPt().y - (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().y / 2 + GRAVITY >= _pt.y + object->getCollider()->getSize().y
			&& _pt.y + object->getCollider()->getSize().y >= (*OBSTACLE->getviObstacle(i))->getPt().y - (*OBSTACLE->getviObstacle(i))->getCollider()->getSize().y / 2;
		bool isLand = true;
		if (inRangeX && inRangeY && isLand)
		{
			return true;
		}
	}
	return false;
}

void C_state::move()
{
	vector2 movePt = object->getPt();
	count++;
	if (count > movetime)
	{
		count = 0;
		movetime = RND->getFromIntTo(60, 200);
		Foward = RND->getFromIntTo(0, 1);
	}
	if (prevFoward != Foward)
	{
		ANIMATION->start(object->getImageInfo().unitName + "LeftWalk");
		ANIMATION->start(object->getImageInfo().unitName + "RightWalk");
	}
	if (Foward)
	{
		movePt.x -= 2;
		object->setUnitImageInfo(object->getImageInfo().unitName, "Left", "Walk");
	}
	else
	{
		movePt.x += 2;
		object->setUnitImageInfo(object->getImageInfo().unitName, "Right", "Walk");
	}

	if(onLand(movePt)) object->setPt(movePt);
	else Foward = !Foward;

	prevFoward = Foward;
}

void C_state::move(bool _isLeft)
{
	vector2 movePt = object->getPt();

	/*count++;
	if (count > movetime)
	{
		count = 0;
		movetime = RND->getFromIntTo(60, 200);
		Foward = _isLeft;
	}*/
	Foward = _isLeft;
	if (prevFoward != Foward)
	{
		ANIMATION->start(object->getImageInfo().unitName + "LeftWalk");
		ANIMATION->start(object->getImageInfo().unitName + "RightWalk");
	}
	if (Foward)
	{
		movePt.x -= 2;
		object->setUnitImageInfo(object->getImageInfo().unitName, "Left", "Walk");
	}
	else
	{
		movePt.x += 2;
		object->setUnitImageInfo(object->getImageInfo().unitName, "Right", "Walk");
	}

	if (onLand(movePt)) object->setPt(movePt);
	else Foward = !Foward;

	prevFoward = Foward;
}
