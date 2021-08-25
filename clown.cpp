#include "framework.h"
#include "clown.h"

C_clown::C_clown()
{
	unitName = "clown";
	unitFoward = "Right";
	unitState = "Idle";
	type = SKUL_TYPE::CLOWN;

	ani = ANIMATION->findAnimation(unitName + "RightIdle");
	ANIMATION->start(unitName + "RightIdle");
	ANIMATION->start(unitName + "LeftIdle");
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
	C_player::update();
}

void C_clown::render()
{
	C_player::render();
}
