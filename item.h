#pragma once
#include "object.h"
class C_player;
class C_item : public C_object
{
protected:
	ITEM_TYPE itemType;
	GOODSITEM goodsType;
	PASSIVEITEM passiveType;
	ACTIVEITEM activeType;
	SKUL_TYPE skulItemType;
private:

public:
	C_item();
	virtual~C_item();

public:
	virtual HRESULT init(C_player* _player);
	virtual void release(C_player* _player);
	virtual void update(C_player* _player);
	virtual void render();
	virtual void render(vector2 _pt);

public:
	ITEM_TYPE getItemType() { return itemType; }
	GOODSITEM getGoodsType() { return goodsType; }
	SKUL_TYPE getSkulItemType() { return skulItemType; }
};
