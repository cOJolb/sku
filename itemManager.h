#pragma once

#include "singleton.h"
class C_item;

typedef vector <C_item*> vitem;
typedef vector <C_item*>::iterator viitem;

class itemManager : public Singleton<itemManager>
{
private:
	vitem vItem;
	viitem viItem;

	vitem vEquipItem;
	viitem viEquipItem;
public:
	itemManager();
	~itemManager();

public:
	HRESULT init();
	void release();
	void update(C_player* _player);
	void render();

public:
	void respawnPassiveItem(PASSIVEITEM _type, vector2 _pt);
	void respawnSkulItem(SKUL_TYPE _type, vector2 _pt);
	void respawnActiveItem(ACTIVEITEM _type, vector2 _pt);
	void respawnGoodsItem(GOODSITEM _type, vector2 _pt);
	void EquipPassiveItem(C_item* _passiveItem);

public:
	void itemRemove(int number);
	void EquipRemove(int number);
	void eraseAllItem();

public:
	vitem getvItem() { return vItem; }
	viitem getviItem(int number);
	vitem getvEquipItem() { return vEquipItem; }
	viitem getviEquipItem(int number);

public:
	void Equip(C_player* _player);
};

