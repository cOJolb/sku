#include "framework.h"
#include "mapTool.h"

C_mapTool::C_mapTool()
{
    
    isDebug = false;
    room.roomType = ROOM::ROOM_NORMAL;
    mapToolSetup();
}

C_mapTool::~C_mapTool()
{
}

HRESULT C_mapTool::init()
{
    isDebug = false;
    room.roomType = ROOM::ROOM_NORMAL;
    mapToolSetup();
    return S_OK;
}

void C_mapTool::release()
{
}

void C_mapTool::update()
{
    if (!SUBWIN->GetIsActive() && InputManager->isOnceKeyDown(VK_LBUTTON))
    {
        //SOUND->play("selectobj");
        setMap();
    }
    //if (!SUBWIN->GetIsActive() && InputManager->isOnceKeyDown(VK_F5)) isDebug = !isDebug;
}

void C_mapTool::render()
{
    TCHAR str[128];
   /* switch (room.roomType)
    {
    case ROOM::ROOM_NORMAL:
        IMAGE->render("basement_normal", getMemDC(), 0, 0);
        break;
    case ROOM::ROOM_BOSS:
        IMAGE->render("basement_boss", getMemDC(), 0, 0);
        break;
    case ROOM::ROOM_SHOP:
        IMAGE->render("shop", getMemDC(), 0, 0);
        break;
    }*/

    for (int i = 0; i < tileX * tileY; i++)
    {
        /*if (isDebug)
            Rectangle(getMemDC(), room.tile[i].rcTile.left, room.tile[i].rcTile.top, room.tile[i].rcTile.right, room.tile[i].rcTile.bottom);*/
        if(room.tile[i].type != OBSTACLE_TYPE::NONE) IMAGE->frameRenderCenter("tile", getMemDC(), room.tile[i].pt, room.tile[i].objFrame.x, room.tile[i].objFrame.y);
        //IMAGE->frameRender("monsterTile", getMemDC(), room.tile[i].rcTile.left, room.tile[i].rcTile.top, room.tile[i].monsterFrame.x, room.tile[i].monsterFrame.y);
    }
}

bool C_mapTool::save(const char* fileName)
{
    HANDLE file;
    DWORD write;
    bool result;
    S_tagRoom save[1];

    file = CreateFile(fileName,
        GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    save[0] = room;
    result = WriteFile(file, save, sizeof(S_tagRoom), &write, NULL);

    CloseHandle(file);

    return result;
}

bool C_mapTool::load(const char* fileName)
{
    HANDLE file;
    DWORD read;
    bool result;
    S_tagRoom load[1];

    file = CreateFile(fileName,
        GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    result = ReadFile(file, load, sizeof(S_tagRoom), &read, NULL);
    room = load[0];

    CloseHandle(file);

    return result;
}

void C_mapTool::tileInit()
{
    for (int i = 0; i < tileX * tileY; i++)
    {
        //bool isWall = i < 15 || i % TILEX == 0 || i % TILEX == 14 || i > TILEX * TILEY - 15;
        //if (isWall) room.tile[i].obj = OBJECT::OBJ_WALL;
        //else room.tile[i].obj = OBJECT::OBJ_NONE;
        //room.tile[i].monster = MONSTER_TYPE::NONE;
        room.tile[i].type = OBSTACLE_TYPE::NONE;
        room.tile[i].objFrame = 0;
        //room.tile[i].monsterFrame = 0;
    }
}

void C_mapTool::mapToolSetup()
{
    for (int i = 0; i < tileX * tileY; i++)
    {
        room.tile[i].pt.x = (i % tileX) * tileSize;
        room.tile[i].pt.y = (i / tileX) * tileSize;
        room.tile[i].type = OBSTACLE_TYPE::NONE;
        room.tile[i].objFrame = 0;
        room.tile[i].tileNumber = i;
        room.tile[i].rc = RectMakeCenter(room.tile[i].pt, tileSize, tileSize);
  
    }
    //tileInit();
}

void C_mapTool::setMap()
{
    for (int i = 0; i < tileX * tileY; i++)
    {
        if (PtInRect(&room.tile[i].rc, m_ptMouse))
        {
            room.tile[i].objFrame = { static_cast<float>(SUBWIN->GetObjFrame().x), static_cast<float>(SUBWIN->GetObjFrame().y) };
            room.tile[i].type = objSelect(SUBWIN->GetObjFrame().x, SUBWIN->GetObjFrame().y);
            InvalidateRect(m_hWnd, NULL, false);
        }
    }
}

OBSTACLE_TYPE C_mapTool::objSelect(int frameX, int frameY)
{
    switch (frameY)
    {
    case 0:
        switch (frameX)
        {
        case 0:
            return OBSTACLE_TYPE::LT_LAND;
            break;
        case 1:
            return OBSTACLE_TYPE::LTC_LAND;
            break;
        case 2:
            return OBSTACLE_TYPE::RTC_LAND;
            break;
        case 3:
            return OBSTACLE_TYPE::RT_LAND;
            break;
        case 4:
            return OBSTACLE_TYPE::L_FLOOR;
            break;
        case 5:
            return OBSTACLE_TYPE::R_FLOOR;
            break;
        }
        break;
    case 1:
        switch (frameX)
        {
        case 0:
            return OBSTACLE_TYPE::L_LAND;
            break;
        case 1:
            return OBSTACLE_TYPE::LC_LAND;
            break;
        case 2:
            return OBSTACLE_TYPE::RC_LAND;
            break;
        case 3:
            return OBSTACLE_TYPE::R_LAND;
            break;
        case 4:
            return OBSTACLE_TYPE::RCA_LAND;
            break;
        case 5:
            return OBSTACLE_TYPE::RA_LAND;
            break;
        }
        break;
    case 2:
        switch (frameX)
        {
        case 0:
            return OBSTACLE_TYPE::TL_LAND;
            break;
        case 1:
            return OBSTACLE_TYPE::BL_LAND;
            break;
        case 2:
            return OBSTACLE_TYPE::BR_LAND;
            break;
        case 3:
            return OBSTACLE_TYPE::TR_LAND;
            break;
        case 4:
            return OBSTACLE_TYPE::NONE;
            break;
        case 5:
            return OBSTACLE_TYPE::NONE;
            break;
        }
        break;
    case 3:
        switch (frameX)
        {
        case 0:
            return OBSTACLE_TYPE::LBC_LAND;
            break;
        case 1:
            return OBSTACLE_TYPE::LB_LAND;
            break;
        case 2:
            return OBSTACLE_TYPE::RB_LAND;
            break;
        case 3:
            return OBSTACLE_TYPE::RBC_LAND;
            break;
        case 4:
            return OBSTACLE_TYPE::LA_LAND;
            break;
        case 5:
            return OBSTACLE_TYPE::LCA_LAND;
            break;
        }
        break;
    }
}
