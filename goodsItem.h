#pragma once
#include "item.h"
//class goodsItem : public C_item
//{
//protected:
//	GOODSITEM goodstype;
//private:
//public:
//	goodsItem();
//	~goodsItem();
//
//public:
//	HRESULT init();
//	void release();
//	void update();
//	void render();
//
//public:
//	GOODSITEM getGoodsItem() { return goodstype; }
//};

class C_Gold : public C_item
{
protected:
private:
public:
	C_Gold();
	C_Gold(vector2 _pt);
	~C_Gold();
public:
	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};