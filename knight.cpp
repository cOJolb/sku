#include "framework.h"
#include "knight.h"

C_knight::C_knight()
{
	C_enemy::init();
}

C_knight::C_knight(vector2 _pt)
{
	pt = _pt;
	unitImageInfo.unitName = "knight";
	unitImageInfo.unitFoward = "Right";
	unitImageInfo.unitState = "Idle";
	type = UNIT_TYPE::KNIGHT;
	collider = new C_collider(pt, { 20,20 });
	atkDelay = 50;
	maxHp = 50;
	hp = 50;
	count = 0;
	C_enemy::init();
}

C_knight::~C_knight()
{
}

HRESULT C_knight::init()
{
	return S_OK;
}

void C_knight::release()
{
}

void C_knight::update()
{
	C_enemy::update();
	
	if (isStart)
	{
		frameX = 0;
		count = 0;
		isStart = false;
	}
	if (unitImageInfo.unitState == "Walk")
	{
		countUpLoop(frameX, 0, 5,count,10);
	}
	else if (unitImageInfo.unitState == "Attack")
	{
		countUp(frameX, 3, count, 10);
	}
}

void C_knight::render()
{
	C_enemy::render();
}
