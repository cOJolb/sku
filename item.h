#pragma once
#include "object.h"
class C_item : public C_object
{
protected:
	ITEM_TYPE itemType;
private:

public:
	C_item();
	virtual~C_item();

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	ITEM_TYPE getItemType() { return itemType; }
};

