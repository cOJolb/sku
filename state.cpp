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

bool C_state::crossRange(int _range, vector2 _pt)
{
	bool horizontality = _pt.y >= object->getPt().y + object->getCollider()->getSize().y/2 - _range && _pt.y <= object->getPt().y + object->getCollider()->getSize().y / 2 + _range;
	bool Perpendicular = _pt.x >= object->getPt().x - _range && _pt.x <= object->getPt().x + _range;
	if (horizontality || Perpendicular)
	{
		return true;
	}
	else return false;
}

bool C_state::crossRangeX(int _range, vector2 _pt)
{

	bool Perpendicular = _pt.x >= object->getPt().x - _range && _pt.x <= object->getPt().x + _range;
	if (Perpendicular)
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

bool C_state::onLand(RECT _rc)
{
	//RECT rec = RectMakeCenter(_pt, object->getCollider()->getSize().x, object->getCollider()->getSize().y);
	bool collision = RectInRegion(OBSTACLE->getTotalLand(),&_rc );
	if (collision)
	{
		return true;
	}
	else return false;
	/*	}
	}*/
	//return false;
}

void C_state::move()
{
	_futureRc = RectMakeCenter(object->getPt(), object->getCollider()->getSize().x, object->getCollider()->getSize().y);
	//vector2 movePt = object->getPt();
	count++;
	if (count > movetime)
	{
		count = 0;
		movetime = RND->getFromIntTo(60, 200);
		Foward = RND->getFromIntTo(0, 1);
	}
	/*if (prevFoward != Foward)
	{
		ANIMATION->start(object->getImageInfo().unitName + "LeftWalk");
		ANIMATION->start(object->getImageInfo().unitName + "RightWalk");
	}*/
	if (Foward)
	{
		movetoLeft(_futureRc, 2);
		object->setUnitImageInfo(object->getImageInfo().unitName, "Left", "Walk");
	}
	else
	{
		movetoRight(_futureRc, 2);
		object->setUnitImageInfo(object->getImageInfo().unitName, "Right", "Walk");
	}

	//if (onLand(_futureRc)) { object->setFutureRc(_futureRc); } //object->setPt(movePt);
	//else Foward = !Foward;

	//prevFoward = Foward;
}

void C_state::move(bool _isLeft)
{
	_futureRc = RectMakeCenter(object->getPt(), object->getCollider()->getSize().x, object->getCollider()->getSize().y);
	count++;
	if (count > movetime)
	{
		count = 0;
		movetime = 50;
		Foward = _isLeft;
	}

	if (Foward)
	{
		movetoLeft(_futureRc, 2);
		object->setUnitImageInfo(object->getImageInfo().unitName, "Left", "Walk");
	}
	else
	{
		movetoRight(_futureRc, 2);
		object->setUnitImageInfo(object->getImageInfo().unitName, "Right", "Walk");
	}

}
