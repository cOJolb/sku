#include "framework.h"
#include "CGurdy.h"

CGurdy::CGurdy()
{

}

CGurdy::~CGurdy()
{
	SAFE_DELETE(anibody);
}

HRESULT CGurdy::init(float x, float y)
{
	setAni(ANIMATION->findAnimation("gurdyfaceidle"));
	ANIMATION->start("gurdyfaceidle");
	anibody = ANIMATION->findAnimation("gurdybodyidle");
	ANIMATION->start("gurdybodyidle");
	body = RectMakeCenter(x, y, IMAGE->findImage("gurdybody")->getFrameWidth(), IMAGE->findImage("gurdybody")->getFrameHeight());

	CCharacter::init({ x,y }, // make pos
		RectMakeCenter(x, y, IMAGE->findImage("gurdyface")->getFrameWidth(), IMAGE->findImage("gurdyface")->getFrameHeight()), //rc
		{ x, y }, { 30,30 }, //collider
		30,	//collider -> shadow distance
		{ x, y + shadowdistance }, { IMAGE->findImage("gurdybody")->getFrameWidth(),IMAGE->findImage("gurdybody")->getFrameWidth() / 3 }, // collider.shadow
		30);//hp
	IMAGE->addImage("shadowGurdy", "images/shadow.bmp", colliderShadow->getSize().x, colliderShadow->getSize().y, true, RGB(255, 0, 255));

	setMonster_Type(MONSTER_TYPE::GURDY);
	maxHp = hp;
	AI_init(this, monsterType);

	SOUND->stop("bgm");
	SOUND->play("bossfight");
	return S_OK;
}

void CGurdy::release()
{
}

void CGurdy::update()
{
	AI_update();
	collider->setPos({ RectX(body), RectY(body) });
	collider->setSize({ IMAGE->findImage("gurdybody")->getFrameWidth(), IMAGE->findImage("gurdybody")->getFrameHeight() });
	colliderShadow->setPos({ RectX(rc), RectY(rc) + shadowdistance });
	ALLUI->setboss(this);
	ALLUI->setRespawn(true);
}

void CGurdy::render()
{
	if (InputManager->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), collider->getPos().x - collider->getSize().x / 2,
			collider->getPos().y - collider->getSize().y / 2,
			collider->getPos().x + collider->getSize().x / 2,
			collider->getPos().y + collider->getSize().y / 2);
	}
	RECT rec = RectMakeCenter(RectX(body), RectY(body)+ IMAGE->findImage("gurdybody")->getFrameHeight()/2 + 30, IMAGE->findImage("gurdybody")->getFrameWidth(), IMAGE->findImage("gurdybody")->getFrameHeight());
	IMAGE->render("shadowGurdy", getMemDC(), rec.left, rec.top);
	IMAGE->findImage("gurdybody")->aniRender(getMemDC(), body.left, body.top, anibody);
	IMAGE->findImage("gurdyface")->aniRender(getMemDC(), getRC().left, getRC().top - 30, getAni());
}
