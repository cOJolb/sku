#include "framework.h"
#include "CFSM.h"
#include "CState.h"


CFSM::CFSM(CCharacter* _pMon) : m_pMon(_pMon)
{
}

CFSM::~CFSM()
{
}

void CFSM::update()
{
	m_pCurState->update();
}

void CFSM::AddState(CState* _pState)
{
	_pState->SetFSM(this);
	m_vecState.push_back(_pState);
}

void CFSM::ChangeState(STATE_TYPE _eType)
{
	m_pCurState->Exit();

	for (UINT i = 0; i < m_vecState.size(); ++i)
	{
		if (_eType == m_vecState[i]->GetStateType())
		{
			m_pCurState = m_vecState[i];
			m_pCurState->Enter();
			return;
		}
	}

	assert(nullptr);
}

void CFSM::SetState(STATE_TYPE _eType)
{
	for (UINT i = 0; i < m_vecState.size(); ++i)
	{
		if (_eType == m_vecState[i]->GetStateType())
		{
			m_pCurState = m_vecState[i];
			m_pCurState->Enter();
			return;
		}
	}

	assert(nullptr);
}

