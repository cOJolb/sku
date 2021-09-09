#pragma once
#include "enemy.h"
class C_BigEnt : public C_enemy
{
protected:
private:
	int count;
public:
	C_BigEnt();
	C_BigEnt(vector2 _pt);
	virtual~C_BigEnt();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:
};
