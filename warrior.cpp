#include "framework.h"
#include "warrior.h"

#include "collision.h"
#include"enemy.h"
#include"fsm.h"
C_warrior::C_warrior()
{
	skulInfo.playerSpeed = 3;
	skulInfo.DashTerm = 10;
	skulInfo.playerDashSpeed = 6;
	skulInfo.DashTime = 34;
	skulInfo.playerJumpPower = 18;
	skulInfo.canDoubleDash = false;
	unitName = "warrior";
	skulInfo.playerSize.x = 20;
	skulInfo.playerSize.y = 40;
	skulInfo.atkDelay = 50;
	skulInfo.jumpAtkDelay = 50;
	skulInfo.DashDelay = 50;
	skulInfo.haveTwoSkill = false;
	skulInfo.playerDamage = 10;
	skulInfo.skill1Delay = 50;
	skulInfo.skill2Delay = 50;
	skulInfo.changeDelay = 30;


	skulInfo.changeCoolTime = 100;
	skulInfo.atkCoolTime = 15;
	skulInfo.skill1CoolTime = 150;
	skulInfo.skill2CoolTime = 50;
	type = SKUL_TYPE::WARRIOR;
}

C_warrior::~C_warrior()
{
}



void C_warrior::playerChange(vector2 _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	count++;
	if (count % 3 == 0)
	{
		if (_isLeft)
		{
			movetoLeft(_rc, 25);
			BULLET->fire({ RectX(_rc) - 50, RectY(_rc) }, { 24,40 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, true, _isLeft);
		}
		else
		{
			movetoRight(_rc, 25);
			BULLET->fire({ RectX(_rc) + 50, RectY(_rc) }, { 24,40 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, true, _isLeft);
		}
	}
	if (count >= skulInfo.changeDelay - 2)
	{
		isChange = false;
		count = 0;
	}
}

void C_warrior::playerDashMove(RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	delay++;
	if (delay % 5 == 0)
	{
		BULLET->fire({ RectX(_rc), RectY(_rc) }, { 20,40 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, true, _isLeft);
	}
	if (delay > 50) { delay = 0; }

	if (_isLeft) 
	{ 
		movetoLeft(_rc, _sInfo.playerDashSpeed); 
	}
	else 
	{
		movetoRight(_rc, _sInfo.playerDashSpeed); 
	}
}

void C_warrior::playerAttack(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo, int number)
{
	switch (number)
	{
	case 0:
		if (_isLeft) { BULLET->fire({ _pt.x - 30, _pt.y }, { 50,70 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, false, _isLeft); }
		else { BULLET->fire({ _pt.x + 30, _pt.y }, { 50,70 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, false, _isLeft); }
		isPlayAtkA = false;
		break;
	case 1:
		if (_isLeft) { BULLET->fire({ _pt.x - 30, _pt.y }, { 50,70 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, false, _isLeft); }
		else { BULLET->fire({ _pt.x + 30, _pt.y }, { 50,70 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, false, _isLeft); }
		isPlayAtkB = false;
		break;
	default:
		break;
	}
}

void C_warrior::playerJumpAtk(vector2 _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	delay++;
	if (delay == 40)
	{
		if (_isLeft) { BULLET->fire({ _pt.x - 30, _pt.y }, { 100,100 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, false, _isLeft); }
		else { BULLET->fire({ _pt.x + 30, _pt.y }, { 100,100 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, false, _isLeft); }
	}
	else if (delay > 40)
	{
		delay = 0;
		isPlayJumpAtk = false;
	}
}

void C_warrior::skillA(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	count++;
	if (count == 10)
	{
		if (_isLeft)
		{
			movetoLeft(_rc, 25);
			BULLET->fire({ RectX(_rc)-50, RectY(_rc) }, { 50,40 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, true, _isLeft);
		}
		else
		{
			movetoRight(_rc, 25);
			BULLET->fire({ RectX(_rc) + 50, RectY(_rc) }, { 50,40 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, true, _isLeft);
		}
	}
	if (count == 40)
	{
		if (_isLeft)
		{
			BULLET->fire({ RectX(_rc) - 50, RectY(_rc) }, { 70,100 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, true, _isLeft);
		}
		else
		{
			BULLET->fire({ RectX(_rc) + 50, RectY(_rc) }, { 70,100 }, _sInfo.playerDamage, 0, 0, 100, 1, "NONE", true, true, _isLeft);
		}
	}
	if (count >= skulInfo.skill1Delay-5) 
	{ 
		isPlaySkillA = false;
		count = 0; 
	}
}

void C_warrior::skillB(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{

}

