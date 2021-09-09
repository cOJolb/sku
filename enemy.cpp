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
	//ani = ANIMATION->findAnimation(unitImageInfo.unitName + "RightIdle");
	//ANIMATION->start(unitImageInfo.unitName + "RightIdle");
	//ANIMATION->start(unitImageInfo.unitName + "LeftIdle");
	rc = RectMakeCenter(collider->getPos(), collider->getSize().x, collider->getSize().y);
	futureRc = RectMakeCenter(collider->getPos(), collider->getSize().x, collider->getSize().y);
	ap = 250;
	count = 0;
	superArmor = false;
	delay = 10;
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
	rc = RectMakeCenter(collider->getPos(), collider->getSize().x, collider->getSize().y);
	ptUpdate();
	//ani = ANIMATION->findAnimation(unitImageInfo.unitName + unitImageInfo.unitFoward + unitImageInfo.unitState);
	if (unitImageInfo.unitFoward == "Left"){frameY = 0;}
	else { frameY = 1; }

	if (isStart)
	{
		frameX = 0;
		count = 0;
		isStart = false;
	}
	switch (frameType)
	{
	case FRAME_TYPE::FIX:
		break;
	case FRAME_TYPE::LOOP:
		countUpLoop(frameX, 0, IMAGE->findImage(unitImageInfo.unitName + unitImageInfo.unitState)->getMaxFrameX(), count, delay);
		break;
	case FRAME_TYPE::RANGE:
		if (frameX == 0) { frameX = startFrameX; }
		countUp(frameX, maxFrameX, count, delay);
		break;
	case FRAME_TYPE::RANGELOOP:
		countUpLoop(frameX, startFrameX, maxFrameX, count, delay);
		break;
	case FRAME_TYPE::NORMAL:
		countUp(frameX, IMAGE->findImage(unitImageInfo.unitName + unitImageInfo.unitState)->getMaxFrameX(), count, delay);
		break;
	default:
		break;
	}
	//if (isLoop) { countUpLoop(frameX, 0, IMAGE->findImage(unitImageInfo.unitName + unitImageInfo.unitState)->getMaxFrameX(), count, delay); }
	//else { countUp(frameX, IMAGE->findImage(unitImageInfo.unitName + unitImageInfo.unitState)->getMaxFrameX(), count, delay); }

	if (ap < 250) { ap += 10; }
	else if (ap > 250) { ap = 250; }
}

void C_enemy::render()
{
	double D_maxHp = maxHp;
	double D_Hp = hp;
	double D_barWidth = IMAGE->findImage("enemyHpBar")->getWidth();
	int NowHp = D_barWidth / D_maxHp * D_Hp;
	IMAGE->findImage("enemyHpBar")->renderCenter(getCVOSDC(), {pt.x, pt.y - collider->getSize().y/2 - 25}, 0, 0, NowHp, IMAGE->findImage("enemyHpBar")->getHeight());
	IMAGE->findImage(unitImageInfo.unitName + unitImageInfo.unitState)->alphaFrameRenderCenter(getCVOSDC(), pt, frameX, frameY, ap);
	//IMAGE->findImage(unitImageInfo.unitName + unitImageInfo.unitState)->frameRenderCenter(getCVOSDC(), pt, frameX, frameY);
	//IMAGE->findImage(unitImageInfo.unitName+ unitImageInfo.unitState)->aniRender(getCVOSDC(), pt.x - IMAGE->findImage(unitImageInfo.unitName+ unitImageInfo.unitState)->getFrameWidth() / 2, pt.y - IMAGE->findImage(unitImageInfo.unitName + unitImageInfo.unitState)->getFrameHeight() / 2, ani);
}
