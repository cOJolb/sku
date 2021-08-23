#pragma once
#include"gameNode.h"
class CObstacle;
typedef vector<CObstacle*> TDvObstacle;
typedef vector<CObstacle*>::iterator TDviObstacle;
class CMap : public gameNode
{
private:
	tagRoom room;
	TDvObstacle vObstacle;
	TDviObstacle viObstacle;

	ROOM_TYPE_ATTR roomAttr;
	ROOM_MARK_ATTR markAttr;
	bool isMonCreate;
	bool isClear;
	bool isCreateReward;
public:
	CMap();
	CMap(const char* fileName);
	CMap(CMap& map);
	CMap(CMap* map);
	~CMap();

	virtual HRESULT init();
	virtual HRESULT init(const char* fileName);
	virtual void release();
	virtual void update();
	virtual void render();

	void load(const char* fileName);
	void tileSet();
	void doorSetting(DOOR_DIRECTION direction);
	void doorOpenClose();
	void createReward();

	void setMonster(MONSTER_TYPE type, vector2 pt);
	
	ROOM_TYPE_ATTR getRoomAttr() { return roomAttr; }
	void setRoomAttr(ROOM_TYPE_ATTR attr) { roomAttr = attr; }

	ROOM_MARK_ATTR getMarkAttr() { return markAttr; }
	void setMarkAttr(ROOM_MARK_ATTR attr) { markAttr = attr; }

	TDvObstacle getvObstacle() { return vObstacle; }
	TDviObstacle getviObstacle(int number);

	tagTile* getTile() { return room.tile; }
	ROOM getRoomType() { return room.roomType; }
	void setRoomType(ROOM type) { room.roomType = type; }

	bool getIsMonCreate() { return isMonCreate; }
	void setIsMonCreate(bool isCreate) { isMonCreate = isCreate; }
};