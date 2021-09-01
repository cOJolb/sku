#pragma once
#include"fsm.h"
class C_state
{
protected:
	C_fsm* fsm;
	STATE_TYPE stateType;
	C_object* object;
protected:
	RECT _futureRc;
	int count;
	int movetime;
	bool Foward;
	bool prevFoward ;
public:
	C_state();
	virtual ~C_state();

public:

	virtual void enter() = 0;
	virtual void update() = 0;
	virtual void exit() = 0;

public:
	STATE_TYPE GetStateType() { return stateType; }
	void SetFSM(C_fsm* _fsm) { fsm = _fsm; }

public:
	bool inRange(int _range, vector2 _pt);
	bool isLeft(vector2 _pt);
	bool onLand(RECT _rc);
	void move();
	void move(bool _isLeft);
};

