#include "framework.h"
#include "GurdyState.h"
#include "CPlayer.h"

Gurdy_Idle::Gurdy_Idle()
{
	m_eState = STATE_TYPE::IDLE;
}

Gurdy_Idle::~Gurdy_Idle()
{
}

void Gurdy_Idle::Enter()
{
}

void Gurdy_Idle::update()
{
	CCharacter* pMon = m_pFSM->GetMon();
	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (Inrange(500, ENEMY->GetPlayer()->getPt()))
	{
		m_pFSM->ChangeState(STATE_TYPE::TRACE);
	}
}

void Gurdy_Idle::Exit()
{
}

bool Gurdy_Idle::Inrange(int range, Vec2 pt)
{
	CCharacter* pMon = m_pFSM->GetMon();
	if (UTIL::getDistance(pMon->getPt().x, pMon->getPt().y, pt.x, pt.y) < range)
	{
		return true;
	}
	else return false;
}

Gurdy_Trace::Gurdy_Trace()
{
	m_eState = STATE_TYPE::TRACE;
}

Gurdy_Trace::~Gurdy_Trace()
{
}
void Gurdy_Trace::Enter()
{
	CCharacter* pMon = m_pFSM->GetMon();
	pMon->setAni(ANIMATION->findAnimation("gurdyfaceidle"));
	ANIMATION->start("gurdyfaceidle");
	count = 0;
}

void Gurdy_Trace::update()
{
	CCharacter* pMon = m_pFSM->GetMon();
	count++;

	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (count == 60)
	{
		m_pFSM->ChangeState(STATE_TYPE::ATTACK);
	}
}
void Gurdy_Trace::Exit()
{
}



Gurdy_Atk::Gurdy_Atk()
{
	m_eState = STATE_TYPE::ATTACK;
}

Gurdy_Atk::~Gurdy_Atk()
{
}

void Gurdy_Atk::Enter()
{
	CCharacter* pMon = m_pFSM->GetMon();
	//paturn = 2;
	paturn = RND->getFromIntTo(0,2);
	angle = UTIL::getAngle(pMon->getPt().x, pMon->getPt().y, ENEMY->GetPlayer()->getPt().x,ENEMY->GetPlayer()->getPt().y);
	if (angle > PI_2 && angle < PI + PI_4) //left
	{
		foward = 0;
	}
	else if (angle > PI + PI_4 && angle < PI + PI_2 + PI_4) //down
	{
		foward = 1;
	}
	else // right
	{
		foward = 2;
	}
	firePt = pMon->getPt();
	escapeAtk = false;
	animationcount = 0;

	speed = 10;
	height = 20;
	distance = 400;
	bulletsize = 15;
}

void Gurdy_Atk::update()
{
	bossatk();
	CCharacter* pMon = m_pFSM->GetMon();
	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (escapeAtk)
	{
		m_pFSM->ChangeState(STATE_TYPE::TRACE);
	}
}

void Gurdy_Atk::Exit()
{

}

void Gurdy_Atk::bossatk()
{
	CCharacter* pMon = m_pFSM->GetMon();
	RECT rec = pMon->getRC();
	
	switch (paturn)
	{
	case 0:
		if (animationcount == 0)
		{
			pMon->setAni(ANIMATION->findAnimation("gurdyatkready"));
			ANIMATION->start("gurdyatkready");
		}
		switch (foward)
		{
		case 0:
			if (animationcount == 30)
			{
				pMon->setRC(RectMakeCenter(RectX(rec) - 60, RectY(rec) + 30, RectWidth(rec), RectHeight(rec)));
				pMon->setAni(ANIMATION->findAnimation("gurdyleftatkready"));
				ANIMATION->start("gurdyleftatkready");
			}
			if (animationcount == 60)
			{
				pMon->setAni(ANIMATION->findAnimation("gurdyleftatk"));
				ANIMATION->start("gurdyleftatk");
				FireBullet();
			}
			if (animationcount == 90)
			{
				pMon->setAni(ANIMATION->findAnimation("gurdyleftatkclose"));
				ANIMATION->start("gurdyleftatkclose");
			}
			if (animationcount == 120)
			{
				pMon->setRC(RectMakeCenter(RectX(rec) + 60, RectY(rec) - 30, RectWidth(rec), RectHeight(rec)));
				escapeAtk = true;
			}
			break;
		case 1:
			if (animationcount == 30)
			{
				pMon->setRC(RectMakeCenter(RectX(rec), RectY(rec) + 60, RectWidth(rec), RectHeight(rec)));
				pMon->setAni(ANIMATION->findAnimation("gurdydownatkready"));
				ANIMATION->start("gurdydownatkready");
			}
			if (animationcount == 60)
			{
				pMon->setAni(ANIMATION->findAnimation("gurdydownatk"));
				ANIMATION->start("gurdydownatk");
				FireBullet();
			}
			if (animationcount == 90)
			{
				pMon->setAni(ANIMATION->findAnimation("gurdydownatkclose"));
				ANIMATION->start("gurdydownatkclose");
			}
			if (animationcount == 120)
			{
				pMon->setRC(RectMakeCenter(RectX(rec), RectY(rec) - 60, RectWidth(rec), RectHeight(rec)));
				escapeAtk = true;
			}
			break;
		case 2:
			if (animationcount == 30)
			{
				pMon->setRC(RectMakeCenter(RectX(rec) +60, RectY(rec) + 30, RectWidth(rec), RectHeight(rec)));
				pMon->setAni(ANIMATION->findAnimation("gurdyrightatkready"));
				ANIMATION->start("gurdyrightatkready");
			}
			if (animationcount == 60)
			{
				pMon->setAni(ANIMATION->findAnimation("gurdyrightatk"));
				ANIMATION->start("gurdyrightatk");
				FireBullet();
			}
			if (animationcount == 90)
			{
				pMon->setAni(ANIMATION->findAnimation("gurdyrightatkclose"));
				ANIMATION->start("gurdyrightatkclose");
			}
			if (animationcount == 120)
			{
				pMon->setRC(RectMakeCenter(RectX(rec) - 60, RectY(rec) - 30, RectWidth(rec), RectHeight(rec)));
				escapeAtk = true;
			}
			break;
		}

		break;
	case 1:
		if (animationcount == 50)
		{
			SOUND->play("gurdyflysound");
			pMon->setAni(ANIMATION->findAnimation("gurdysummonpooter"));
			ANIMATION->start("gurdysummonpooter");
			ENEMY->respawn(MONSTER_TYPE::FLY, pMon->getPt());
		}
		if (animationcount == 80)
		{
			escapeAtk = true;
		}
		break;
	case 2:

		if (animationcount == 30)
		{
			pMon->setAni(ANIMATION->findAnimation("gurdysummonflyready"));
			ANIMATION->start("gurdysummonflyready");
		}
		if (animationcount == 60)
		{
			SOUND->play("gurdylittleflysound");
			pMon->setAni(ANIMATION->findAnimation("gurdysummonfly"));
			ANIMATION->start("gurdysummonfly");
			ENEMY->respawn(MONSTER_TYPE::SMALLFLY, pMon->getPt() + 50);
			ENEMY->respawn(MONSTER_TYPE::SMALLFLY, pMon->getPt() - 50);
		}
		if (animationcount == 90)
		{
			pMon->setAni(ANIMATION->findAnimation("gurdysummonflyclose"));
			ANIMATION->start("gurdysummonflyclose");
		}
		if (animationcount == 120)
		{
			escapeAtk = true;
		}
		break;
	default:
		break;
	}
	animationcount++;
}

void Gurdy_Atk::FireBullet()
{
	CCharacter* pMon = m_pFSM->GetMon();
	RECT rec = pMon->getRC();
	SOUND->play("gurdyfiresound");
	switch (foward)
	{
	case 0:
		angle = UTIL::getAngle(RectX(rec), RectY(rec), ENEMY->GetPlayer()->getPt().x, ENEMY->GetPlayer()->getPt().y);

		BULLET->fire(angle, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		BULLET->fire(angle + PI / 32, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		BULLET->fire(angle - PI / 32, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		BULLET->fire(angle + PI / 16, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		BULLET->fire(angle - PI / 16, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");

		break;
	case 1:
		firePt.y += 60;
		angle = UTIL::getAngle(RectX(rec), RectY(rec), ENEMY->GetPlayer()->getPt().x, ENEMY->GetPlayer()->getPt().y);

		BULLET->fire(angle, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		BULLET->fire(angle + PI / 32, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		BULLET->fire(angle - PI / 32, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		BULLET->fire(angle + PI / 16, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		BULLET->fire(angle - PI / 16, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		break;
	case 2:
		firePt.x += 60;
		firePt.y += 30;
		angle = UTIL::getAngle(RectX(rec), RectY(rec), ENEMY->GetPlayer()->getPt().x, ENEMY->GetPlayer()->getPt().y);

		BULLET->fire(angle, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		BULLET->fire(angle + PI / 32, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		BULLET->fire(angle - PI / 32, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		BULLET->fire(angle + PI / 16, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		BULLET->fire(angle - PI / 16, speed, firePt, height, distance, 1, CHARACTER::MONSTER, bulletsize, "GurdyBullet");
		break;
	default:
		break;
	}
}



Gurdy_Die::Gurdy_Die()
{
	m_eState = STATE_TYPE::DEAD;
}

Gurdy_Die::~Gurdy_Die()
{
}

void Gurdy_Die::Enter()
{
	EFFECT->play("gurdydie", m_pFSM->GetMon()->getPt().x, m_pFSM->GetMon()->getPt().y);
	EFFECT->play("bossdiebase", m_pFSM->GetMon()->getPt().x, m_pFSM->GetMon()->getPt().y);
	SOUND->stop("bossfight");
	SOUND->play("bgm");
	count = 0;
}

void Gurdy_Die::update()
{

}

void Gurdy_Die::Exit()
{
}
