#include "framework.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CStage.h"
#include "CObstacle.h"
#include "CMinimap.h"
#include "UseItem.h"
#include "RandomMapGenerator.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	for (int i = 0; i < 100; i++)
		SAFE_DELETE(room[i]);
	//SAFE_DELETE(player);
	rnd->release();
	SAFE_DELETE(rnd);
}

void CStage::update()
{
	curRoom->update();
	player->update();
	playerEnterDoor();
	
	COLLISION->stageCollision(player);
	COLLISION->isMonsterDie();
	COLLISION->isBossDie();
	nextStage();

	if (InputManager->isOnceKeyDown('Z'))
	{
		ENEMY->eraserAllEnemy();
	}
	if (InputManager->isOnceKeyDown('H'))
	{
		ITEM->respawnItem(ITEM_TYPE::ITEM_MOMSLIPSTICK, { MAPSIZEX / 2,MAPSIZEY / 2 });
	}
	if (InputManager->isOnceKeyDown('J'))
	{
		ITEM->respawnItem(ITEM_TYPE::ITEM_BLOODBAG, { MAPSIZEX / 2,MAPSIZEY / 2 });
	}
	if (InputManager->isOnceKeyDown('K'))
	{
		ITEM->respawnItem(ITEM_TYPE::ITEM_PENTAGRAM, { MAPSIZEX / 2,MAPSIZEY / 2 });
	}
	if (InputManager->isOnceKeyDown('L'))
	{
		ITEM->respawnItem(ITEM_TYPE::ITEM_SPEEDBALL, { MAPSIZEX / 2,MAPSIZEY / 2 });
	}
	if (InputManager->isOnceKeyDown('G'))
	{
		ITEM->respawnItem(ITEM_TYPE::ITEM_THEINNEREYE, { MAPSIZEX / 2,MAPSIZEY / 2 });
	}
}

void CStage::render()
{
	curRoom->render();
	player->render();

}

void CStage::release()
{
	for (int i = 0; i < 100; i++)
	{
		room[i]->release();
		SAFE_DELETE(room[i]);
	}
}

void CStage::enter()
{
	curRoomIdx = 0;
	player = new CPlayer;
	rnd = new RandomMapGenerator;

	rnd->mapGenerate();
	randomMapSetting();
	player->init();

	ALLUI->getMinimap()->eraseMinimap();
	ALLUI->setPlayer(player);
	ALLUI->setrandomMap(rnd);

	ALLUI->getMinimap()->setRND(rnd);
	ALLUI->getMinimap()->mapAttrSetting();
	
	ENEMY->SetPlayer(player);
	player->setRoomLink(curRoom);

	ITEM->setPlayer(player);

	SOUND->play("bgm", 1.0f);

	(*STAGE->getCurStage()->getCurRoom()->getviObstacle(40))->setObjType(OBJECT::OBJ_FIREPLACE);

}

void CStage::exit()
{
	SAFE_DELETE(player);
	SAFE_DELETE(rnd);
	for(int i = 0; i < 100; i++)
		SAFE_DELETE(room[i]);
}

void CStage::randomMapSetting()
{
	for (int i = 0; i < 100; i++)
		room[i] = new CMap(*rnd->getRNDGenMap(i));

	changeRoom(45);
}

void CStage::changeRoom(int roomNum)
{
	ENEMY->eraserAllEnemy();
	BULLET->eraserAll();
	ITEM->eraseAllItem();

	room[curRoomIdx] = curRoom;
	curRoomIdx = roomNum;
	curRoom = room[curRoomIdx];
	if (!curRoom->getIsMonCreate())
	{
		curRoom->setIsMonCreate(true);
		for (int i = 0; i < TILEX * TILEY; i++)
			curRoom->setMonster(curRoom->getTile()[i].monster, curRoom->getTile()[i].pt);
	}

}

void CStage::playerEnterDoor()
{
	DOOR_DIRECTION door_direction = COLLISION->doorCollision(curRoom, player);
	if(door_direction == DOOR_DIRECTION::TOP)
	{
		if (room[curRoomIdx - 10]->getRoomType() != ROOM::ROOM_NONE)
		{
			player->setPt(curRoom->getTile()[112].pt);
			changeRoom(curRoomIdx - 10);
		}
	}
	else if (door_direction == DOOR_DIRECTION::BOTTOM)
	{
		if (room[curRoomIdx + 10]->getRoomType() != ROOM::ROOM_NONE)
		{
			changeRoom(curRoomIdx + 10);
			player->setPt(curRoom->getTile()[22].pt);
		}
	}
	else if (door_direction == DOOR_DIRECTION::LEFT)
	{
		if (room[curRoomIdx - 1]->getRoomType() != ROOM::ROOM_NONE)
		{
			changeRoom(curRoomIdx - 1);
			player->setPt(curRoom->getTile()[73].pt);
		}
	}
	else if (door_direction == DOOR_DIRECTION::RIGHT)
	{
		if (room[curRoomIdx + 1]->getRoomType() != ROOM::ROOM_NONE)
		{
			changeRoom(curRoomIdx + 1);
			player->setPt(curRoom->getTile()[61].pt);
		}
	}
}

void CStage::nextStage()
{
	if (COLLISION->goalCollision(curRoom, player))
	{
		if(STAGE->getCurStageIdx() < STAGE->getvStage().size() - 1)
			STAGE->changeStage(STAGE->getCurStageIdx() + 1);
		else if (IDOK == MessageBox(m_hWnd, "확인 : 메인메뉴 / 취소 : 게임 종료", "게임 클리어!",
			MB_ICONQUESTION | MB_OKCANCEL))
		{
			SCENE->changeScene("mainMenu");
		}
		else
		{
			PostQuitMessage(0);
			return;
		}
	}
}
