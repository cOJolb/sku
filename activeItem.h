#pragma once
#include "item.h"
class C_player;
class C_littleBoneHead : public C_item
{
private:
	bool foward;
	bool isOnce;
public:
	//C_MedalOfCarleon();
	C_littleBoneHead(vector2 _pt);
	//~C_MedalOfCarleon();
public:
	//virtual HRESULT init(C_player* _player);
	//virtual void release(C_player* _player);
	virtual void update(C_player* _player);
	virtual void render();
	//virtual void render(vector2 _pt);
};
