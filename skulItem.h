#pragma once
#include "item.h"
class C_skulItem : public C_item
{
protected:
	SKULITEM skulItemType;
private:

public:
	C_skulItem();
	virtual~C_skulItem();

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	SKULITEM getskulType() { return skulItemType; }
};

class C_crownskul : public C_skulItem
{
public:
	C_crownskul();
	C_crownskul(vector2 _pt);
	virtual~C_crownskul();

public:
	void render();

};