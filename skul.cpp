#include "framework.h"
#include "skul.h"

C_skul::C_skul()
{
}

C_skul::~C_skul()
{
}

HRESULT C_skul::init()
{
	return S_OK;
}

void C_skul::release()
{
}

void C_skul::update(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
	if (isChange)
	{
		playerChange(_pt, _rc, _isLeft, _sInfo);
	}
	if (isPlayAtkA)
	{
		playerAttack(_pt, _rc, _isLeft, _sInfo, 0);
	}
	if (isPlayAtkB)
	{
		playerAttack(_pt, _rc, _isLeft, _sInfo, 1);
	}
	if (isPlaySkillA)
	{
		skillA(_pt, _rc, _isLeft, _sInfo);
	}
	if (isPlaySkillB)
	{
		skillB(_pt, _rc, _isLeft, _sInfo);
	}
	if (isPlayJumpAtk)
	{
		playerJumpAtk(_pt, _rc, _isLeft, _sInfo);
	}

}

void C_skul::render()
{
}

void C_skul::playerDashMove(RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
}

void C_skul::playerAttack(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo, int number)
{
}

void C_skul::playerJumpAtk(vector2 _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
}

void C_skul::skillA(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
}

void C_skul::skillB(vector2& _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
}

void C_skul::playerChange(vector2 _pt, RECT& _rc, bool _isLeft, S_skulInfo _sInfo)
{
}



bool C_skul::PlayAtkA()
{
	count = 0;
	isPlayAtkA = true;
	return true;
}

bool C_skul::PlayAtkB()
{
	count = 0;
	isPlayAtkB = true;
	return true;
}

bool C_skul::PlaySkillA()
{
	count = 0;
	isPlaySkillA = true;
	return true;
}

bool C_skul::PlaySkillB()
{
	count = 0;
	isPlaySkillB = true;
	return true;
}

bool C_skul::PlayJumpAtk()
{
	count = 0;
	isPlayJumpAtk = true;
	return true;
}

bool C_skul::PlayChange()
{
	count = 0;
	isChange = true;
	return true;
}

