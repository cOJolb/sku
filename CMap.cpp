#include"framework.h"
#include "CObstacle.h"
#include "CMap.h"

CMap::CMap() :
    isMonCreate(false), isClear(false),
    isCreateReward(false)
{
    tileSet();
}

CMap::CMap(const char* fileName) :
    isMonCreate(false), isClear(false),
    isCreateReward(false)
{
    load(fileName);
    tileSet();
}

CMap::CMap(CMap& map)
{
    for (int i = 0; i < TILEX * TILEY; i++)
        room.tile[i] = map.room.tile[i];
    
    room.roomType = map.room.roomType;

    for (int i = 0; i < map.vObstacle.size(); i++)
    {
        CObstacle* tempObstacle = new CObstacle(map.vObstacle[i]);
        vObstacle.push_back(tempObstacle);
    }

    roomAttr = map.roomAttr;
    markAttr = map.markAttr;
    isMonCreate = map.isMonCreate;
    isClear = map.isClear;
}

CMap::CMap(CMap* map)
{
    for (int i = 0; i < TILEX * TILEY; i++)
        room.tile[i] = map->room.tile[i];

    room.roomType = map->room.roomType;

    for (int i = 0; i < map->vObstacle.size(); i++)
    {
        CObstacle* tempObstacle = new CObstacle(map->vObstacle[i]);
        vObstacle.push_back(tempObstacle);
    }

    roomAttr = map->roomAttr;
    markAttr = map->markAttr;
    isMonCreate = map->isMonCreate;
    isClear = map->isClear;
}

CMap::~CMap()
{
    vObstacle.clear();
    Safe_Delete_Vector(vObstacle);
}

HRESULT CMap::init()
{
    tileSet();
    return S_OK;
}

HRESULT CMap::init(const char* fileName)
{
    load(fileName);
    tileSet();
    return S_OK;
}

void CMap::release()
{
    vObstacle.clear();
    Safe_Delete_Vector(vObstacle);
}

void CMap::update()
{
    doorOpenClose();
    createReward();
    for (viObstacle = vObstacle.begin(); viObstacle != vObstacle.end(); viObstacle++)
    {
        (*viObstacle)->update();
    }
}

void CMap::render()
{
    switch(room.roomType)
    {
    case ROOM::ROOM_FIRST:
        IMAGE->render("basement_first", getMemDC(), 0, 0);
        break;
    case ROOM::ROOM_REWARD:
    case ROOM::ROOM_NORMAL:
        IMAGE->render("basement_normal", getMemDC(), 0, 0);
        break;
    case ROOM::ROOM_BOSS:
        IMAGE->render("basement_boss", getMemDC(), 0, 0);
        break;
    case ROOM::ROOM_SHOP:
        IMAGE->render("shop", getMemDC(), 0, 0);
        break;
    }
    for (viObstacle = vObstacle.begin(); viObstacle != vObstacle.end(); viObstacle++)
    {
        (*viObstacle)->render();
    }
}

void CMap::load(const char* fileName)
{
    HANDLE file;
    DWORD read;
    tagRoom load[1];

    file = CreateFile(fileName,
        GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    ReadFile(file, load, sizeof(tagRoom), &read, NULL);
    room = load[0];

    CloseHandle(file);
}

void CMap::tileSet()
{
    for (size_t i = 0; i < TILEY; i++)
    {
        for (size_t j = 0; j < TILEX; j++)
        {
            SetRect(&room.tile[i * TILEX + j].rcTile,
                j * TILEWIDTH + MAPSTARTX,
                i * TILEHEIGHT + MAPSTARTY,
                j * TILEWIDTH + TILEWIDTH + MAPSTARTX,
                i * TILEHEIGHT + TILEHEIGHT + MAPSTARTY);

            room.tile[i * TILEX + j].pt.x = RectX(room.tile[i * TILEX + j].rcTile);
            room.tile[i * TILEX + j].pt.y = RectY(room.tile[i * TILEX + j].rcTile);
        }
    }

    for (int i = 0; i < TILEX * TILEY; i++)
    {
        CObstacle* tempObstacle = new CObstacle(room.tile[i].pt,
                RectMakeCenter(room.tile[i].pt, TILEWIDTH, TILEHEIGHT),
                room.tile[i].obj);

        vObstacle.push_back(tempObstacle);
    }
}

void CMap::doorSetting(DOOR_DIRECTION direction)
{
    switch (direction)
    {
    case DOOR_DIRECTION::TOP:
        room.tile[7].obj = OBJECT::OBJ_CLOSETOPDOOR;
        vObstacle[7]->setObjType(OBJECT::OBJ_CLOSETOPDOOR);
        break;
    case DOOR_DIRECTION::LEFT:
        room.tile[60].obj = OBJECT::OBJ_CLOSELEFTDOOR;
        vObstacle[60]->setObjType(OBJECT::OBJ_CLOSELEFTDOOR);
        break;
    case DOOR_DIRECTION::RIGHT:
        room.tile[74].obj = OBJECT::OBJ_CLOSERIGHTDOOR;
        vObstacle[74]->setObjType(OBJECT::OBJ_CLOSERIGHTDOOR);
        break;
    case DOOR_DIRECTION::BOTTOM:
        room.tile[127].obj = OBJECT::OBJ_CLOSEBOTTOMDOOR;
        vObstacle[127]->setObjType(OBJECT::OBJ_CLOSEBOTTOMDOOR);
        break;
    }
}

void CMap::doorOpenClose()
{
    if (!isClear && ENEMY->getvmonster().size() == 0)
    {
        isClear = true;
        if (vObstacle[7]->getObjType() == OBJECT::OBJ_CLOSETOPDOOR)
            vObstacle[7]->setObjType(OBJECT::OBJ_TOPDOOR);

        if (vObstacle[60]->getObjType() == OBJECT::OBJ_CLOSELEFTDOOR)
            vObstacle[60]->setObjType(OBJECT::OBJ_LEFTDOOR);

        if (vObstacle[74]->getObjType() == OBJECT::OBJ_CLOSERIGHTDOOR)
            vObstacle[74]->setObjType(OBJECT::OBJ_RIGHTDOOR);

        if (vObstacle[127]->getObjType() == OBJECT::OBJ_CLOSEBOTTOMDOOR)
            vObstacle[127]->setObjType(OBJECT::OBJ_BOTTOMDOOR);
    }
}

void CMap::createReward()
{
    if (room.roomType == ROOM::ROOM_REWARD && !isCreateReward)
    {
        isCreateReward = true;
        ITEM->respawnItem(static_cast<ITEM_TYPE>(RND->getFromIntTo(5, 9)), room.tile[67].pt);
    }
}

void CMap::setMonster(MONSTER_TYPE type, vector2 pt)
{
    ENEMY->respawnMinion(type, pt);
}

TDviObstacle CMap::getviObstacle(int number)
{
    viObstacle = vObstacle.begin() + number;
    return viObstacle;
}
