#include "framework.h"
#include "knightState.h"
#include "object.h"

knight_Idle::knight_Idle()
{
	stateType = STATE_TYPE::IDLE;
}

knight_Idle::~knight_Idle()
{
}

void knight_Idle::enter()
{
	object = fsm->getObject();
	object->setUnitImageInfo(object->getImageInfo().unitName, "Left", "Idle");
	count = 0;
}

void knight_Idle::update()
{
	if (inRange(200, PLAYERDATA->getPlayerData().playerPt))
	{
		fsm->ChangeState(STATE_TYPE::TRACE);
	}
	
}

void knight_Idle::exit()
{
}


knight_Trace::knight_Trace()
{
	stateType = STATE_TYPE::TRACE;
}

knight_Trace::~knight_Trace()
{
}

void knight_Trace::enter()
{
	object = fsm->getObject();
}

void knight_Trace::update()
{
	if (inRange(50, PLAYERDATA->getPlayerData().playerPt))
	{
		fsm->ChangeState(STATE_TYPE::ATTACK);
	}
	else if (inRange(200, PLAYERDATA->getPlayerData().playerPt))
	{
		move(isLeft(PLAYERDATA->getPlayerData().playerPt));
	}
	else move();
}

void knight_Trace::exit()
{
}


knight_Atk::knight_Atk()
{
	stateType = STATE_TYPE::ATTACK;
}

knight_Atk::~knight_Atk()
{
}

void knight_Atk::enter()
{
}

void knight_Atk::update()
{
}

void knight_Atk::exit()
{
}


knight_Die::knight_Die()
{
	stateType = STATE_TYPE::DEAD;
}

knight_Die::~knight_Die()
{
}

void knight_Die::enter()
{
}

void knight_Die::update()
{
}

void knight_Die::exit()
{
}

knight_Damage::knight_Damage()
{
	stateType = STATE_TYPE::DAMAGE;
}

knight_Damage::~knight_Damage()
{
}

void knight_Damage::enter()
{
}

void knight_Damage::update()
{
}

void knight_Damage::exit()
{
}
