#pragma once

#include "singleton.h"
class C_item;
//class C_useItem;

typedef vector <C_item*> vitem;
typedef vector <C_item*>::iterator viitem;
//typedef vector <C_useItem*> vuseItem;
//typedef vector <C_useItem*>::iterator viuseItem;

class itemManager : public Singleton<itemManager>
{
private:
	vitem vItem;
	viitem viItem;
	//vuseItem vUseItem;
	//viuseItem viUseItem;
public:
	itemManager();
	~itemManager();

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	void respawnPassiveItem(PASSIVEITEM _type, vector2 _pt);
	void respawnSkulItem(SKULITEM _type, vector2 _pt);
	void respawnActiveItem(ACTIVEITEM _type, vector2 _pt);

	vitem getvItem() { return vItem; }
	viitem getviItem(int number);
	//vuseItem getvUseItem() { return vUseItem; }
	//viuseItem getviUseItem(int number);
	void itemRemove(int number);
	//void useItemRemove(int number);
	void eraseAllItem();

};

