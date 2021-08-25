#include "framework.h"
#include "skul.h"

C_skul::C_skul()
{
	unitName = "skul";
	unitFoward = "Right";
	unitState = "Idle";
	type = SKUL_TYPE::SKUL;

	ani = ANIMATION->findAnimation(unitName + "RightIdle");
	ANIMATION->start(unitName + "RightIdle");
	ANIMATION->start(unitName + "LeftIdle");
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

void C_skul::update()
{
	C_player::update();
}

void C_skul::render()
{
	C_player::render();
}
