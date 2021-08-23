#include "framework.h"
#include "CMapSetting.h"

CMapSetting::CMapSetting() : isDebug(false)
{
    mapToolSetup();
}

CMapSetting::~CMapSetting()
{
}

HRESULT CMapSetting::init()
{
    isDebug = false;
    room.roomType = ROOM::ROOM_NORMAL;
    mapToolSetup();
    return S_OK;
}

void CMapSetting::release()
{
}

void CMapSetting::update()
{
    if (!SUBWIN->GetIsActive() && InputManager->isOnceKeyDown(VK_LBUTTON))
    {
        SOUND->play("selectobj");
        setMap();
    }
    if (!SUBWIN->GetIsActive() && InputManager->isOnceKeyDown(VK_F5)) isDebug = !isDebug;
    
}

void CMapSetting::render()
{
    TCHAR str[128];
    switch (room.roomType)
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
    }
    
    for (int i = 0; i < TILEX * TILEY; i++)
    {
        if (isDebug)
            Rectangle(getMemDC(), room.tile[i].rcTile.left, room.tile[i].rcTile.top, room.tile[i].rcTile.right, room.tile[i].rcTile.bottom);
        IMAGE->frameRender("objectTile", getMemDC(), room.tile[i].rcTile.left, room.tile[i].rcTile.top, room.tile[i].objFrame.x, room.tile[i].objFrame.y);
        IMAGE->frameRender("monsterTile", getMemDC(), room.tile[i].rcTile.left, room.tile[i].rcTile.top, room.tile[i].monsterFrame.x, room.tile[i].monsterFrame.y);
    }
}

void CMapSetting::tileInit()
{
    for (int i = 0; i < TILEX * TILEY; i++)
    {
        bool isWall = i < 15 || i % TILEX == 0 || i % TILEX == 14 || i > TILEX * TILEY - 15;
        if (isWall) room.tile[i].obj = OBJECT::OBJ_WALL;
        else room.tile[i].obj = OBJECT::OBJ_NONE;
        room.tile[i].monster = MONSTER_TYPE::NONE;

        room.tile[i].objFrame = 0;
        room.tile[i].monsterFrame = 0;
    }
}

void CMapSetting::mapToolSetup()
{
    for (int i = 0; i < TILEY; i++)
    {
        for (int j = 0; j < TILEX; j++)
        {
            SetRect(&room.tile[i * TILEX + j].rcTile,
                j * TILEWIDTH + MAPSTARTX,
                i * TILEHEIGHT + MAPSTARTY,
                j * TILEWIDTH + TILEWIDTH + MAPSTARTX,
                i * TILEHEIGHT + TILEHEIGHT + MAPSTARTY);
        }
    }
    tileInit();
}

void CMapSetting::setMap()
{
    for (int i = 0; i < TILEX * TILEY; i++)
    {
        if (PtInRect(&room.tile[i].rcTile, m_ptMouse))
        {
            bool isNonMon = room.tile[i].monsterFrame.x == 0 && room.tile[i].monsterFrame.y == 0;
            bool isWall = room.tile[i].obj == OBJECT::OBJ_WALL;
            if (isNonMon && !isWall)
            {
                room.tile[i].objFrame = { static_cast<float>(SUBWIN->GetObjFrame().x), static_cast<float>(SUBWIN->GetObjFrame().y) };
                room.tile[i].obj = objSelect(SUBWIN->GetObjFrame().x, SUBWIN->GetObjFrame().y);
                InvalidateRect(m_hWnd, NULL, false);
            }
        }
    }

    for (int i = 0; i < TILEX * TILEY; i++)
    {
        if (PtInRect(&room.tile[i].rcTile, m_ptMouse))
        {
            bool isNonObj = room.tile[i].objFrame.x == 0 && room.tile[i].objFrame.y == 0;
            bool isWall = room.tile[i].obj == OBJECT::OBJ_WALL;
            if (isNonObj && !isWall)
            {
                room.tile[i].monster = monsterSelect(SUBWIN->GetMonsterFrame().x, SUBWIN->GetMonsterFrame().y);
                room.tile[i].monsterFrame = { static_cast<float>(SUBWIN->GetMonsterFrame().x), static_cast<float>(SUBWIN->GetMonsterFrame().y) };
                InvalidateRect(m_hWnd, NULL, false);
            }
        }
    }

    for (int i = 0; i < TILEX * TILEY; i++)
    {
        if (room.tile[i].monster == MONSTER_TYPE::GURDY)
        {
            bool isRightWall = room.tile[i + 1].obj == OBJECT::OBJ_WALL;
            if (isRightWall)
            {
                room.tile[i].monster = MONSTER_TYPE::NONE;
                room.tile[i].monsterFrame = 0;
                break;
            }

            room.tile[i].monster = monsterSelect(SUBWIN->GetMonsterFrame().x, SUBWIN->GetMonsterFrame().y);
            room.tile[i].monsterFrame = { static_cast<float>(SUBWIN->GetMonsterFrame().x), static_cast<float>(SUBWIN->GetMonsterFrame().y) };

            break;
        }
    }

    if (PtInRect(&RectMake({ 0, 0 }, WINSIZEX, WINSIZEY), m_ptMouse))
        room.roomType = (ROOM)SUBWIN->GetRoomFrame().x;
}

bool CMapSetting::save(const char* fileName)
{
    HANDLE file;
    DWORD write;
    bool result;
    tagRoom save[1];

    file = CreateFile(fileName,
        GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    save[0] = room;
    result = WriteFile(file, save, sizeof(tagRoom), &write, NULL);

    CloseHandle(file);

    return result;
}

bool CMapSetting::load(const char* fileName)
{
    HANDLE file;
    DWORD read;
    bool result;
    tagRoom load[1];

    file = CreateFile(fileName,
        GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    result = ReadFile(file, load, sizeof(tagRoom), &read, NULL);
    room = load[0];

    CloseHandle(file);

    return result;
}

OBJECT CMapSetting::objSelect(int frameX, int frameY)
{
    if (frameY == 0)
    {
        switch (frameX)
        {
        case 0:
            return OBJECT::OBJ_NONE;
            break;

        case 1:
            return OBJECT::OBJ_POOP;
            break;

        case 2:
            return OBJECT::OBJ_SPIKE;
            break;

        case 3:
            return OBJECT::OBJ_ROCK;
            break;

        case 4:
            return OBJECT::OBJ_STEEL;
            break;

        case 5:
            return OBJECT::OBJ_FIREPLACE;
            break;
        }
    }
    else if (frameY == 1)
    {
        switch (frameX)
        {
        case 0:
            return OBJECT::OBJ_LT_PIT;
            break;

        case 1:
            return OBJECT::OBJ_MT_PIT;
            break;

        case 2:
            return OBJECT::OBJ_RT_PIT;
            break;

        case 3:
            return OBJECT::OBJ_L_PIT;
            break;

        case 4:
            return OBJECT::OBJ_M_PIT;
            break;

        case 5:
            return OBJECT::OBJ_R_PIT;
            break;
        }
    }
    else if (frameY == 2)
    {
        switch (frameX)
        {
        case 0:
            return OBJECT::OBJ_LB_PIT;
            break;

        case 1:
            return OBJECT::OBJ_MB_PIT;
            break;

        case 2:
            return OBJECT::OBJ_RB_PIT;
            break;
        case 3:
        case 4:
        case 5:
            return OBJECT::OBJ_NONE;
            break;
        }
    }
}

MONSTER_TYPE CMapSetting::monsterSelect(int frameX, int frameY)
{
    if (frameY == 0)
    {
        switch (frameX)
        {
        case 0:
            return MONSTER_TYPE::NONE;
            break;
        case 1:
            return MONSTER_TYPE::WORM;
            break;
        case 2:
            return MONSTER_TYPE::FLY;
            break;
        case 3:
            return MONSTER_TYPE::HOST;
            break;
        case 4:
            return MONSTER_TYPE::HOPPER;
            break;
        case 5:
            return MONSTER_TYPE::MULLIGAN;
            break;
        case 6:
            return MONSTER_TYPE::GURDY;
            break;
        }
    }
}
