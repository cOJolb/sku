
#pragma once
#include"CState.h"

class Smallfly_Idle : public CState
{
private:
	int count;
	int atkcount;
	int movetime;
	int delay;

	int foward;
	float angle;
	float distance;

	bool idle;

	void Move();
	bool Inrange(int range, vector2 pt);

public:
	Smallfly_Idle();
	~Smallfly_Idle();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Smallfly_Trace : public CState
{
private:
	int count;

	float angle;

	void MovetoPlayer();
	bool Inrange(int range, vector2 pt);
	
public:
	Smallfly_Trace();
	~Smallfly_Trace();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Smallfly_Atk : public CState
{
private:

public:
	Smallfly_Atk();
	~Smallfly_Atk();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Smallfly_Die : public CState
{
private:
public:
	Smallfly_Die();
	~Smallfly_Die();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};