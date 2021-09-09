#pragma once
#include"state.h"
class Bigknight_Idle : public C_state
{
private:
protected:
	int count;
public:
	Bigknight_Idle();
	~Bigknight_Idle();

public:
	void enter();
	void update();
	void exit();
};
class Bigknight_Trace : public C_state
{
private:
public:
	Bigknight_Trace();
	~Bigknight_Trace();

public:
	void enter();
	void update();
	void exit();
};

class Bigknight_Atk : public C_state
{
private:
	int delay;
	bool foward;
	int atkType;
	bool skillA;
public:
	Bigknight_Atk();
	~Bigknight_Atk();

public:
	void enter();
	void update();
	void exit();
};

class Bigknight_Die : public C_state
{
private:

public:
	Bigknight_Die();
	~Bigknight_Die();

public:
	void enter();
	void update();
	void exit();
};

class Bigknight_Damage : public C_state
{
private:
	int delay;
	bool foward;
public:
	Bigknight_Damage();
	~Bigknight_Damage();

public:
	void enter();
	void update();
	void exit();
};
