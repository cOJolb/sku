#pragma once
#include"state.h"
class knight_Idle : public C_state
{
private:
public:
	knight_Idle();
	~knight_Idle();

public:
	void enter();
	void update();
	void exit();
};
