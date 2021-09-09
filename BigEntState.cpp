#include "framework.h"
#include "BigEntState.h"
#include "object.h"
#include "player.h"

BigEnt_Idle::BigEnt_Idle()
{
	stateType = STATE_TYPE::IDLE;
}

BigEnt_Idle::~BigEnt_Idle()
{
}

void BigEnt_Idle::enter()
{
	object = fsm->getObject();
	object->setUnitImageInfo(object->getImageInfo().unitName, "Left", "Idle");
	count = 0;
	object->setStart(true);
	object->setFrameRender(FRAME_TYPE::LOOP);
}

void BigEnt_Idle::update()
{
	count++;
	bool canAtk = (count >= object->getAtkDelay());
	if (inRange(400, PLAYERDATA->getPlayerData()->getPt()) && canAtk)
	{
		fsm->ChangeState(STATE_TYPE::ATTACK);
	}
}

void BigEnt_Idle::exit()
{
}

BigEnt_Trace::BigEnt_Trace()
{
	stateType = STATE_TYPE::TRACE;
}

BigEnt_Trace::~BigEnt_Trace()
{
}

void BigEnt_Trace::enter()
{
	object = fsm->getObject();
}

void BigEnt_Trace::update()
{
}

void BigEnt_Trace::exit()
{
}

BigEnt_Atk::BigEnt_Atk()
{
	stateType = STATE_TYPE::ATTACK;
}

BigEnt_Atk::~BigEnt_Atk()
{
}

void BigEnt_Atk::enter()
{
	object = fsm->getObject();
	if (crossRangeX(30, PLAYERDATA->getPlayerData()->getPt())) { atkType = 0; }
	else { atkType = 1; }
	switch (atkType)
	{
	case 0:
		object->setUnitImageInfo(object->getImageInfo().unitName, "Left", "Attack");
		object->setStart(true);
		
		object->setFrameRender(FRAME_TYPE::NORMAL);
		break;
	case 1:
		object->setUnitImageInfo(object->getImageInfo().unitName, "Left", "Attack2");
		object->setStart(true);
		object->setFrameMaxMin(0, 2);
		object->setFrameRender(FRAME_TYPE::RANGE);
		break;
	default:
		break;
	}
	delay = 0;
	//object->setFutureRc(_futureRc);

	//object->setFrameMaxMin(0, 2);
}

void BigEnt_Atk::update()
{
	delay++;
	switch (atkType)
	{
	case 0:
		if (delay == 40)
		{
			BULLET->fire({ object->getPt().x, object->getPt().y + 30 }, { 100,30 }, object->getDamage(), 0, PI / 2, 300, 10, "NONE", false, true, false);
		}
		if (delay == 100)
		{
			fsm->ChangeState(STATE_TYPE::IDLE);
		}
		break;
	case 1:
		if (delay == 150)
		{
			object->setFrameMaxMin(object->getMaxFrameX() - 2, 0);
			object->setFrameRender(FRAME_TYPE::RANGE);
		}
		if (delay == 180)
		{
			BULLET->fire(object->getPt(), { 15,15 }, 5, 5, PI / 2, 300, 500, "BigEnt",  false, true,false);
			BULLET->fire(object->getPt(), { 15,15 }, 5, 5, PI / 2 + PI / 3, 300, 500, "BigEnt", false, true, false);
			BULLET->fire(object->getPt(), { 15,15 }, 5, 5, PI / 2 + PI / 3 + PI / 3, 300, 500, "BigEnt", false, true, false);
			BULLET->fire(object->getPt(), { 15,15 }, 5, 5, PI + PI / 2, 300, 500, "BigEnt", false, true, false);
			BULLET->fire(object->getPt(), { 15,15 }, 5, 5, PI + PI / 2 + PI / 3, 300, 500, "BigEnt", false, true, false);
			BULLET->fire(object->getPt(), { 15,15 }, 5, 5, PI + PI / 2 + PI / 3 + PI / 3, 300, 500, "BigEnt", false, true, false);
		}
		if (delay == 200)
		{
			fsm->ChangeState(STATE_TYPE::IDLE);
		}
		break;
	default:
		break;
	}
}

void BigEnt_Atk::exit()
{
}

BigEnt_Die::BigEnt_Die()
{
	stateType = STATE_TYPE::DEAD;
}

BigEnt_Die::~BigEnt_Die()
{
}

void BigEnt_Die::enter()
{
}

void BigEnt_Die::update()
{
}

void BigEnt_Die::exit()
{
}

BigEnt_Damage::BigEnt_Damage()
{
	stateType = STATE_TYPE::DAMAGE;
}

BigEnt_Damage::~BigEnt_Damage()
{
}

void BigEnt_Damage::enter()
{
}

void BigEnt_Damage::update()
{
}

void BigEnt_Damage::exit()
{
}
