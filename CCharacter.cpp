#include "framework.h"
#include "CCharacter.h"

#include"CFSM.h"
#include"PooterState.h"
#include"HopperState.h"
#include"HostState.h"
#include"WormState.h"
#include"MulliganState.h"
#include"GurdyState.h"
#include"SmallflyState.h"
#include"PlayerState.h"
CCharacter::CCharacter() :
	CObject(), hp(0)
{
}

CCharacter::CCharacter(Vec2 _pos, RECT _rc, int _hp) :
	CObject(_pos, _rc), hp(_hp) , m_pAI(nullptr)
{
}

CCharacter::~CCharacter()
{
	SAFE_DELETE(m_pAI);
	Safe_Delete_Vector(vAI);
}

HRESULT CCharacter::init()
{
	CObject::init();
	hp = 0;
	return S_OK;
}

HRESULT CCharacter::init(vector2 _pt, RECT _rc, vector2 _objectPt, vector2 _objectSize, float _shadowdistance, vector2 _objectShadowPt, vector2 _objectShadowSize, int _hp)
{
	CObject::init(_pt, _rc, _objectPt, _objectSize, _shadowdistance, _objectShadowPt, _objectShadowSize);
	hp = _hp;
	return S_OK;
}

void CCharacter::AI_init(CCharacter* monster, MONSTER_TYPE type)
{
	m_pAI = new CFSM(monster);
	switch (type)
	{
	case MONSTER_TYPE::FLY:
		m_pAI->AddState(new Fly_Idle);
		m_pAI->AddState(new Fly_Trace);
		m_pAI->AddState(new Fly_Atk);
		m_pAI->AddState(new Fly_Die);
		m_pAI->SetState(STATE_TYPE::IDLE);
		break;
	case MONSTER_TYPE::HOPPER:

		m_pAI->AddState(new Hopper_Idle);
		m_pAI->AddState(new Hopper_Trace);
		m_pAI->AddState(new Hopper_Atk);
		m_pAI->AddState(new Hopper_Die);
		m_pAI->SetState(STATE_TYPE::IDLE);
		break;
	case MONSTER_TYPE::HOST:

		m_pAI->AddState(new Host_Idle);
		m_pAI->AddState(new Host_Trace);
		m_pAI->AddState(new Host_Atk);
		m_pAI->AddState(new Host_Die);
		m_pAI->SetState(STATE_TYPE::IDLE);
		break;
	case MONSTER_TYPE::MULLIGAN:
		m_pAI->AddState(new Mulligan_Idle);
		m_pAI->AddState(new Mulligan_Trace);
		m_pAI->AddState(new Mulligan_Atk);
		m_pAI->AddState(new Mulligan_Die);
		m_pAI->SetState(STATE_TYPE::IDLE);
		break;
	case MONSTER_TYPE::WORM:
		m_pAI->AddState(new Worm_idle);
		m_pAI->AddState(new Worm_trace);
		m_pAI->AddState(new Worm_Atk);
		m_pAI->AddState(new Worm_Die);
		m_pAI->SetState(STATE_TYPE::IDLE);
		break;
	case MONSTER_TYPE::GURDY:
		m_pAI->AddState(new Gurdy_Idle);
		m_pAI->AddState(new Gurdy_Trace);
		m_pAI->AddState(new Gurdy_Atk);
		m_pAI->AddState(new Gurdy_Die);
		m_pAI->SetState(STATE_TYPE::IDLE);
		break;
	case MONSTER_TYPE::SMALLFLY:
		m_pAI->AddState(new Smallfly_Idle);
		m_pAI->AddState(new Smallfly_Trace);
		m_pAI->AddState(new Smallfly_Atk);
		m_pAI->AddState(new Smallfly_Die);
		m_pAI->SetState(STATE_TYPE::IDLE);
		break;
	case MONSTER_TYPE::NONE:
		m_pAI->AddState(new Player_Idle);
		m_pAI->AddState(new Player_Trace);
		m_pAI->AddState(new Player_Atk);
		m_pAI->AddState(new Player_Die);
		m_pAI->SetState(STATE_TYPE::IDLE);
		break;
	default:
		break;
	}
}

void CCharacter::AI_update()
{
	m_pAI->update();
}

STATE_TYPE CCharacter::getstate()
{
	STATE_TYPE st = m_pAI->getState()->GetStateType();
	return st;
}

