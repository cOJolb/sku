#pragma once
#include"CState.h"
class Player_Idle : public CState
{
private:
public:
	Player_Idle();
	~Player_Idle();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};
class Player_Trace : public CState
{
private:
	int count;
public:
	Player_Trace();
	~Player_Trace();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Player_Atk : public CState
{
private:
	int count;
public:
	Player_Atk();
	~Player_Atk();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Player_Die : public CState
{
private:
	int count;
public:
	Player_Die();
	~Player_Die();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

