#include "framework.h"
#include "goodsItem.h"

//goodsItem::goodsItem()
//{
//}
//
//goodsItem::~goodsItem()
//{
//}
//
//HRESULT goodsItem::init()
//{
//	return E_NOTIMPL;
//}
//
//void goodsItem::release()
//{
//}
//
//void goodsItem::update()
//{
//}
//
//void goodsItem::render()
//{
//}

C_Gold::C_Gold()
{
}

C_Gold::C_Gold(vector2 _pt)
{
	pt = _pt;
	collider = new C_collider(pt, {20,20});
	itemType = ITEM_TYPE::GOODS;
	goodsType = GOODSITEM::GOLD;
}

C_Gold::~C_Gold()
{
}

HRESULT C_Gold::init()
{
	return S_OK;
}

void C_Gold::release()
{
}

void C_Gold::update()
{
}

void C_Gold::render()
{
	IMAGE->findImage("gold")->render(getCVOSDC(), pt.x, pt.y);
}
