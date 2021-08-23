#pragma once
#include"CFSM.h"
#include"CCharacter.h"

class CFSM;
class CState
{
protected:
	CFSM* m_pFSM;
	STATE_TYPE m_eState;

public:
	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	STATE_TYPE GetStateType() { return m_eState; }
	void SetFSM(CFSM* _pFSM) { m_pFSM = _pFSM; }

public:
	CState();
	virtual ~CState();
};