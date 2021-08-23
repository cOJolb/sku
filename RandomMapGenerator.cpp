#include "framework.h"
#include "RandomMapGenerator.h"

RandomMapGenerator::RandomMapGenerator() :
	started(false), placedSpecial(false), isMapCompleted(false),
	floorplanCount(0),
	maxRooms(15), minRooms(4), bossRoomNum(-1), rewardRoomNum(-1),
	shopRoomNum(-1)
{
	ZeroMemory(room, sizeof(room));
	ZeroMemory(floorplan, sizeof(floorplan));
	endRoom.clear();

	for (int roomNum = 0; roomNum < 100; roomNum++)
	{
		room[roomNum] = new CMap;
	}
}

RandomMapGenerator::~RandomMapGenerator()
{
	for (int roomNum = 0; roomNum < 100; roomNum++)
		SAFE_DELETE(room[roomNum]);
}

HRESULT RandomMapGenerator::init()
{
	ZeroMemory(floorplan, sizeof(floorplan));

	memset(floorplan, 0, sizeof(floorplan));
	endRoom.clear();

	placedSpecial = false;
	isMapCompleted = false;
	floorplanCount = 0;

	return S_OK;
}

void RandomMapGenerator::release()
{
	for (int roomNum = 0; roomNum < 100; roomNum++)
		SAFE_DELETE(room[roomNum]);

}

void RandomMapGenerator::start()
{
	started = true;
	placedSpecial = false;
	init();
	visit(45);
}

void RandomMapGenerator::update()
{
	while (!isMapCompleted)
	{
		bool created = false;
		if (started)
		{
			if (cellQueue.size() > 0)
			{
				int roomNumber = cellQueue.front();
				cellQueue.pop();
				int roomLine = roomNumber % 10;

				if (roomLine > 1) created = created | visit(roomNumber - 1);
				if (roomLine < 9) created = created | visit(roomNumber + 1);
				if (roomNumber > 20) created = created | visit(roomNumber - 10);
				if (roomNumber < 70) created = created | visit(roomNumber + 10);
				if (!created)
					endRoom.push_back(roomNumber);
			}
			else if (!placedSpecial)
			{
				if (floorplanCount <= minRooms)
				{
					init();
					visit(45);
				}
				else if (endRoom.size() >= 3)
				{
					bossRoomNum = endRoom.back();
					endRoom.pop_back();

					rewardRoomNum = popRandomEndRoom();
					shopRoomNum = popRandomEndRoom();
					isMapCompleted = true;
				}
				else
				{
					init();
					visit(45);
				}
			}
		}
	}
}

bool RandomMapGenerator::visit(int roomNumber)
{
	if (floorplan[roomNumber])
		return false;

	int neighbours = neighbourCount(roomNumber);

	if (neighbours > 1)
		return false;

	if (floorplanCount >= maxRooms)
		return false;

	if ((float)RND->getInt(10) / 10.0 < 0.5 && roomNumber != 45)
		return false;

	cellQueue.push(roomNumber);
	floorplan[roomNumber] = true;
	floorplanCount += 1;

	return true;
}

int RandomMapGenerator::neighbourCount(int roomNumber)
{
	return floorplan[roomNumber - 10] +
		floorplan[roomNumber - 1] + 
		floorplan[roomNumber + 1] + 
		floorplan[roomNumber + 10];
}

int RandomMapGenerator::popRandomEndRoom()
{
	int idx = floor(RND->getFloat() * endRoom.size());
	int roomNum = endRoom[idx];
	endRoom.erase(endRoom.begin() + idx);
	return roomNum;
}

void RandomMapGenerator::roomSetting()
{
	for (int roomNum = 0; roomNum < 100; roomNum++)
	{
		int rndNum = -1;
		if (roomNum == bossRoomNum)
		{
			rndNum = RND->getInt(MAP->getMaxRoomNum((UINT)FILE_TYPE::BOSS));
			room[bossRoomNum] = new CMap(MAP->getBossRoom()[rndNum]);

			room[bossRoomNum]->setRoomAttr(ROOM_TYPE_ATTR::NONCHECK);
			room[bossRoomNum]->setMarkAttr(ROOM_MARK_ATTR::BOSS);
			room[bossRoomNum]->setRoomType(ROOM::ROOM_BOSS);
		}
		else if (roomNum == shopRoomNum)
		{
			rndNum = RND->getInt(MAP->getMaxRoomNum((UINT)FILE_TYPE::SHOP));
			room[shopRoomNum] = new CMap(MAP->getShopRoom()[rndNum]);

			room[shopRoomNum]->setRoomAttr(ROOM_TYPE_ATTR::NONCHECK);
			room[shopRoomNum]->setMarkAttr(ROOM_MARK_ATTR::SHOP);
			room[shopRoomNum]->setRoomType(ROOM::ROOM_SHOP);
			
		}
		else if (roomNum == rewardRoomNum)
		{
			rndNum = RND->getInt(MAP->getMaxRoomNum((UINT)FILE_TYPE::REWARD));
			room[rewardRoomNum] = new CMap(MAP->getShopRoom()[rndNum]);

			room[rewardRoomNum]->setRoomAttr(ROOM_TYPE_ATTR::NONCHECK);
			room[rewardRoomNum]->setMarkAttr(ROOM_MARK_ATTR::REWARD);
			room[roomNum]->setRoomType(ROOM::ROOM_REWARD);
		}
		else if (floorplan[roomNum])
		{
			if (roomNum == 45)
			{
				room[roomNum] = new CMap(MAP->getNormalRoom()[0]);
				room[roomNum]->setRoomType(ROOM::ROOM_FIRST);
			}
			else
			{
				rndNum = RND->getFromIntTo(1, MAP->getMaxRoomNum((UINT)FILE_TYPE::NORMAL)) - 1;
				room[roomNum] = new CMap(MAP->getNormalRoom()[rndNum]);
				room[roomNum]->setRoomType(ROOM::ROOM_NORMAL);
			}
			
			room[roomNum]->setRoomAttr(ROOM_TYPE_ATTR::NONCHECK);
		}
		else if (!floorplan[roomNum])
		{
			room[roomNum]->setRoomAttr(ROOM_TYPE_ATTR::NONEROOM);
			room[roomNum]->setRoomType(ROOM::ROOM_NONE);
		}
	}

	for (int roomNum = 0; roomNum < 100; roomNum++)
	{
		if (room[roomNum]->getRoomType() == ROOM::ROOM_NONE) continue;
		if (roomNum - 10 >= 0)
		{
			if (room[roomNum - 10]->getRoomType() != ROOM::ROOM_NONE)
			{
				room[roomNum]->doorSetting(DOOR_DIRECTION::TOP);
			}
		}
		if (roomNum + 10 < 100)
		{
			if (room[roomNum + 10]->getRoomType() != ROOM::ROOM_NONE)
			{
				room[roomNum]->doorSetting(DOOR_DIRECTION::BOTTOM);
			}

		}
		if (roomNum % 10 > 0)
		{

			if (room[roomNum - 1]->getRoomType() != ROOM::ROOM_NONE)
			{
				room[roomNum]->doorSetting(DOOR_DIRECTION::LEFT);
			}
		}
		if (roomNum % 10 < 9)
		{
			if (room[roomNum + 1]->getRoomType() != ROOM::ROOM_NONE)
			{
				room[roomNum]->doorSetting(DOOR_DIRECTION::RIGHT);
			}
		}
	}
}

void RandomMapGenerator::mapGenerate()
{
	start();
	update();
	roomSetting();
}
