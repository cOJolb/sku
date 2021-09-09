#pragma once
#include"state.h"
class BigEnt_Idle : public C_state
{
private:
protected:
	int count;
	int atkDelay;
public:
	BigEnt_Idle();
	~BigEnt_Idle();

public:
	void enter();
	void update();
	void exit();
};
class BigEnt_Trace : public C_state
{
private:
public:
	BigEnt_Trace();
	~BigEnt_Trace();

public:
	void enter();
	void update();
	void exit();
};

class BigEnt_Atk : public C_state
{
private:
	int atkType;
	int delay;
	bool foward;
public:
	BigEnt_Atk();
	~BigEnt_Atk();

public:
	void enter();
	void update();
	void exit();
};

class BigEnt_Die : public C_state
{
private:

public:
	BigEnt_Die();
	~BigEnt_Die();

public:
	void enter();
	void update();
	void exit();
};

class BigEnt_Damage : public C_state
{
private:
	int delay;
	bool foward;
public:
	BigEnt_Damage();
	~BigEnt_Damage();

public:
	void enter();
	void update();
	void exit();
};
