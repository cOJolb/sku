#include "framework.h"
#include "skulItem.h"
#include "clown.h"
#include "littlebone.h"

C_crownskul::C_crownskul(vector2 _pt)
{
	pt = _pt;
	collider = new C_collider(pt, { 30,30 });
	itemType = ITEM_TYPE::SKUL;
	skulItemType = SKUL_TYPE::CLOWN;

}

void C_crownskul::render()
{
	IMAGE->findImage("clownHead")->renderCenter(getCVOSDC(), pt);
}

void C_crownskul::render(vector2 _pt)
{
	IMAGE->findImage("clownHead")->renderCenter(getMemDC(), _pt);
}

C_littleBoneskul::C_littleBoneskul(vector2 _pt)
{
	pt = _pt;
	collider = new C_collider(pt, { 30,30 });
	itemType = ITEM_TYPE::SKUL;
	skulItemType = SKUL_TYPE::SKUL;

}

void C_littleBoneskul::render()
{
	IMAGE->findImage("skulHead")->renderCenter(getCVOSDC(), pt);
}

void C_littleBoneskul::render(vector2 _pt)
{
	IMAGE->findImage("skulHead")->renderCenter(getMemDC(), _pt);
}
