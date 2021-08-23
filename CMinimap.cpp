#include "framework.h"
#include "CMinimap.h"
#include "CStage.h"
#include "CMap.h"
#include "RandomMapGenerator.h"

CMinimap::CMinimap()
{
	memset(map, 0, sizeof(map));

	int startX = 700;
	int startY = 0;


	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			SetRect(&map[i * 10 + j].rc,
				j * MINIMAPROOMX + startX,
				i * MINIMAPROOMY + startY,
				j * MINIMAPROOMX + startX + MINIMAPROOMX,
				i * MINIMAPROOMY + startY + MINIMAPROOMY);
		}
	}
}

CMinimap::~CMinimap()
{
	SAFE_DELETE(rnd);
}

HRESULT CMinimap::init()
{

	return S_OK;
}

void CMinimap::release()
{

}

void CMinimap::update()
{
	CStage* curMap = STAGE->getCurStage();

	if (curRoomIdx != curMap->getCurRoomIdx())
	{
		map[curRoomIdx].roomAttr = ROOM_TYPE_ATTR::VISITROOM;
		curRoomIdx = curMap->getCurRoomIdx();
		map[curRoomIdx].roomAttr = ROOM_TYPE_ATTR::CURROOM;
	}
}

void CMinimap::render()
{
	int frameX;
	for (int i = 0; i < 100; i++)
	{
		frameX = -1;
		if (map[i].roomAttr == ROOM_TYPE_ATTR::CURROOM)
			frameX = 1;
		if (map[i].roomAttr == ROOM_TYPE_ATTR::NONCHECK)
			frameX = 2;
		if (map[i].roomAttr == ROOM_TYPE_ATTR::VISITROOM)
			frameX = 0;
		IMAGE->alphaFrameRender("minimapRoom", getMemDC(), map[i].rc.left, map[i].rc.top, frameX, 0, 200);
		frameX = -1;
		if (map[i].markAttr == ROOM_MARK_ATTR::NONEMARK)
			frameX = 0;
		if (map[i].markAttr == ROOM_MARK_ATTR::BOSS)
			frameX = 1;
		if (map[i].markAttr == ROOM_MARK_ATTR::REWARD)
			frameX = 2;
		if (map[i].markAttr == ROOM_MARK_ATTR::SHOP)
			frameX = 3;
		IMAGE->alphaFrameRender("minimapMark", getMemDC(), map[i].rc.left, map[i].rc.top, frameX, 0, 200);
	}
}

void CMinimap::mapAttrSetting()
{
	for (int i = 0; i < 100; i++)
	{
		if (i == 45)
		{
			map[i].roomAttr = ROOM_TYPE_ATTR::CURROOM;
			curRoomIdx = i;
		}
		else if (rnd->getRNDGenMap(i)->getRoomAttr() == ROOM_TYPE_ATTR::NONCHECK)
			map[i].roomAttr = ROOM_TYPE_ATTR::NONCHECK;

		if (rnd->getRNDGenMap(i)->getMarkAttr() == ROOM_MARK_ATTR::BOSS)
			map[i].markAttr = ROOM_MARK_ATTR::BOSS;
		if (rnd->getRNDGenMap(i)->getMarkAttr() == ROOM_MARK_ATTR::SHOP)
			map[i].markAttr = ROOM_MARK_ATTR::SHOP;
		if (rnd->getRNDGenMap(i)->getMarkAttr() == ROOM_MARK_ATTR::REWARD)
			map[i].markAttr = ROOM_MARK_ATTR::REWARD;
	}
}

void CMinimap::eraseMinimap()
{
	for (int i = 0; i < 100; i++)
	{
		map[i].markAttr = ROOM_MARK_ATTR::NONEMARK;
		map[i].roomAttr = ROOM_TYPE_ATTR::NONEROOM;
	}
}
