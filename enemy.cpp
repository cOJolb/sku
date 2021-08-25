#include "framework.h"
#include "enemy.h"

C_enemy::C_enemy()
{
}

C_enemy::~C_enemy()
{
}

HRESULT C_enemy::init()
{
    return S_OK;
}

void C_enemy::release()
{
}

void C_enemy::update()
{
	Gravity();
	isLand();
	isClogged();
	collider->setPos(pt);
	ptUpdate();
	ani = ANIMATION->findAnimation(unitName + unitFoward + unitState);
}

void C_enemy::render()
{
	RECT rec = RectMakeCenter(pt, 20, 20);
	Rectangle(getMemDC(), rec.left, rec.top, rec.right, rec.bottom);


	IMAGE->findImage(unitName+unitState)->aniRender(getMemDC(), pt.x - IMAGE->findImage(unitName+unitState)->getFrameWidth() / 2, pt.y - IMAGE->findImage(unitName + unitState)->getFrameHeight() / 2, ani);
}
