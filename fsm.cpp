#include "framework.h"
#include "fsm.h"
#include "state.h"

C_fsm::C_fsm(C_object* _object)
{
	object = _object;
}

C_fsm::~C_fsm()
{
}

void C_fsm::update()
{
	CurState->update();
}

void C_fsm::AddState(C_state* _pState)
{
	_pState->SetFSM(this);
	vState.push_back(_pState);
}

void C_fsm::ChangeState(STATE_TYPE _eType)
{
	CurState->exit();

	for (UINT i = 0; i < vState.size(); ++i)
	{
		if (_eType == vState[i]->GetStateType())
		{
			CurState = vState[i];
			CurState->enter();
			return;
		}
	}

	assert(nullptr);
}

void C_fsm::SetState(STATE_TYPE _eType)
{
	for (UINT i = 0; i < vState.size(); ++i)
	{
		if (_eType == vState[i]->GetStateType())
		{
			CurState = vState[i];
			CurState->enter();
			return;
		}
	}

	assert(nullptr);
}
