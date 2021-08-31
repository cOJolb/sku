#include "framework.h"
#include "clown.h"

C_clown::C_clown()
{
	skulInfo.playerSpeed = 5;
	skulInfo.DashTerm = 10;
	skulInfo.playerDashSpeed = 8;
	skulInfo.DashTime = 34;
	skulInfo.playerJumpPower = 20;
	skulInfo.canDoubleDash = true;
	skulInfo.playerSize.x = 20;
	skulInfo.playerSize.y = 20;
	unitName = "clown";
}

C_clown::~C_clown()
{
}

HRESULT C_clown::init()
{
	return S_OK;
}

void C_clown::release()
{
}

void C_clown::update()
{
}

void C_clown::render()
{
}

void C_clown::playerAttack()
{
}

void C_clown::playerDashMove()
{
}

void C_clown::skillA()
{
}

void C_clown::skillB()
{
}
