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
	AI_init(this,type);
	ani = ANIMATION->findAnimation(unitImageInfo.unitName + "RightIdle");
	ANIMATION->start(unitImageInfo.unitName + "RightIdle");
	ANIMATION->start(unitImageInfo.unitName + "LeftIdle");
    return S_OK;
}

void C_enemy::release()
{
}

void C_enemy::update()
{
	AI_update();
	Gravity();
	isLand();
	isClogged();
	collider->setPos(pt);
	ptUpdate();
	ani = ANIMATION->findAnimation(unitImageInfo.unitName + unitImageInfo.unitFoward + unitImageInfo.unitState);
}

void C_enemy::render()
{
	RECT rec = RectMakeCenter(pt, 20, 20);
	Rectangle(getMemDC(), rec.left, rec.top, rec.right, rec.bottom);

	IMAGE->findImage(unitImageInfo.unitName+ unitImageInfo.unitState)->aniRender(getMemDC(), pt.x - IMAGE->findImage(unitImageInfo.unitName+ unitImageInfo.unitState)->getFrameWidth() / 2, pt.y - IMAGE->findImage(unitImageInfo.unitName + unitImageInfo.unitState)->getFrameHeight() / 2, ani);
}
