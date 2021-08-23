#pragma once
#include"CState.h"
class BulletManager;
class enemyManager;

class Host_Idle : public CState
{
private:
	bool inrange(int range, vector2 pt);
	bool crossrange(int range, vector2 pt);
public:
	Host_Idle();
	~Host_Idle();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};
class Host_Trace : public CState
{
private:
	int delay;
public:
	Host_Trace();
	~Host_Trace();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};
class Host_Atk :public CState
{
private:
	int count;
	int delay;

	float angle;
	float speed;
	vector2 fire;
	int shadowDistance;
	int distance;

	bool inrange(int range, vector2 pt);
	bool crossrange(int range, vector2 pt);
public:
	Host_Atk();
	~Host_Atk();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};
class Host_Die :public CState
{
private:

public:
	Host_Die();
	~Host_Die();
	virtual void update();
	virtual void Enter();
	virtual void Exit();
};