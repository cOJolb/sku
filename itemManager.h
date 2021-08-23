#pragma once

#include "singleton.h"
class CItem;
class CUseItem;
class CPlayer;
typedef vector <CItem*> vItem;
typedef vector <CItem*>::iterator viItem;
typedef vector <CUseItem*> vUseItem;
typedef vector <CUseItem*>::iterator viUseItem;
class itemManager : public Singleton<itemManager>
{
private :
	vItem item;
	viItem iItem;

	vUseItem useItem;
	viUseItem viuseItem;

	CPlayer* player;
public :
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void respawnItem(ITEM_TYPE type, vector2 pos);
	void respawnUseItem(USE_ITEM type, vector2 pos);
	vItem getItem() { return item; }
	viItem getviItem(int number);
	vUseItem getUseItem() { return useItem; }
	viUseItem getviUseItem(int number);
	void itemRemove(int number);
	void useItemRemove(int number);

	void respawnRandomBasicItem(vector2 pos);
	void bombFire();

	void eraseAllItem();

	void setPlayer(CPlayer* _player) { player = _player; }
};

