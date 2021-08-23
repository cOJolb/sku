#pragma once
#include "CMap.h"
#include <queue>
#include <stack>
class RandomMapGenerator
{
private:
	CMap* room[100];

	bool started;
	bool placedSpecial;
	bool isMapCompleted;

	queue<int> cellQueue;
	vector<int> endRoom;

	bool floorplan[100];
	int floorplanCount;

	int maxRooms;
	int minRooms;

	int bossRoomNum;
	int shopRoomNum;
	int rewardRoomNum;
public:
	RandomMapGenerator();
	~RandomMapGenerator();

	HRESULT init();
	void release();
	void start();
	void update();

	bool visit(int roomNumber);
	int neighbourCount(int roomNumber);
	int popRandomEndRoom();

	void roomSetting();
	void mapGenerate();

	CMap* getRNDGenMap(int arrNum) { return room[arrNum]; }
	vector<int> getEndRoom() { return endRoom; }
	int getFloorplanCount() { return floorplanCount; }
	bool* getFloorplan() { return floorplan; }
};