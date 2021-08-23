#pragma once
#include"CState.h"
class CPlayer;
class Gurdy_Idle : public CState
{
private:
	bool Inrange(int range, Vec2 pt);
public:
	Gurdy_Idle();
	~Gurdy_Idle();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Gurdy_Trace : public CState
{
private:
	int count;
public:
	Gurdy_Trace();
	~Gurdy_Trace();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Gurdy_Atk : public CState
{
private:
	int paturn;
	
	bool escapeAtk;
	
	void FireBullet();
	void bossatk();
	float angle;
	int foward;
	Vec2 firePt;
	int animationcount;

	float speed;
	float height;
	float distance;
	int bulletsize;
public:
	Gurdy_Atk();
	~Gurdy_Atk();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};

class Gurdy_Die : public CState
{
private:
	int count;
public:
	Gurdy_Die();
	~Gurdy_Die();

	virtual void update();
	virtual void Enter();
	virtual void Exit();
};