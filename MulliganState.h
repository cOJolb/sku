#pragma once
#include"CState.h"
class BulletManager;
class enemyManager;

class Mulligan_Idle :public CState
{
private:
	int count;
	int movetime;
	int foward;
	int respawnCount;
	bool anistart;

	void Move();
	bool Inrange(int range, vector2 pt);

public:
	Mulligan_Idle();
	~Mulligan_Idle();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Mulligan_Trace : public CState
{
private:
	int count;
	int movetime;
	int delay;

	float parabola;
	float angle;
	float distance;

	bool jumpstart;
	bool downstart;
	bool idlestart;

	bool idle;
	bool foward;
	bool changefoward;

	void Move_run();
	bool Inrange(int range, vector2 pt);
	bool isleft(vector2 pt);
	bool isdown(vector2 pt);

public:
	Mulligan_Trace();
	~Mulligan_Trace();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Mulligan_Atk : public CState
{
private:
public:
	Mulligan_Atk();
	~Mulligan_Atk();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Mulligan_Die : public CState
{
private:

public:
	Mulligan_Die();
	~Mulligan_Die();


	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

