#include "framework.h"
#include "CHopper.h"
#include "CStage.h"
#include "CMap.h"
#include "CObstacle.h"

CHopper::CHopper()
{
}

CHopper::~CHopper()
{
}

HRESULT CHopper::init(float x, float y)
{
	setAni(ANIMATION->findAnimation("idlehopper"));

	CCharacter::init({ x,y }, // make pos
		RectMakeCenter(x, y, IMAGE->findImage("hopper")->getFrameWidth(), IMAGE->findImage("hopper")->getFrameHeight()), //rc
		{ x, y }, { 50,50 }, //collider
		30,	//collider -> shadow distance
		{ x, y + shadowdistance }, { IMAGE->findImage("hopper")->getFrameWidth(),IMAGE->findImage("hopper")->getFrameWidth() / 3 }, // collider.shadow
		6);//hp
	IMAGE->addImage("shadowHopper", "images/shadow.bmp", colliderShadow->getSize().x, colliderShadow->getSize().y, true, RGB(255, 0, 255));

	setMonster_Type(MONSTER_TYPE::HOPPER);
	AI_init(this, monsterType);

	return S_OK;
}

void CHopper::release()
{
}

void CHopper::update()
{
	AI_update();
	/*vector2 sPt = { pt.x, pt.y + shadowdistance };
	if (COLLISION->wallCollision(sPt, { MAPSTARTX + TILEWIDTH, MAPSTARTY + TILEHEIGHT }, TILESIZEX - TILEWIDTH * 2, TILESIZEY - TILEHEIGHT * 2))
	{
		colliderShadow->setPos(sPt);
	}
	else colliderShadow->setPos({ RectX(rc), RectY(rc) + shadowdistance });
	if (COLLISION->wallCollision(pt, { MAPSTARTX + TILEWIDTH, MAPSTARTY + TILEHEIGHT }, TILESIZEX - TILEWIDTH * 2, TILESIZEY - TILEHEIGHT * 2))
	{
		shadowdistance = 10;
	}
	

	rc = RectMakeCenter(pt, IMAGE->findImage("hopper")->getFrameWidth(), IMAGE->findImage("hopper")->getFrameHeight());

	collider->setPos({ RectX(rc), RectY(rc) });*/

	//vector2 rcPt;
	//rcPt.x = RectX(rc);
	//rcPt.y = RectY(rc) + shadowdistance;
	//foward = COLLISION->whereAreYouGoing(prevPt, rcPt);
	//if (COLLISION->wallCollision(rcPt, { MAPSTARTX + TILEWIDTH, MAPSTARTY + TILEHEIGHT }, TILESIZEX - TILEWIDTH * 2, TILESIZEY - TILEHEIGHT * 2))
	//{
	//	shadowdistance = 10;
	//}
	//else if (shadowdistance < 30)
	//{
	//	if (COLLISION->tileCollision(STAGE->getCurStage()->getCurRoom(), rcPt, prevPt, foward, 0))
	//	{
	//		shadowdistance = 10;
	//	}
	//}
	//collider->setPos({ rcPt.x, rcPt.y - shadowdistance });
	//colliderShadow->setPos(rcPt);
	//rc = RectMakeCenter(collider->getPos(), IMAGE->findImage("hopper")->getFrameWidth(), IMAGE->findImage("hopper")->getFrameHeight());

	//AI_update();

	//AI_update();

	collider->setPos({ RectX(rc), RectY(rc) });
	colliderShadow->setPos({ RectX(rc), RectY(rc) + shadowdistance });
	//foward = COLLISION->whereAreYouGoing(prevPt, colliderShadow->getPos());
}

void CHopper::render()
{
	if (InputManager->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), collider->getPos().x - collider->getSize().x / 2,
			collider->getPos().y - collider->getSize().y / 2,
			collider->getPos().x + collider->getSize().x / 2,
			collider->getPos().y + collider->getSize().y / 2);
	}

	//RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);
	////IMAGE->render("shadowHopper", getMemDC(), rec.left, rec.top);
	RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);

	int hereIndex = (rec.left / TILEWIDTH - 1) + (rec.top / TILEHEIGHT - 1) * TILEX;
	if (hereIndex > 105) hereIndex = 6;
	bool ismoveable = (*STAGE->getCurStage()->getCurRoom()->getviObstacle(hereIndex))->getUnmovalbe();
	if (!ismoveable)
	{
		IMAGE->render("shadowHopper", getMemDC(), rec.left, rec.top);
	}
	IMAGE->findImage("hopper")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
}
