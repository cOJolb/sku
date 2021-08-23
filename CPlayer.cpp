#include "framework.h"
#include "CPlayer.h"
#include "CFSM.h"
#include "PlayerState.h"
#include "CState.h"
#include "CStage.h"
#include "CMap.h"
#include "CBullet.h"
#include "CItem.h"
CPlayer::CPlayer() :
	CCharacter(), isMove(false), totalTears(0)
{
	setAni(ANIMATION->findAnimation("down_head"));
	theInnerEye = false;
	moveDistance = 0;
	addAngle = 0;
}

CPlayer::CPlayer(Vec2 _pos, RECT _rc, int _hp) :
	CCharacter(_pos, _rc, _hp), isMove(false), totalTears(0)
{ 
	setAni(ANIMATION->findAnimation("down_head"));

}

CPlayer::~CPlayer()
{
	SAFE_DELETE(ani_body);

}

HRESULT CPlayer::init()
{
	CCharacter::init({ WINSIZEX / 2, WINSIZEY / 2 }, // make pos
		RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, PLAYERWIDTH, PLAYERHEIGHT), //rc
		{ WINSIZEX / 2, WINSIZEY / 2 }, { PLAYERWIDTH,PLAYERWIDTH }, //collider
		IMAGE->findImage("isaac")->getFrameHeight()/2,	//collider -> shadow distance
		{ WINSIZEX / 2, WINSIZEY / 2 + shadowdistance }, { PLAYERWIDTH,PLAYERWIDTH / 3 }, // collider.shadow
		10);//hp
	IMAGE->addImage("shadowPlayer", "images/shadow.bmp", colliderShadow->getSize().x, colliderShadow->getSize().y, true, RGB(255, 0, 255));

	setAni(ANIMATION->findAnimation("playeridlehead"));
	ani_body = ANIMATION->findAnimation("playeridlebody");
	animation anitemp = *ANIMATION->findAnimation("playeridlebody");
	anitemp.start();
	ANIMATION->start("playeridlebody");
	ANIMATION->start("playeridlehead");
	isMove = false;
	
	//player item and hp
	maxHp = 10;
	hp = 10;

	//player speed
	playerMaxSpeed = 4;
	playerspeed = 0;

	//bullet information
	bulletsize = 20; 
	bulletdistance = 100;
	bulletDamage = 2;
	height = 30;
	bulletSpeed = 8;
	totalTears = 0;
	tearDelay = 0;

	IMAGE->addImage("playerBullet", "images/playerbullet.bmp", bulletsize * 13, bulletsize, true, RGB(255, 0, 255));
	IMAGE->addImage("playerBulletShadow", "images/shadow.bmp", bulletsize, bulletsize / 3, true, RGB(255, 0, 255));

	//player information
	coin = 10;
	bomb = 3;
	key = 0;

	AI_init(this,MONSTER_TYPE::NONE);
	return S_OK;
}

void CPlayer::release()
{
}

void CPlayer::update()
{
	if (getstate() == STATE_TYPE::IDLE || getstate() == STATE_TYPE::ATTACK)
	{
		Move();
		fire();
		UseBomb();
	}
	
	COLLISION->tileCollision(STAGE->getCurStage()->getCurRoom(), pt, prevPt, playerfoward, 0);
	//pt = COLLISION->wallCollision(pt, { MAPSTARTX+ TILEWIDTH, MAPSTARTY + TILEHEIGHT }, TILESIZEX- TILEWIDTH*2, TILESIZEY - TILEHEIGHT*2);
	prevPt = pt;

	colliderShadow->setPos(pt);
	collider->setPos({ pt.x, pt.y -shadowdistance });
	rc = RectMakeCenter(collider->getPos(), PLAYERWIDTH, PLAYERHEIGHT);

	playerGetItem();

	if (InputManager->isOnceKeyDown('X'))
	{
		hp = maxHp;
	}
	if (InputManager->isOnceKeyDown('C'))
	{
		coin = 99;
		bomb = 99;
		key = 99;
	}
	
	AI_update();
}

void CPlayer::render()
{
	if (InputManager->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), collider->getPos().x - collider->getSize().x / 2,
			collider->getPos().y - collider->getSize().y / 2,
			collider->getPos().x + collider->getSize().x / 2,
			collider->getPos().y + collider->getSize().y / 2);
	}
	RECT rec = RectMakeCenter(colliderShadow->getPos().x, colliderShadow->getPos().y, colliderShadow->getSize().x, colliderShadow->getSize().y);
	IMAGE->render("shadowPlayer", getMemDC(), rec.left, rec.top);
	if (getstate() == STATE_TYPE::ATTACK)
	{
		if (count > 80)
		{
			count = 0;
		}
		if (count >= 30)
		{
			if(count ==30 )atkani = 0;
			setAnimation();
			setAnimationbody();
			IMAGE->findImage("playerbody")->aniRender(getMemDC(),
				getRC().left + IMAGE->findImage("isaac")->getFrameWidth() / 2 - IMAGE->findImage("playerbody")->getFrameWidth() / 2,
				getRC().top + 28, ani_body);
			IMAGE->findImage("isaac")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
		}
		else
		{
			IMAGE->findImage("isaacEvent")->aniRender(getMemDC(), getRC().left - 18, getRC().top - 18, getAni());
		}
		count++;
	}
	else if (getstate() == STATE_TYPE::IDLE)
	{
		count = 0;
		IMAGE->findImage("playerbody")->aniRender(getMemDC(),
			getRC().left + IMAGE->findImage("isaac")->getFrameWidth() / 2 - IMAGE->findImage("playerbody")->getFrameWidth() / 2,
			getRC().top + 28, ani_body);
		IMAGE->findImage("isaac")->aniRender(getMemDC(), getRC().left, getRC().top, getAni());
		setAnimation();
		setAnimationbody();
	}
	else
	{
		IMAGE->findImage("isaacEvent")->aniRender(getMemDC(), getRC().left - 18, getRC().top - 18, getAni());
	}
}

void CPlayer::Move()
{
	if (InputManager->isStayKeyDown('S') && InputManager->isStayKeyDown('A'))
	{
		movecount = 5;
		playerfoward = FOWARD::LEFTDOWN;
		playerspeed += playerMaxSpeed / sqrtf(2) / 10;
		if (playerspeed >= playerMaxSpeed / sqrtf(2)) playerspeed = playerMaxSpeed / sqrtf(2);
		pt = Vec2(pt.x - playerspeed, pt.y + playerspeed);
	}
	else if (InputManager->isStayKeyDown('A') && InputManager->isStayKeyDown('W'))
	{
		movecount = 5;
		playerfoward = FOWARD::LEFTTOP;
		playerspeed += playerMaxSpeed / sqrtf(2) / 10;
		if (playerspeed >= playerMaxSpeed / sqrtf(2)) playerspeed = playerMaxSpeed / sqrtf(2);
		pt = Vec2(pt.x - playerspeed, pt.y - playerspeed);
	}
	else if (InputManager->isStayKeyDown('D') && InputManager->isStayKeyDown('W'))
	{
		movecount = 5;
		playerfoward = FOWARD::RIGHTTOP;
		playerspeed += playerMaxSpeed / sqrtf(2) / 10;
		if (playerspeed >= playerMaxSpeed / sqrtf(2)) playerspeed = playerMaxSpeed / sqrtf(2);
		pt = Vec2(pt.x + playerspeed, pt.y - playerspeed);
	}

	else if (InputManager->isStayKeyDown('D') && InputManager->isStayKeyDown('S'))
	{
		movecount = 5;
		playerfoward = FOWARD::RIGHTDOWN;
		playerspeed += playerMaxSpeed / sqrtf(2) / 10;
		if (playerspeed >= playerMaxSpeed / sqrtf(2) +0.2) playerspeed = playerMaxSpeed / sqrtf(2) + 0.2;
		pt = Vec2(pt.x + playerspeed, pt.y + playerspeed);
	}
	else if (InputManager->isStayKeyDown('A'))
	{
		movecount = 5;
		playerfoward = FOWARD::LEFT;
		playerspeed += playerMaxSpeed / 10;
		if (playerspeed >= playerMaxSpeed) playerspeed = playerMaxSpeed;
		//movetoLeft(rc, playerspeed);
		pt = Vec2(pt.x - playerspeed, pt.y);
	}

	else if (InputManager->isStayKeyDown('S'))
	{
		movecount = 5;
		playerfoward = FOWARD::DOWN;
		playerspeed += playerMaxSpeed / 10;
		if (playerspeed >= playerMaxSpeed) playerspeed = playerMaxSpeed;
		//movetoLeft(rc, playerspeed);
		pt = Vec2(pt.x, pt.y + playerspeed);
	}
	else if (InputManager->isStayKeyDown('D'))
	{
		movecount = 5;
		playerfoward = FOWARD::RIGHT;
		playerspeed += playerMaxSpeed / 10;
		if (playerspeed >= playerMaxSpeed + playerMaxSpeed / 10) playerspeed = playerMaxSpeed + playerMaxSpeed / 10;
		//movetoLeft(rc, playerspeed);
		pt = Vec2(pt.x + playerspeed, pt.y);
	}
	else if (InputManager->isStayKeyDown('W'))
	{
		movecount = 5;
		playerfoward = FOWARD::UP;
		playerspeed += playerMaxSpeed / 10;
		if (playerspeed >= playerMaxSpeed) playerspeed = playerMaxSpeed;
		//movetoLeft(rc, playerspeed);
		pt = Vec2(pt.x, pt.y - playerspeed);
	}
	else
	{
		_slide();
		playerspeed = 0;
	}
	if (prevfoward != playerfoward)
	{
		moveani = 0;
		atkani = 0;
		if (prevfoward < 4 && playerfoward < 4)
		{
			playerspeed = 0;
		}
		prevfoward = playerfoward;
	}

	/*STAGE->getCurStage()->getMap()->GetvObstacle();
	if (IntersectRect(&rec, &rc, &STAGE->getCurStage()->getMap()->getTile()[20].rcTile))*/

	rc = RectMakeCenter(pt.x, pt.y, PLAYERWIDTH, PLAYERHEIGHT);
	collider->setPos(pt);
}
	
		

void CPlayer::_slide()
{
	movenatual++;
	if (movecount > 0)
	{
		if (movenatual % 5 == 0)
		{
			switch (playerfoward)
			{
			case FOWARD::DOWN:
				movecount--;
				pt = Vec2(pt.x, pt.y + 2.1);
				break;
			case FOWARD::LEFT:
				movecount--;
				pt = Vec2(pt.x - 2.1, pt.y);
				break;
			case FOWARD::RIGHT:
				movecount--;
				pt = Vec2(pt.x + 2.1, pt.y);
				break;
			case FOWARD::UP:
				movecount--;
				pt = Vec2(pt.x, pt.y - 2.1);
				break;
			case FOWARD::LEFTDOWN:
				movecount--;
				pt = Vec2(pt.x - 2, pt.y + 2);
				break;
			case FOWARD::LEFTTOP:
				movecount--;
				pt = Vec2(pt.x - 2, pt.y - 2);
				break;
			case FOWARD::RIGHTDOWN:
				movecount--;
				pt = Vec2(pt.x + 2, pt.y + 2);
				break;
			case FOWARD::RIGHTTOP:
				movecount--;
				pt = Vec2(pt.x + 2, pt.y - 2);
				break;
			default:
				break;
			}
		}
	}

	else movenatual = 0;
}


void CPlayer::fire()
{
	static int fireCnt = 0;
	static vector2 firePt = { 0, 0 };
	float fireAngle = PI;
	
	int tdelay = 0;
	if (tearDelay >= 0)
	{
		tdelay = floor(16 - 6 * sqrtf(tearDelay * 1.3 + 1));
	}
	else if (tearDelay <0 && tearDelay > -0.77)
	{
		tdelay = floor(16 - 6 * sqrtf(tearDelay * 1.3 + 1) - 6 * tearDelay);
	}
	else tdelay = floor (16 - 6 * tearDelay);
	if (tdelay < 5) tdelay = 5;
	
	fireCnt++;
	if (fireCnt >= floor (100 / (30/tdelay))) fireCnt = floor (100 / (30 / tdelay));
	bool isFire = false;

	bool isUp = InputManager->isStayKeyDown(VK_UP);
	bool isDown = InputManager->isStayKeyDown(VK_DOWN);
	bool isLeft = InputManager->isStayKeyDown(VK_LEFT);
	bool isRight = InputManager->isStayKeyDown(VK_RIGHT);
	if (isUp && !isDown && !isLeft && !isRight)
	{
		headfoward = FOWARD::UP;
		fireAngle = PI_2;
		firePt = { pt.x, static_cast<float>(rc.top - 20) };
		isFire = true;
	}
	if (!isUp && isDown && !isLeft && !isRight)
	{
		headfoward = FOWARD::DOWN;
		fireAngle = PI + PI_2;
		firePt = { pt.x, static_cast<float>(rc.bottom - 20) }; 
		isFire = true;
	}
	if (!isUp && !isDown && isLeft && !isRight)
	{
		headfoward = FOWARD::LEFT;
		fireAngle = PI;
		firePt = { static_cast<float>(rc.left), static_cast<float>(rc.top) };
		isFire = true;
	}
	if (!isUp && !isDown && !isLeft && isRight)
	{
		headfoward = FOWARD::RIGHT;
		fireAngle = PI2;
		firePt = { static_cast<float>(rc.right), static_cast<float>(rc.top) };
		isFire = true;
	}
	if (!isUp && !isDown && !isLeft && !isRight)
	{
		isFire = false;
	}
	if (isFire && fireCnt == floor(100 / (30 / tdelay)))
	{
		fireCnt = 0;
		SOUND->play("tearfiresound");
		if (theInnerEye)
		{
			if (headfoward <= 1)
			{
				BULLET->fire(fireAngle, bulletSpeed, {firePt.x, firePt.y -20}, height, bulletdistance, bulletDamage, CHARACTER::PLAYER, bulletsize, "playerBullet");
				BULLET->fire(fireAngle, bulletSpeed, firePt, height, bulletdistance, bulletDamage, CHARACTER::PLAYER, bulletsize, "playerBullet");
				BULLET->fire(fireAngle, bulletSpeed, {firePt.x, firePt.y +20}, height, bulletdistance, bulletDamage, CHARACTER::PLAYER, bulletsize, "playerBullet");
			}
			else
			{
				BULLET->fire(fireAngle, bulletSpeed, { firePt.x-20, firePt.y}, height, bulletdistance,bulletDamage, CHARACTER::PLAYER, bulletsize, "playerBullet");
				BULLET->fire(fireAngle, bulletSpeed, firePt, height, bulletdistance, bulletDamage, CHARACTER::PLAYER, bulletsize, "playerBullet");
				BULLET->fire(fireAngle, bulletSpeed, { firePt.x+20, firePt.y}, height, bulletdistance, bulletDamage, CHARACTER::PLAYER, bulletsize, "playerBullet");
			}
		}
		else
		{
			BULLET->fire(fireAngle, bulletSpeed, firePt, height, bulletdistance, bulletDamage, CHARACTER::PLAYER, bulletsize, "playerBullet");
		}
	}
}

void CPlayer::UseBomb()
{
	if (InputManager->isOnceKeyDown('E'))
	{
		if (bomb > 0)
		{
			bomb--;
			ITEM->respawnUseItem(USE_ITEM::BOMB, pt);
		}
	}
}

void CPlayer::setAnimation()
{
	bool isUp = InputManager->isStayKeyDown(VK_UP);
	bool isDown = InputManager->isStayKeyDown(VK_DOWN);
	bool isLeft = InputManager->isStayKeyDown(VK_LEFT);
	bool isRight = InputManager->isStayKeyDown(VK_RIGHT);

	if (headfoward != prevhead)
	{
		atkani = 0;
		prevhead = headfoward;
	}
	if (isUp && !isDown && !isLeft && !isRight)
	{
		if (atkani % 30 == 0)
		{
			ani = ANIMATION->findAnimation("up_head");
			ANIMATION->start("up_head");
		}
	}
	if (!isUp && isDown && !isLeft && !isRight)
	{
		if (atkani % 30 == 0)
		{
			ani = ANIMATION->findAnimation("down_head");
			ANIMATION->start("down_head");
		}
	}
	if (!isUp && !isDown && isLeft && !isRight)
	{
		if (atkani % 30 == 0)
		{
			ani = ANIMATION->findAnimation("left_head");
			ANIMATION->start("left_head");
		}
	}
	if (!isUp && !isDown && !isLeft && isRight)
	{
		if (atkani % 30 == 0)
		{
			ani = ANIMATION->findAnimation("right_head");
			ANIMATION->start("right_head");
		}
	}
	if (isUp + isDown + isLeft + isRight  >= 2 || isUp + isDown + isLeft + isRight == 0)
	{
		if (atkani % 30 == 0)
		{
			atkani = 0;
			ani = ANIMATION->findAnimation("playeridlehead");
			ANIMATION->start("playeridlehead");
		}
		if (atkani == 0) atkani = -1;
	}
	atkani++;
	
}

void CPlayer::setAnimationbody()
{

	if (InputManager->isStayKeyDown('W'))
	{
		if (moveani % 100 == 0)
		{
			ani_body = ANIMATION->findAnimation("playerupbody");
			ANIMATION->start("playerupbody");
		}
	}
	else if (InputManager->isStayKeyDown('S'))
	{
		if (moveani % 100 == 0)
		{
			ani_body = ANIMATION->findAnimation("playerdownbody");
			ANIMATION->start("playerdownbody");
		}
	}
	else if (InputManager->isStayKeyDown('A'))
	{
		if (moveani % 100 == 0)
		{
			ani_body = ANIMATION->findAnimation("playerleftbody");
			ANIMATION->start("playerleftbody");
		}
	}
	else if (InputManager->isStayKeyDown('D'))
	{
		if (moveani % 100 == 0)
		{
			ani_body = ANIMATION->findAnimation("playerrightbody");
			ANIMATION->start("playerrightbody");
		}
	}
	else
	{
		moveani = 0;
		ani_body = ANIMATION->findAnimation("playeridlebody");
		ANIMATION->start("playeridlebody");
		moveani--;
		
	}
	moveani++;
}

void CPlayer::playerGetItem()
{
	for (int i = 0; i < ITEM->getItem().size(); i++)
	{
		bool isIbcp = COLLISION->isCollision((*ITEM->getviItem(i))->getcollider(), collider);
		bool isIbsp = COLLISION->isCollision((*ITEM->getviItem(i))->GetcolliderShadow(),colliderShadow);
		if (isIbcp)
		{
			switch ((*ITEM->getviItem(i))->getItemType())
			{
			case ITEM_TYPE::ITEM_HEART:
				if (isFullHp()) { break; }
				else
				{
					SOUND->play("getbasicitem");
					hp += 2;
					cantHpOver();
					ITEM->itemRemove(i);
					break;
				}
			case ITEM_TYPE::ITEM_COIN:
				if (coin >= 99) { break; }
				else
				{
					SOUND->play("getbasicitem");
					coin += 1;
					cantCoinOver();
					ITEM->itemRemove(i);
					break;
				}
			case ITEM_TYPE::ITEM_BOMB:
				if (bomb >= 99) { break; }
				else
				{
					SOUND->play("getbasicitem");
					bomb += 1;
					cantBombOver();
					ITEM->itemRemove(i);
					break;
				}
			case ITEM_TYPE::ITEM_KEY:
				if (key >= 99) { break; }
				else
				{
					SOUND->play("getbasicitem");
					key += 1;
					cantKeyOver();
					ITEM->itemRemove(i);
					break;
				}
			case ITEM_TYPE::ITEM_THEINNEREYE:
				SOUND->play("getitem");
				setInnerEye(true);
				tearDelay -= 0.2;
				ITEM->itemRemove(i);
				break;
			case ITEM_TYPE::ITEM_MOMSLIPSTICK:
				SOUND->play("getitem");
				bulletdistance += 100;
				ITEM->itemRemove(i);
				break;
			case ITEM_TYPE::ITEM_PENTAGRAM:
				SOUND->play("getitem");
				bulletDamage += 1;
				ITEM->itemRemove(i);
				break;
			case ITEM_TYPE::ITEM_BLOODBAG:
				SOUND->play("getitem");
				maxHp += 2;
				hp += 10;
				cantHpOver();
				playerMaxSpeed += 0.3;
				cantSpeedOver();
				ITEM->itemRemove(i);
				break;
			case ITEM_TYPE::ITEM_SPEEDBALL:
				SOUND->play("getitem");
				playerMaxSpeed += 0.3;
				cantSpeedOver();
				bulletSpeed += 0.2;
				cantBulletSpeedOver();
				ITEM->itemRemove(i);
			default:
				break;
			}
			break;
		}
	}
}

bool CPlayer::isFullHp()
{
	if (maxHp == hp)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CPlayer::cantHpOver()
{
	if (hp > maxHp)
	{
		hp = maxHp;
	}
}

