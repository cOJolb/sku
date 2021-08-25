#include "framework.h"
#include "skulItem.h"

C_skulItem::C_skulItem()
{
	itemType = ITEM_TYPE::SKUL;
}

C_skulItem::~C_skulItem()
{
}

HRESULT C_skulItem::init()
{
	return S_OK;
}

void C_skulItem::release()
{
}

void C_skulItem::update()
{
}

void C_skulItem::render()
{
}



C_crownskul::C_crownskul()
{
}

C_crownskul::C_crownskul(vector2 _pt)
{
	pt = _pt;
}

C_crownskul::~C_crownskul()
{
}

void C_crownskul::render()
{
}
