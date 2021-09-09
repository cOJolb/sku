#include "framework.h"
#include "BigknightState.h"
#include "object.h"
#include "player.h"

Bigknight_Idle::Bigknight_Idle()
{
	stateType = STATE_TYPE::IDLE;
}

Bigknight_Idle::~Bigknight_Idle()
{
}

void Bigknight_Idle::enter()
{
	object = fsm->getObject();
	object->setUnitImageInfo(object->getImageInfo().unitName, "Left", "Idle");
	object->setFrameRender(FRAME_TYPE::LOOP);
	count = 0;
}

void Bigknight_Idle::update()
{
	if (inRange(200, PLAYERDATA->getPlayerData()->getPt()))
	{
		fsm->ChangeState(STATE_TYPE::TRACE);
	}

}

void Bigknight_Idle::exit()
{
}


Bigknight_Trace::Bigknight_Trace()
{
	stateType = STATE_TYPE::TRACE;
}

Bigknight_Trace::~Bigknight_Trace()
{
}

void Bigknight_Trace::enter()
{
	object = fsm->getObject();
	object->setFrameRender(FRAME_TYPE::LOOP);
}

void Bigknight_Trace::update()
{
	if (inRange(80, PLAYERDATA->getPlayerData()->getPt()))
	{
		fsm->ChangeState(STATE_TYPE::ATTACK);
	}
	else if (inRange(200, PLAYERDATA->getPlayerData()->getPt()))
	{
		move(isLeft(PLAYERDATA->getPlayerData()->getPt()));
	}
	else move();
	object->setFutureRc(_futureRc);

}

void Bigknight_Trace::exit()
{
}


Bigknight_Atk::Bigknight_Atk()
{
	stateType = STATE_TYPE::ATTACK;
}

Bigknight_Atk::~Bigknight_Atk()
{
}

void Bigknight_Atk::enter()
{
	object = fsm->getObject();
	foward = isLeft(PLAYERDATA->getPlayerData()->getPt());
	if (crossRangeX(80, PLAYERDATA->getPlayerData()->getPt()) && !skillA ) { atkType = 0; }
	else { atkType = 1; }
	switch (atkType)
	{
	case 0:
		skillA = true;
		if (foward)
		{
			object->setUnitImageInfo(object->getImageInfo().unitName, "Left", "Attack2");
			object->setStart(true);
		}
		else
		{
			object->setUnitImageInfo(object->getImageInfo().unitName, "Right", "Attack2");
			object->setStart(true);
		}
		object->setFrameRender(FRAME_TYPE::FIX);
		break;
	case 1:
		skillA = false;
		if (foward)
		{
			object->setUnitImageInfo(object->getImageInfo().unitName, "Left", "Attack");
			object->setStart(true);
		}
		else
		{
			object->setUnitImageInfo(object->getImageInfo().unitName, "Right", "Attack");
			object->setStart(true);
		}
		object->setFrameRender(FRAME_TYPE::NORMAL);
		break;
	default:
		break;
	}
	
	delay = 0;
	object->setFutureRc(_futureRc);
}

void Bigknight_Atk::update()
{
	delay++;
	switch (atkType)
	{
	case 0:
		if (delay == 100)
		{
			object->setFrameX(1);
			object->setFrameRender(FRAME_TYPE::FIX);
		}
		if (delay > 100)
		{
			if (delay % 5 == 0)
			{
				BULLET->fire(object->getPt(), { 80,60 }, object->getDamage() / 2, 0, 0, 150, 1, "NONE", false, true, false);
			}
			_futureRc = RectMakeCenter(object->getPt(), object->getCollider()->getSize().x, object->getCollider()->getSize().y);
			count++;
			if (count > movetime)
			{
				count = 0;
				movetime = 50;
			}

			if (foward)
			{
				movetoLeft(_futureRc, 4);
				object->setFutureRc(_futureRc);
			}
			else
			{
				movetoRight(_futureRc, 4);
				object->setFutureRc(_futureRc);
			}
			
		}
		if (delay == 120)
		{
			fsm->ChangeState(STATE_TYPE::IDLE);
		}
		
		break;
	case 1:
		if (delay == 20)
		{
			if (foward)
			{
				BULLET->fire({ object->getPt().x - 30,object->getPt().y }, { 80,60 }, object->getDamage(), 0, 0, 150, 5, "NONE", false, true, false);
			}
			else
			{
				BULLET->fire({ object->getPt().x + 30,object->getPt().y }, { 80,60 }, object->getDamage(), 0, 0, 150, 5, "NONE", false, true, false);
			}
		}
		break;
	default:
		break;
	}
	if (delay > object->getAtkDelay())
	{
		fsm->ChangeState(STATE_TYPE::IDLE);
	}
	//object->setFutureRc(_futureRc);
}

void Bigknight_Atk::exit()
{
}


Bigknight_Die::Bigknight_Die()
{
	stateType = STATE_TYPE::DEAD;

}

Bigknight_Die::~Bigknight_Die()
{
}

void Bigknight_Die::enter()
{
	object = fsm->getObject();
	object->setFrameRender(FRAME_TYPE::NORMAL);
}

void Bigknight_Die::update()
{
}

void Bigknight_Die::exit()
{
}

Bigknight_Damage::Bigknight_Damage()
{
	stateType = STATE_TYPE::DAMAGE;

}

Bigknight_Damage::~Bigknight_Damage()
{
}

void Bigknight_Damage::enter()
{
	object = fsm->getObject();
	foward = isLeft(PLAYERDATA->getPlayerData()->getPt());
	/*if (foward)
	{
		
	}
	else
	{
		
	}

	delay = 0;*/
	object->setFrameRender(FRAME_TYPE::NORMAL);
}

void Bigknight_Damage::update()
{
	delay++;

	if (delay > object->getAtkDelay())
	{
		fsm->ChangeState(STATE_TYPE::IDLE);
	}
}

void Bigknight_Damage::exit()
{
}
