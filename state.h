#pragma once
#include"fsm.h"
class C_state
{
protected:
	C_fsm* fsm;
	STATE_TYPE stateType;

public:
	C_state();
	virtual ~C_state();

public:
	virtual void Enter() = 0;
	virtual void update() = 0;
	virtual void Exit() = 0;

public:
	STATE_TYPE GetStateType() { return stateType; }
	void SetFSM(C_fsm* _fsm) { fsm = _fsm; }

};

