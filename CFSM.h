#pragma once

class CState;
class CCharacter;

class CFSM
{
private:
	CCharacter* m_pMon;
	vector<CState*> m_vecState;
	CState* m_pCurState;

public:
	void update();

public:
	void AddState(CState* _pState);
	void ChangeState(STATE_TYPE _eType);
	void SetState(STATE_TYPE _eType);
	CState* getState() { return m_pCurState; }
	CCharacter* GetMon() { return m_pMon; }

public:
	CFSM(CCharacter* _pMon);
	~CFSM();
};