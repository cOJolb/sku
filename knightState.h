#pragma once
#include"state.h"
class knight_Idle : public C_state
{
private:
protected:
	int count;
public:
	knight_Idle();
	~knight_Idle();

public:
	void enter();
	void update();
	void exit();
};
class knight_Trace : public C_state
{
private:
public:
	knight_Trace();
	~knight_Trace();

public:
	void enter();
	void update();
	void exit();
};

class knight_Atk : public C_state
{
private:
	int delay;
	bool foward;
public:
	knight_Atk();
	~knight_Atk();

public:
	void enter();
	void update();
	void exit();
};

class knight_Die : public C_state
{
private:
	
public:
	knight_Die();
	~knight_Die();

public:
	void enter();
	void update();
	void exit();
};

class knight_Damage : public C_state
{
private:
public:
	knight_Damage();
	~knight_Damage();

public:
	void enter();
	void update();
	void exit();
};
