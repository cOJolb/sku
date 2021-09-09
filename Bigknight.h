#pragma once
#include "enemy.h"
class C_Bigknight : public C_enemy
{
protected:
private:
	int count;
public:
	C_Bigknight();
	C_Bigknight(vector2 _pt);
	virtual~C_Bigknight();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:
};
