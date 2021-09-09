#include "framework.h"
#include "littlebone.h"
#include "collision.h"
#include"enemy.h"
#include"fsm.h"
#include "item.h"
C_littlebone::C_littlebone()
{
	skulInfo.playerSpeed = 3;
	skulInfo.DashTerm = 10;
	skulInfo.playerDashSpeed = 6;
	skulInfo.DashTime = 34;
	skulInfo.playerJumpPower = 18;
	skulInfo.canDoubleDash = true;
	unitName = "skul";
	skulInfo.playerSize.x = 20;
	skulInfo.playerSize.y = 35;
	skulInfo.DashDelay = 50;
	skulInfo.haveTwoSkill = true;
	skulInfo.playerDamage = 10;

	skulInfo.atkDelay = 20;
	skulInfo.jumpAtkDelay = 30;
	skulInfo.skill1Delay = 5;
	skulInfo.skill2Delay = 10;
	skulInfo.changeDelay = 100;

	skulInfo.changeCoolTime = 200;
	skulInfo.atkCoolTime = 30;
	skulInfo.skill1CoolTime = 50;
	skulInfo.skill2CoolTime = 50;
	type = SKUL_TYPE::SKUL;
}

C_littlebone::~C_littlebone()
{
}



void C_littlebone::playerChange(vector2 _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	count++;
	if (_isLeft){movetoLeft(_rc, _sInfo.playerSpeed * 2 / 3);}
	else { movetoRight(_rc, _sInfo.playerSpeed * 2 / 3); }
	if (count % 5 == 0)
	{
		BULLET->fire(_pt, { 60,60 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, false, _isLeft);
	}
	if (count >= _sInfo.changeDelay) { isChange = false; }
}

void C_littlebone::playerDashMove(RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	if (_isLeft) { movetoLeft(_rc, _sInfo.playerDashSpeed); }
	else { movetoRight(_rc, _sInfo.playerDashSpeed); }
}

void C_littlebone::playerAttack(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo, int number)
{
	switch (number)
	{
	case 0:
		if (_isLeft) 
		{
			movetoLeft(_rc, 10);
			BULLET->fire({ _pt.x - 30, _pt.y  }, { 40,50 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, false, _isLeft); 
		}
		else 
		{ 
			movetoRight(_rc, 10);
			BULLET->fire({ _pt.x + 30, _pt.y  }, { 40,50 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, false, _isLeft); 
		}
		isPlayAtkA = false;
		break;
	case 1:
		if (_isLeft) 
		{
			movetoLeft(_rc, 10);
			BULLET->fire({ _pt.x - 30, _pt.y }, { 40,50 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, false, _isLeft);
		}
		else 
		{ 
			movetoRight(_rc, 10);
			BULLET->fire({ _pt.x + 30, _pt.y }, { 40,50 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, false, _isLeft);
		}
		isPlayAtkB = false;
		break;
	default:
		break;
	}
}

void C_littlebone::playerJumpAtk(vector2 _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	if (_isLeft) { BULLET->fire({ _pt.x - 30, _pt.y +30 }, { 40,50 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, false, _isLeft); }
	else { BULLET->fire({ _pt.x + 30, _pt.y+30 }, { 40,50 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, false, _isLeft); }
	isPlayJumpAtk = false;
}

void C_littlebone::skillA(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	ITEM->respawnActiveItem(ACTIVEITEM::LITTLEBONEHEAD, _pt);
	isPlaySkillA = false;
}

void C_littlebone::skillB(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	for (int i = 0; i < ITEM->getvItem().size(); i++)
	{
		bool headOk = (*ITEM->getviItem(i))->getActiveType() == ACTIVEITEM::LITTLEBONEHEAD;
		if (headOk)
		{
			_rc = RectMakeCenter((*ITEM->getviItem(i))->getPt(),_sInfo.playerSize.x,_sInfo.playerSize.y);
			ITEM->itemRemove(i);
			break;
		}
	}
	isPlaySkillB = false;
}

bool C_littlebone::PlayJumpAtk()
{
	count = 0;
	isPlayJumpAtk = true;
	return false;
}
