#include "framework.h"
#include "PooterState.h"
#include "BulletManager.h"
#include "enemyManager.h"
#include "CPlayer.h"
//=============================================대기상태=========================================================
Fly_Idle::Fly_Idle()
{
	m_eState = STATE_TYPE::IDLE;
}

Fly_Idle::~Fly_Idle()
{
}

void Fly_Idle::Enter()
{
	count = 0;
	movetime = 32;
	delay = 35;
	atkcount = 0;

	idle = 0;

	foward = RND->getFromIntTo(0, 7);
	distance = 0.0f;
	parabola = 0.0f;
	angle = 0.0f;
}
void Fly_Idle::update()
{
	CCharacter* pMon = m_pFSM->GetMon();
	atkcount++;
	Move();

	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (inrange(200, ENEMY->GetPlayer()->getPt()))
	{
		m_pFSM->ChangeState(STATE_TYPE::ATTACK);
	}
}



void Fly_Idle::Exit()
{
}
void Fly_Idle::Move()
{
	CObject* pMon = m_pFSM->GetMon();

	if (count > delay)
	{
		count = 0;
		parabola = 0.0f;
		foward = RND->getFromIntTo(0, 7);
		distance = 0;
	}
	RECT rec = pMon->getRC();
	
	distance += 0.1;

	if (count <= movetime && count % 2 == 0)
	{
		rec = RectMakeCenter(
			RectX(rec) + cosf(PI - foward * PI_4) * distance,
			RectY(rec) - sinf(PI - foward * PI_4) * distance,
			RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
		parabola += PI_16;
	}

	pMon->setRC(rec);
	Vec2 p_monster;
	p_monster.x = RectX(rec);
	p_monster.y = RectY(rec);
	pMon->setPt(p_monster);

	count++;
}

bool Fly_Idle::inrange(int range, vector2 pt)
{
	CObject* pMon = m_pFSM->GetMon();
	if (UTIL::getDistance(pMon->getPt().x, pMon->getPt().y, pt.x, pt.y) < range)
	{
		return true;
	}
	else return false;
}
//=============================================대기상태=========================================================



//=============================================감지상태=========================================================


Fly_Trace::Fly_Trace()
{
	m_eState = STATE_TYPE::TRACE;
}

Fly_Trace::~Fly_Trace()
{
}
void Fly_Trace::Enter()
{
}
void Fly_Trace::update()
{
}

void Fly_Trace::Exit()
{
}
//=============================================대기상태=========================================================


//=============================================공격상태=========================================================
Fly_Atk::Fly_Atk()
{
	m_eState = STATE_TYPE::ATTACK;

}

Fly_Atk::~Fly_Atk()
{
}

void Fly_Atk::Enter()
{
	count = 0;
	delay = 70;

	angle = 0.0f;
	speed = 0.0f;
	fire = 0;
	shadowDistance = 0;
	distance = 0;
}

void Fly_Atk::update()
{
	CCharacter* pMon = m_pFSM->GetMon();
	if (count == 0)
	{
		angle = UTIL::getAngle(pMon->getPt().x, pMon->getPt().y, ENEMY->GetPlayer()->getPt().x, ENEMY->GetPlayer()->getPt().y);
		speed = 5;
		fire = pMon->getPt();
		shadowDistance = 20;
		distance = 200;

		BULLET->fire(angle, speed, fire, shadowDistance, distance,1, CHARACTER::MONSTER, 15, "FlyBullet");
		if (isleft(ENEMY->GetPlayer()->getPt().x))
		{
			pMon->setAni(ANIMATION->findAnimation("leftAtkfly"));
			ANIMATION->start("leftAtkfly");
		}
		else
		{
			pMon->setAni(ANIMATION->findAnimation("rightAtkfly"));
			ANIMATION->start("rightAtkfly");
		}
	}
	if (count == 65)
	{
		if (isleft(ENEMY->GetPlayer()->getPt().x))
		{
			pMon->setAni(ANIMATION->findAnimation("leftfly"));
			ANIMATION->start("leftfly");
		}
		else
		{
			pMon->setAni(ANIMATION->findAnimation("rightfly"));
			ANIMATION->start("rightfly");
		}
	}

	count++;
	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (count > delay)
	{
		m_pFSM->ChangeState(STATE_TYPE::IDLE);
	}
}

void Fly_Atk::Exit()
{
}

bool Fly_Atk::isleft(float x)
{
	CObject* pMon = m_pFSM->GetMon();
	if (x - pMon->getPt().x <= 0)
	{
		return true;
	}
	else return false;
}

//=============================================공격상태=========================================================

Fly_Die::Fly_Die()
{
	m_eState = STATE_TYPE::DEAD;
}

Fly_Die::~Fly_Die()
{
}

void Fly_Die::Enter()
{
	//SOUND->pause("flysound");
}

void Fly_Die::update()
{
}

void Fly_Die::Exit()
{
}
