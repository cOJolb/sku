#include "framework.h"
#include "CHost.h"
#include"BulletManager.h"
CHost::CHost()
{
}

CHost::~CHost()
{
}

HRESULT CHost::init(float x, float y)
{

	setAni(ANIMATION->findAnimation("hostidle"));
	ANIMATION->start("hostidle");

	CCharacter::init({ x,y }, // make pos
		RectMakeCenter(x, y, IMAGE->findImage("host")->getFrameWidth(), IMAGE->findImage("host")->getFrameHeight()), //rc
		{ x, y }, { 50,50 }, //collider
		27,	//collider -> shadow distance
		{ x, y + shadowdistance }, { IMAGE->findImage("host")->getFrameWidth(),IMAGE->findImage("host")->getFrameWidth() / 3 }, // collider.shadow
		7);//hp
	IMAGE->addImage("shadowHost", "images/shadow.bmp", colliderShadow->getSize().x, colliderShadow->getSize().y, true, RGB(255, 0, 255));

	setMonster_Type(MONSTER_TYPE::HOST);
	AI_init(this, monsterType);

	return S_OK;
}

void CHost::release()
{
}

void CHost::update()
{
	AI_update();
	collider->setPos({ RectX(rc), RectY(rc)});
	colliderShadow->setPos({ RectX(rc), RectY(rc) + shadowdistance });
	foward = COLLISION->whereAreYouGoing(prevPt, colliderShadow->getPos());
}

void CHost::render()
{
	if (InputManager->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), collider->getPos().x - collider->getSize().x / 2,
			collider->getPos().y - collider->getSize().y / 2,
			collider->getPos().x + collider->getSize().x / 2,
			collider->getPos().y + collider->getSize().y / 2);
	}
	RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);
	IMAGE->render("shadowHost", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("host")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());

}

