#pragma once

class C_state;
class C_object;

class C_fsm
{
private:
	C_object* object;
	vector<C_state*> vState;
	C_state* CurState;

public:
	C_fsm(C_object* _object);
	~C_fsm();

public:
	void update();

public:
	void AddState(C_state* _state);
	void ChangeState(STATE_TYPE _eType);
	void SetState(STATE_TYPE _eType);
	C_state* getState() { return CurState; }
	C_object* getObject() { return object; }


};