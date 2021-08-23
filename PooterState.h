#pragma once
#include"CState.h"
class BulletManager;
class enemyManager;
class CPlayer;
class Fly_Idle : public CState
{
	int count;
	int atkcount;
	int movetime;
	int delay;

	int foward;
	float parabola;
	float angle;
	float distance;

	bool idle;

	void Move();
	bool inrange(int range, vector2 pt);

public:
	Fly_Idle();
	virtual ~Fly_Idle();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};
class Fly_Trace : public CState
{
private:
public:
	Fly_Trace();
	virtual~Fly_Trace();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};
class Fly_Atk : public CState
{
private:

	int count;
	int delay;

	float angle;
	float speed;
	vector2 fire;
	int shadowDistance;
	int distance;

	bool isleft(float x);

public:
	Fly_Atk();
	virtual ~Fly_Atk();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Fly_Die : public CState
{
private:
public:
	Fly_Die();
	virtual ~Fly_Die();

	virtual void Enter();
	virtual void update();
	virtual void Exit();
};