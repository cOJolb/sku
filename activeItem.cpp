#include "framework.h"
#include "activeItem.h"
#include "player.h"
C_littleBoneHead::C_littleBoneHead(vector2 _pt)
{
	pt = _pt;
	collider = new C_collider(pt, { 15,15 });
	itemType = ITEM_TYPE::ACTIVE;
	activeType = ACTIVEITEM::LITTLEBONEHEAD;
	futureRc = RectMakeCenter(pt, collider->getSize().x, collider->getSize().y);
	futureRcLTRB();
	isOnce = false;
	foward = false;
}

void C_littleBoneHead::update(C_player* _player)
{
	isLand();
	isClogged();
	if (!isOnce) 
	{
		foward = _player->getisLeft();
		isOnce = true;
	}
	if (foward){ movetoLeft(futureRc, 4); }
	else { movetoRight(futureRc, 4); }
}

void C_littleBoneHead::render()
{
	IMAGE->findImage("littleBoneHead")->renderCenter(getCVOSDC(), pt);
}
