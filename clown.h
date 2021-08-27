#pragma once
#include "skul.h"
class C_clown : public C_skul
{
private:
protected:
public:
	C_clown();
	~C_clown();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:
	virtual void playerAttack();
	virtual void playerDashMove();
	virtual void skillA();
	virtual void skillB();
};

