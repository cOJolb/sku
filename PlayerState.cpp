#include "framework.h"
#include "PlayerState.h"

Player_Idle::Player_Idle()
{
	m_eState = STATE_TYPE::IDLE;
}

Player_Idle::~Player_Idle()
{
}

void Player_Idle::Enter()
{
}

void Player_Idle::update()
{
}

void Player_Idle::Exit()
{
}

Player_Trace::Player_Trace()
{
	m_eState = STATE_TYPE::TRACE;
}

Player_Trace::~Player_Trace()
{
	
}

void Player_Trace::Enter()
{
	count = 0;
	CCharacter* character = m_pFSM->GetMon();
	character->setAni(ANIMATION->findAnimation("playerGetItem"));
	ANIMATION->start("playerGetItem");
}

void Player_Trace::update()
{
	count++;
	if (count > 80)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
}

void Player_Trace::Exit()
{
}

Player_Atk::Player_Atk()
{
	m_eState = STATE_TYPE::ATTACK;
}

Player_Atk::~Player_Atk()
{
}

void Player_Atk::Enter()
{
	count = 0;
	CCharacter* character = m_pFSM->GetMon();
	character->setAni(ANIMATION->findAnimation("playerisDamage"));
	ANIMATION->start("playerisDamage");
}

void Player_Atk::update()
{
	count++;
	CCharacter* character = m_pFSM->GetMon();
	if (count > 80)
	{
		m_pFSM->ChangeState(STATE_TYPE::IDLE);
	}
	else if (character->gethp() <= 0)
	{
		m_pFSM->ChangeState(STATE_TYPE::DEAD);
	}
}

void Player_Atk::Exit()
{
}

Player_Die::Player_Die()
{
	m_eState = STATE_TYPE::DEAD;
}

Player_Die::~Player_Die()
{
}

void Player_Die::Enter()
{
	count = 0;
	CCharacter* character = m_pFSM->GetMon();
	character->setAni(ANIMATION->findAnimation("playerisDie"));
	if (SOUND->isPlaySound("bossfight"))
		SOUND->stop("bossfight");
	ANIMATION->start("playerisDie");
	SOUND->play("playerdiesound");
	SOUND->stop("bgm");
	SOUND->play("playerdiebgm");
}

void Player_Die::update()
{
}

void Player_Die::Exit()
{
}
