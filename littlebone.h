#pragma once
#include "skul.h"
class C_littlebone : public C_skul
{
private:
protected:
public:
	C_littlebone();
	~C_littlebone();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:
	virtual void playerAttack(vector2 _pt, bool _isLeft);
	virtual void playerDashMove(RECT& _rc, int& _DashCount, bool _DashJump, bool _DashFoward, float _DashSpeed);
	virtual void skillA();
	virtual void skillB();
};

