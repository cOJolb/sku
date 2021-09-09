#include "framework.h"
#include "Bigknight.h"

C_Bigknight::C_Bigknight()
{
}

C_Bigknight::C_Bigknight(vector2 _pt)
{
	pt = _pt;
	unitImageInfo.unitName = "Bigknight";
	unitImageInfo.unitFoward = "Left";
	unitImageInfo.unitState = "Idle";
	type = UNIT_TYPE::BIGKNIGHT;
	collider = new C_collider(pt, { 60,70 });
	atkDelay = 180;
	maxHp = 50;
	hp = 50;
	count = 0;
	damage = 16;
	C_enemy::init();
	superArmor = true;
}

C_Bigknight::~C_Bigknight()
{
}

HRESULT C_Bigknight::init()
{
	return E_NOTIMPL;
}

void C_Bigknight::release()
{
}

void C_Bigknight::update()
{
	C_enemy::update();
}

void C_Bigknight::render()
{
	C_enemy::render();
}
