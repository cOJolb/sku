#pragma once
#include"enemy.h"
class C_knight : public C_enemy
{
protected:
private:
	int count;
public:
	C_knight();
	C_knight(vector2 _pt);
	virtual~C_knight();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:

};

