#include "framework.h"
#include "BigEnt.h"

C_BigEnt::C_BigEnt()
{
}

C_BigEnt::C_BigEnt(vector2 _pt)
{
	pt = _pt;
	unitImageInfo.unitName = "BigEnt";
	unitImageInfo.unitFoward = "_";
	unitImageInfo.unitState = "Idle";
	type = UNIT_TYPE::BIGENT;
	collider = new C_collider(pt, { 60,88 });
	atkDelay = 80;
	maxHp = 50;
	hp = 50;
	count = 0;
	damage = 10;
	C_enemy::init();
	superArmor = true;
}

C_BigEnt::~C_BigEnt()
{
}

HRESULT C_BigEnt::init()
{
    return S_OK;
}

void C_BigEnt::release()
{
}

void C_BigEnt::update()
{
	C_enemy::update();
}

void C_BigEnt::render()
{
	C_enemy::render();
}
