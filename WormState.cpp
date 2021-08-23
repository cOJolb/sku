#include "framework.h"
#include "WormState.h"
#include "enemyManager.h"
#include "CPlayer.h"

//지렁이 대기
//=============================================대기상태=========================================================
Worm_idle::Worm_idle()
{
	m_eState = STATE_TYPE::IDLE;
}

Worm_idle::~Worm_idle()
{
}

void Worm_idle::Enter()
{
	count = 0;
	movetime = 5;
	foward = 0;
	anistart = 0;
	atk_count = 0;
}

void Worm_idle::update()
{
	CCharacter* pMon = m_pFSM->GetMon();
	Move();
	atk_count++;
	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (Inrange(300, ENEMY->GetPlayer()->getPt()) && Crossrange(50, ENEMY->GetPlayer()->getPt()) && atk_count > 400)
	{
		m_pFSM->ChangeState(STATE_TYPE::TRACE);
	}
}

void Worm_idle::Exit()
{

}
void Worm_idle::Move()
{
	CCharacter* pMon = m_pFSM->GetMon();
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
			/*pMon->setRC(movetoLeft(pMon->getRC(), 2));
			pMon->setPtX(pMon->getPtX() - 2);*/
			movetoLeft(rec, 2);
		}
		pMon->setAni(ANIMATION->findAnimation("leftworm"));
		if (anistart)
		{
			ANIMATION->start("leftworm");
			anistart = 0;
		}
		break;
	case 1:
		if (count % 5 == 0)
		{
			/*pMon->setRC(movetoRight(pMon->getRC(), 2));
			pMon->setPtX(pMon->getPtX() + 2);*/
			movetoRight(rec, 2);
		}
		pMon->setAni(ANIMATION->findAnimation("rightworm"));
		if (anistart)
		{
			ANIMATION->start("rightworm");
			anistart = 0;
		}
		break;
	case 2:
		if (count % 5 == 0)
		{
		/*	pMon->setRC(movetoDown(pMon->getRC(), 2));
			pMon->setPtY(pMon->getPtY() + 2);*/
			movetoDown(rec, 2);
		}
		pMon->setAni(ANIMATION->findAnimation("downworm"));
		if (anistart)
		{
			ANIMATION->start("downworm");
			anistart = 0;
		}
		break;
	case 3:
		if (count % 5 == 0)
		{
			/*pMon->setRC(movetoUp(pMon->getRC(), 2));
			pMon->setPtY(pMon->getPtY() - 2);*/
			movetoUp(rec, 2);
		}
		pMon->setAni(ANIMATION->findAnimation("upworm"));
		if (anistart)
		{
			ANIMATION->start("upworm");
			anistart = 0;
		}
		break;
	case 4:
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

bool Worm_idle::Inrange(int range, vector2 pt)
{
	CObject* pMon = m_pFSM->GetMon();
	if (UTIL::getDistance(pMon->getPt().x, pMon->getPt().y, pt.x, pt.y) < range)
	{
		return true;
	}
	else return false;
}

bool Worm_idle::Crossrange(int range, vector2 pt)
{
	CObject* pMon = m_pFSM->GetMon();

	bool horizontality = pt.y >= pMon->getPt().y - range && pt.y <= pMon->getPt().y + range;
	bool Perpendicular = pt.x >= pMon->getPt().x - range && pt.x <= pMon->getPt().x + range;
	if (horizontality || Perpendicular)
	{
		return true;
	}
	else return false;
}

//=============================================대기상태=========================================================



//=============================================감지상태=========================================================
//지렁이 따라옴
Worm_trace::Worm_trace()
{
	m_eState = STATE_TYPE::TRACE;
}

Worm_trace::~Worm_trace()
{
}

void Worm_trace::Enter()
{
	count = 0;
	movetime = 0;
	foward = 0;
	anistart = 0;
}

void Worm_trace::update()
{
	CCharacter* pMon = m_pFSM->GetMon();
	if (foward == 0)
	{
		setfoward(50, ENEMY->GetPlayer()->getPt());
	}
	Move();

	count++;
	if (pMon->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
	else if (count > 200)
	{
		m_pFSM->ChangeState(STATE_TYPE::IDLE);
	}
}

void Worm_trace::Exit()
{
}

void Worm_trace::Move()
{
	CObject* pMon = m_pFSM->GetMon();
	RECT rec = pMon->getRC();
	movetime++;
	if (count == 0)
	{
		anistart = 1;
	}
	switch (foward)
	{

	case 1:
		if (count % 3 == 0)
		{
			 movetoLeft(rec, 8);
		}
		pMon->setAni(ANIMATION->findAnimation("leftwormAtk"));
		if (anistart)
		{
			ANIMATION->start("leftwormAtk");
			anistart = 0;
		}
		break;
	case 2:
		if (count % 3 == 0)
		{
			movetoRight(rec, 8);
		}
		pMon->setAni(ANIMATION->findAnimation("rightwormAtk"));
		if (anistart)
		{
			ANIMATION->start("rightwormAtk");
			anistart = 0;
		}
		break;
	case 3:
		if (count % 3 == 0)
		{
		movetoDown(rec, 8);
		}
		pMon->setAni(ANIMATION->findAnimation("downwormAtk"));
		if (anistart)
		{
			ANIMATION->start("downwormAtk");
			anistart = 0;
		}
		break;
	case 4:
		if (count % 3 == 0)
		{
	
			movetoUp(rec, 8);
		}
		pMon->setAni(ANIMATION->findAnimation("upwormAtk"));
		if (anistart)
		{
			ANIMATION->start("upwormAtk");
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

int Worm_trace::setfoward(int range, vector2 pt)
{
	CObject* pMon = m_pFSM->GetMon();
	bool isleft = pt.x < pMon->getPt().x - range;
	bool isright = pt.x > pMon->getPt().x + range;
	bool isup = pt.y < pMon->getPt().y - range;
	bool isdown = pt.y > pMon->getPt().y + range;

	if (isleft) foward = 1;
	else if (isright) foward = 2;
	else if (isdown) foward = 3;
	else if (isup) foward = 4;

	return foward;
}

//=============================================감지상태=========================================================



Worm_Atk::Worm_Atk()
{
	m_eState = STATE_TYPE::ATTACK;
}

Worm_Atk::~Worm_Atk()
{
}

void Worm_Atk::update()
{
}

void Worm_Atk::Enter()
{
}

void Worm_Atk::Exit()
{
}

Worm_Die::Worm_Die()
{
	m_eState = STATE_TYPE::DEAD;
}

Worm_Die::~Worm_Die()
{
}

void Worm_Die::update()
{
}

void Worm_Die::Enter()
{

}

void Worm_Die::Exit()
{
}
