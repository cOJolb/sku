#pragma once
#include "collider.h"
class C_skul
{
private:
protected:
	S_skulInfo skulInfo;
	string unitName;
	C_collider* attackRange;
	SKUL_TYPE type;
public:
	C_skul();
	~C_skul();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:
	virtual void playerDashMove(RECT& _rc, int& _DashCount, bool _DashJump, bool _DashFoward, float _DashSpeed);
	virtual void playerAttack(vector2 _pt, bool _isLeft);
	virtual void skillA();
	virtual void skillB();

public:
	S_skulInfo getskulInfo() { return skulInfo; }
	string getUnitName() { return unitName; }
	SKUL_TYPE getSkulType() { return type; }
};

