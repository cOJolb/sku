#include "framework.h"
#include "MulliganState.h"
#include "BulletManager.h"
#include "enemyManager.h"
#include "CPlayer.h"

//=============================================대기상태=========================================================

Mulligan_Idle::Mulligan_Idle()
{
	m_eState = STATE_TYPE::IDLE;
	respawnCount = 0;
}

Mulligan_Idle::~Mulligan_Idle()
{
}

void Mulligan_Idle::Enter()
{
	count = 0;
	movetime = 5;
	foward = RND->getFromIntTo(0, 4);
	anistart = 0;
}

void Mulligan_Idle::update()
{
	CCharacter* pMon = m_pFSM->GetMon();
	Move();
	respawnCount++;
	if (respawnCount == 200)
	{
		EFFECT->play("poofeffect", pMon->getPt().x, pMon->getPt().y);
		ENEMY->respawn(MONSTER_TYPE::SMALLFLY, m_pFSM->GetMon()->getPt());
		respawnCount = 0;
	}
	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (Inrange(300, ENEMY->GetPlayer()->getPt()))
	{
		m_pFSM->ChangeState(STATE_TYPE::TRACE);
	}
}


void Mulligan_Idle::Exit()
{
}

void Mulligan_Idle::Move()
{
	CObject* pMon = m_pFSM->GetMon();
	RECT rec = pMon->getRC();
	count++;
	if (count > movetime)
	{
		count = 0;
 		movetime = RND->getFromIntTo(60, 200);
		foward = RND->getFromIntTo(0, 4);
		anistart = 1;
	}
	switch (foward)
	{
	case 0:
		if (count % 5 == 0)
		{
			movetoLeft(rec, 2);
		}
		//pMon->setAni(ANIMATION->findAnimation("lefthead"));
		pMon->setAni(ANIMATION->findAnimation("leftbody"));
		if (anistart)
		{
			ANIMATION->start("lefthead");
			ANIMATION->start("leftbody");
			anistart = 0;
		}
		break;
	case 1:
		if (count % 5 == 0)
		{
			movetoRight(rec, 2);
		}
		//pMon->setAni(ANIMATION->findAnimation("righthead"));
		pMon->setAni(ANIMATION->findAnimation("rightbody"));
		if (anistart)
		{
			ANIMATION->start("righthead");
			ANIMATION->start("rightbody");
			anistart = 0;
		}
		break;
	case 2:
		if (count % 5 == 0)
		{
		movetoDown(rec, 2);
		}
		
		pMon->setAni(ANIMATION->findAnimation("downbody"));
		if (anistart)
		{
			ANIMATION->start("downbody");
			anistart = 0;
		}
		break;
	case 3:
		if (count % 5 == 0)
		{
			movetoUp(rec, 2);
		}
		pMon->setAni(ANIMATION->findAnimation("upbody"));
		if (anistart)
		{
			ANIMATION->start("upbody");
			anistart = 0;
		}
		break;
	case 4:
		pMon->setAni(ANIMATION->findAnimation("mulliganidle"));
		if (anistart)
		{
			ANIMATION->start("mulliganidle");
			anistart = 0;
		}
		break;
	default:
		break;
	}

	pMon->setRC(rec);
	Vec2 p_monster;
	p_monster.x = RectX(rec);
	p_monster.y = RectY(rec);
	pMon->setPt(p_monster);

}

bool Mulligan_Idle::Inrange(int range, vector2 pt)
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
Mulligan_Trace::Mulligan_Trace()
{
	m_eState = STATE_TYPE::TRACE;
}

Mulligan_Trace::~Mulligan_Trace()
{
}

void Mulligan_Trace::Enter()
{
	count = 0;
	movetime = 32;
	delay = 50;

	jumpstart = 1;
	downstart = 1;
	idlestart = 1;
	idle = 0;

	parabola = 0;
	angle = 0.0f;
	distance = 0.0f;

	changefoward = true;
	foward = false;
	

}

void Mulligan_Trace::update()
{
	CCharacter* pMon = m_pFSM->GetMon();
	
	angle = UTIL::getAngle(pMon->getPt().x, pMon->getPt().y, ENEMY->GetPlayer()->getPt().x, ENEMY->GetPlayer()->getPt().y);
	

	if (foward != isleft(ENEMY->GetPlayer()->getPt()) )
	{
		changefoward = true;
	}
	if (isleft(ENEMY->GetPlayer()->getPt()))
	{
		if (changefoward)
		{
			//pMon->setAni(ANIMATION->findAnimation("righthead"));
			pMon->setAni(ANIMATION->findAnimation("rightbody"));
			ANIMATION->start("righthead");
			ANIMATION->start("rightbody");
			changefoward = false;
		}
	}
	else
	{
		if (changefoward)
		{
			//pMon->setAni(ANIMATION->findAnimation("lefthead"));
			pMon->setAni(ANIMATION->findAnimation("leftbody"));
			ANIMATION->start("lefthead");
			ANIMATION->start("leftbody");
			changefoward = false;
		}
	}
	Move_run();
	foward = isleft(ENEMY->GetPlayer()->getPt());
	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (!Inrange(300,ENEMY->GetPlayer()->getPt()))
	{
		m_pFSM->ChangeState(STATE_TYPE::IDLE);
	}
}


void Mulligan_Trace::Exit()
{
}


void Mulligan_Trace::Move_run()
{
	CObject* pMon = m_pFSM->GetMon();

	RECT rec = pMon->getRC();

	if (count % 3 == 0)
	{
		rec = RectMakeCenter(
			RectX(rec) + cosf(angle-PI) * 4,
			RectY(rec) - sinf(angle-PI) * 4,
			RectWidth(pMon->getRC()), RectHeight(pMon->getRC()));
	}
	
	pMon->setRC(rec);
	Vec2 p_monster;
	p_monster.x = RectX(rec);
	p_monster.y = RectY(rec);
	pMon->setPt(p_monster);

	count++;
}
bool Mulligan_Trace::Inrange(int range, vector2 pt)
{
	CObject* pMon = m_pFSM->GetMon();
	if (UTIL::getDistance(pMon->getPt().x, pMon->getPt().y, pt.x, pt.y) < range)
	{
		return true;
	}
	else return false;
}
bool Mulligan_Trace::isleft(vector2 pt)
{
	CObject* pMon = m_pFSM->GetMon();
	if (pt.x - pMon->getPt().x <= 0)
	{
		return true;
	}
	else return false;
}

bool Mulligan_Trace::isdown(vector2 pt)
{
	CObject* pMon = m_pFSM->GetMon();
	if (pt.y - pMon->getPt().y <= 0)
	{
		return true;
	}
	else return false;
}
//=============================================감지상태=========================================================



//=============================================공격상태=========================================================

Mulligan_Atk::Mulligan_Atk()
{
	m_eState = STATE_TYPE::ATTACK;
}

Mulligan_Atk::~Mulligan_Atk()
{
}

void Mulligan_Atk::update()
{
}

void Mulligan_Atk::Enter()
{
}

void Mulligan_Atk::Exit()
{
}
//=============================================공격상태=========================================================


//=============================================죽음상태=========================================================
Mulligan_Die::Mulligan_Die()
{
	m_eState = STATE_TYPE::DEAD;
}

Mulligan_Die::~Mulligan_Die()
{
}

void Mulligan_Die::update()
{
}

void Mulligan_Die::Enter()
{
	ENEMY->respawn(MONSTER_TYPE::SMALLFLY, m_pFSM->GetMon()->getPt());
}

void Mulligan_Die::Exit()
{
}

//=============================================죽음상태=========================================================