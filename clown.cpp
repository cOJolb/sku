#include "framework.h"
#include "clown.h"

C_clown::C_clown()
{
	unitImageInfo.unitName = "clown";
	unitImageInfo.unitFoward = "Right";
	unitImageInfo.unitState = "Idle";
	type = SKUL_TYPE::CLOWN;

	ani = ANIMATION->findAnimation(unitImageInfo.unitName + "RightIdle");
	ANIMATION->start(unitImageInfo.unitName + "RightIdle");
	ANIMATION->start(unitImageInfo.unitName + "LeftIdle");
}

C_clown::~C_clown()
{
}

HRESULT C_clown::init(vector2 _pt)
{
	pt = _pt;
    return S_OK;
}

void C_clown::release()
{
}

void C_clown::update()
{
	C_player::update();
}

void C_clown::render()
{
	C_player::render();
}
