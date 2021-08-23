#pragma once
#include "singleton.h"

class CMap;
class mapManager : public Singleton<mapManager>
{
private:
	vector<CMap*> vNormalRoom;

	vector<CMap*> vBossRoom;

	vector<CMap*> vShopRoom;

	vector<CMap*> vRewardRoom;

	int maxRoomNum[(UINT)FILE_TYPE::END];
public:
	mapManager();
	~mapManager();

	HRESULT init();
	void release();
	void render();

	vector<CMap*> getNormalRoom() { return vNormalRoom; }
	vector<CMap*> getBossRoom() { return vBossRoom; }
	vector<CMap*> getShopRoom() { return vShopRoom; }
	int getMaxRoomNum(int type) { return maxRoomNum[type]; }
};