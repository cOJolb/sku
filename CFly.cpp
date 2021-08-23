#include "framework.h"
#include "CFly.h"
#include "CStage.h"
#include "CMap.h"
#include "CObstacle.h"

CFly::CFly()
{

}

CFly::~CFly()
{
}

HRESULT CFly::init(float x, float y)
{
	setAni(ANIMATION->findAnimation("rightfly"));
	ANIMATION->start("rightfly");

	CCharacter::init({ x,y }, // make pos
		RectMakeCenter(x, y, IMAGE->findImage("fly")->getFrameWidth(), IMAGE->findImage("fly")->getFrameHeight()), //rc
		{ x, y }, { 50,50 }, //collider
		30,	//collider -> shadow distance
		{ x, y + shadowdistance }, { IMAGE->findImage("fly")->getFrameWidth(),IMAGE->findImage("fly")->getFrameWidth() / 3 }, // collider.shadow
		8);//hp
	IMAGE->addImage("shadowFly", "images/shadow.bmp", colliderShadow->getSize().x, colliderShadow->getSize().y, true, RGB(255, 0, 255));

	setMonster_Type(MONSTER_TYPE::FLY);

	AI_init(this, monsterType);
	//if (!SOUND->isPlaySound("flysound")) { SOUND->play("flysound"); }
	return S_OK;
}

void CFly::release()
{
}

void CFly::update()
{
	AI_update();
	COLLISION->wallCollision(pt, { MAPSTARTX + TILEWIDTH, MAPSTARTY + TILEHEIGHT }, TILESIZEX - TILEWIDTH * 2, TILESIZEY - TILEHEIGHT * 2);
	rc = RectMakeCenter(pt, IMAGE->findImage("fly")->getFrameWidth(), IMAGE->findImage("fly")->getFrameHeight());
	collider->setPos({ RectX(rc), RectY(rc) });
	colliderShadow->setPos({ RectX(rc), RectY(rc) + shadowdistance });
	//if (SOUND->isPauseSound("flysound") && !SOUND->isPlaySound("flysound")) { SOUND->play("flysound"); }
	
}

void CFly::render()
{
	if (InputManager->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), collider->getPos().x - collider->getSize().x / 2,
			collider->getPos().y - collider->getSize().y / 2,
			collider->getPos().x + collider->getSize().x / 2,
			collider->getPos().y + collider->getSize().y / 2);
	}
	RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);

	int hereIndex = (rec.left / TILEWIDTH - 1) + (rec.top / TILEHEIGHT - 1) * TILEX;
	if (hereIndex > 105) hereIndex = 6;
	bool isnotNone = (*STAGE->getCurStage()->getCurRoom()->getviObstacle(hereIndex))->getObjType() != OBJECT::OBJ_NONE;
	bool ispass = (*STAGE->getCurStage()->getCurRoom()->getviObstacle(hereIndex))->getPassBullet();
	if (isnotNone && ispass){}
	else IMAGE->render("shadowFly", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("fly")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
