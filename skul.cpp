#include "framework.h"
#include "skul.h"

C_skul::C_skul()
{
	unitImageInfo.unitName = "skul";
	unitImageInfo.unitFoward = "Right";
	unitImageInfo.unitState = "Idle";
	type = SKUL_TYPE::SKUL;

	ani = ANIMATION->findAnimation(unitImageInfo.unitName + "RightIdle");
	ANIMATION->start(unitImageInfo.unitName + "RightIdle");
	ANIMATION->start(unitImageInfo.unitName + "LeftIdle");
}

C_skul::~C_skul()
{
}

HRESULT C_skul::init(vector2 _pt)
{
	pt = _pt;
	return S_OK;
}

void C_skul::release()
{
}

void C_skul::update()
{
	C_player::update();
}

void C_skul::render()
{
	C_player::render();
}
