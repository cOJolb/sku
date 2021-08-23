#include "framework.h"
#include "Csmallfly.h"
#include "CStage.h"
#include "CMap.h"
#include "CObstacle.h"
Csmallfly::Csmallfly()
{
}

Csmallfly::~Csmallfly()
{
}

HRESULT Csmallfly::init(float x, float y)
{
	setAni(ANIMATION->findAnimation("smallflyani"));
	ANIMATION->start("smallflyani");

	RECT rc = RectMakeCenter(x, y, IMAGE->findImage("smallfly")->getFrameWidth(), IMAGE->findImage("smallfly")->getFrameHeight());
	hp = 8;

	CCharacter::init({ x,y }, // make pos
		RectMakeCenter(x, y, IMAGE->findImage("smallfly")->getFrameWidth(), IMAGE->findImage("smallfly")->getFrameHeight()), //rc
		{x, y }, { 30,30 }, //collider
		36,	//collider -> shadow distance
		{ x, y + shadowdistance }, { IMAGE->findImage("smallfly")->getFrameWidth(),IMAGE->findImage("smallfly")->getFrameWidth() / 3 }, // collider.shadow
		10);//hp
	IMAGE->addImage("shadowSmallfly", "images/shadow.bmp", colliderShadow->getSize().x, colliderShadow->getSize().y, true, RGB(255, 0, 255));

	setMonster_Type(MONSTER_TYPE::SMALLFLY);
	AI_init(this, monsterType);
	return S_OK;
}

void Csmallfly::release()
{
}

void Csmallfly::update()
{

	COLLISION->wallCollision(pt, { MAPSTARTX + TILEWIDTH, MAPSTARTY + TILEHEIGHT }, TILESIZEX - TILEWIDTH * 2, TILESIZEY - TILEHEIGHT * 2);
	rc = RectMakeCenter(pt, IMAGE->findImage("smallfly")->getFrameWidth(), IMAGE->findImage("smallfly")->getFrameHeight());
	collider->setPos({ RectX(rc), RectY(rc) });
	colliderShadow->setPos({ RectX(rc), RectY(rc) + shadowdistance });

	AI_update();
}

void Csmallfly::render()
{
	if (InputManager->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), collider->getPos().x - collider->getSize().x / 2,
			collider->getPos().y - collider->getSize().y / 2,
			collider->getPos().x + collider->getSize().x / 2,
			collider->getPos().y + collider->getSize().y / 2);
	}
	//RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);
	//IMAGE->render("shadowSmallfly", getMemDC(), rec.left, rec.top);

	/*RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);

	int hereIndex = (rec.left / TILEWIDTH - 1) + (rec.top / TILEHEIGHT - 1) * TILEX;
	if (hereIndex > 105) hereIndex = 6;
	bool ismoveable = (*STAGE->getCurStage()->getCurRoom()->getviObstacle(hereIndex))->getUnmovalbe();
	if (!ismoveable)
	{
		IMAGE->render("shadowSmallfly", getMemDC(), rec.left, rec.top);
	}*/
	RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);

	int hereIndex = (rec.left / TILEWIDTH - 1) + (rec.top / TILEHEIGHT - 1) * TILEX;
	if (hereIndex > 105) hereIndex = 6;
	bool isnotNone = (*STAGE->getCurStage()->getCurRoom()->getviObstacle(hereIndex))->getObjType() != OBJECT::OBJ_NONE;
	bool ispass = (*STAGE->getCurStage()->getCurRoom()->getviObstacle(hereIndex))->getPassBullet();
	if (isnotNone && ispass) {}
	else IMAGE->render("shadowSmallfly", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("smallfly")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
