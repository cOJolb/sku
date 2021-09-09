#include "framework.h"
#include "clown.h"

C_clown::C_clown()
{
	skulInfo.playerSpeed = 3;
	skulInfo.DashTerm = 10;
	skulInfo.playerDashSpeed = 6;
	skulInfo.DashTime = 34;
	skulInfo.playerJumpPower = 18;
	skulInfo.canDoubleDash = true;
	unitName = "clown";
	skulInfo.playerSize.x = 20;
	skulInfo.playerSize.y = 40;


	skulInfo.DashDelay = 50;
	skulInfo.haveTwoSkill = false;
	skulInfo.playerDamage = 10;
	skulInfo.skill1Delay = 50;
	skulInfo.skill2Delay = 50;
	skulInfo.changeDelay = 30;

	skulInfo.atkDelay = 25;
	skulInfo.jumpAtkDelay = 30;
	skulInfo.changeCoolTime = 100;
	skulInfo.atkCoolTime = 10;
	skulInfo.skill1CoolTime = 150;
	skulInfo.skill2CoolTime = 50;
	type = SKUL_TYPE::CLOWN;
}

C_clown::~C_clown()
{
}



void C_clown::playerChange(vector2 _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	if (_isLeft)
	{
		movetoRight(_rc, 20);
		BULLET->fire({ _pt.x, _pt.y + 5 }, { 10,8 }, _sInfo.playerDamage, 8, PI, 500, 500, "clown", true, true, _isLeft);
		BULLET->fire({ _pt.x, _pt.y - 5 }, { 10,8 }, _sInfo.playerDamage, 8, PI, 500, 500, "clown", true, true, _isLeft);
		movetoRight(_rc, 20);
	}
	else
	{
		movetoLeft(_rc, 20);
		BULLET->fire({ _pt.x, _pt.y + 5 }, { 10,8 }, _sInfo.playerDamage, 8, 0, 500, 500, "clown", true, true, _isLeft);
		BULLET->fire({ _pt.x, _pt.y - 5 }, { 10,8 }, _sInfo.playerDamage, 8, 0, 500, 500, "clown", true, true, _isLeft);
		movetoLeft(_rc, 20);
	}
	isChange = false;
}

void C_clown::playerDashMove(RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	if (_isLeft) { movetoLeft(_rc, _sInfo.playerDashSpeed); }
	else { movetoRight(_rc, _sInfo.playerDashSpeed); }
}

void C_clown::playerAttack(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo, int number)
{
	switch (number)
	{
	case 0:
		if (_isLeft) { BULLET->fire(_pt, { 10,8 }, _sInfo.playerDamage, 8, PI, 500, 500, "clown", true, true, _isLeft); }
		else { BULLET->fire(_pt, { 10,8 }, _sInfo.playerDamage, 8, 0, 500, 500, "clown", true, true, _isLeft); }
		isPlayAtkA = false;
		break;
	case 1:
		if (_isLeft)
		{
			BULLET->fire({_pt.x, _pt.y + 5}, { 10,8 }, _sInfo.playerDamage, 8, PI, 500, 500, "clown", true, true, _isLeft);
			BULLET->fire({ _pt.x, _pt.y - 5 }, { 10,8 }, _sInfo.playerDamage, 8, PI, 500, 500, "clown", true, true, _isLeft);
			movetoRight(_rc, 10);
		}
		else 
		{ 
			BULLET->fire({ _pt.x, _pt.y + 5 }, { 10,8 }, _sInfo.playerDamage, 8, 0, 500, 500, "clown", true, true, _isLeft);
			BULLET->fire({ _pt.x, _pt.y - 5 }, { 10,8 }, _sInfo.playerDamage, 8, 0, 500, 500, "clown", true, true, _isLeft);
			movetoLeft(_rc, 10);
		}
		isPlayAtkB = false;
		break;
	default:
		break;
	}
	
}

void C_clown::playerJumpAtk(vector2 _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	if (_isLeft) { BULLET->fire(_pt, { 10,8 }, _sInfo.playerDamage, 8, PI, 500, 500, "clown", true, true, _isLeft); }
	else { BULLET->fire(_pt, { 10,8 }, _sInfo.playerDamage, 8, 0, 500, 500, "clown", true, true, _isLeft); }
	isPlayJumpAtk = false;
}

void C_clown::skillA(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	count++;
	if (count == 15)
	{
		if (_isLeft) { movetoRight(_rc, 20); }
		else { movetoLeft(_rc, 20); }
	}
	if (count == 30)
	{
		if (_isLeft)
		{
			movetoRight(_rc, 20);
			BULLET->fire({ _pt.x, _pt.y + 5 }, { 10,8 }, _sInfo.playerDamage, 8, PI, 500, 500, "clown", true, true, _isLeft);
			BULLET->fire({ _pt.x, _pt.y - 5 }, { 10,8 }, _sInfo.playerDamage, 8, PI, 500, 500, "clown", true, true, _isLeft);
			BULLET->fire({ _pt.x, _pt.y }, { 10,8 }, _sInfo.playerDamage, 8, PI, 500, 500, "clown", true, true, _isLeft);
			movetoRight(_rc, 20);
		}
		else
		{
			movetoLeft(_rc, 20);
			BULLET->fire({ _pt.x, _pt.y + 5 }, { 10,8 }, _sInfo.playerDamage, 8, 0, 500, 500, "clown", true, true, _isLeft);
			BULLET->fire({ _pt.x, _pt.y - 5 }, { 10,8 }, _sInfo.playerDamage, 8, 0, 500, 500, "clown", true, true, _isLeft);
			BULLET->fire({ _pt.x, _pt.y }, { 10,8 }, _sInfo.playerDamage, 8, 0, 500, 500, "clown", true, true, _isLeft);
			movetoLeft(_rc, 20);
		}
	}
	if (count >= skulInfo.skill1Delay - 5)
	{
		isPlaySkillA = false;
		count = 0;
	}
}

void C_clown::skillB(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
}

bool C_clown::PlayJumpAtk()
{
	count = 0;
	isPlayJumpAtk = true;
	return false;
}
