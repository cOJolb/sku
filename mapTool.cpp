#include "framework.h"
#include "mapTool.h"

C_mapTool::C_mapTool() : isDebug(false)
{

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
    if (!SUBWINDOW->GetIsActive() && InputManager->isOnceKeyDown(VK_LBUTTON))
    {
        //SOUND->play("selectobj");
        setMap();
    }
    if (!SUBWINDOW->GetIsActive() && InputManager->isOnceKeyDown(VK_F5)) isDebug = !isDebug;

}

void C_mapTool::render()
{
    for (int i = 0; i < 30 * 20; i++)
    {
       // if (isDebug)
          Rectangle(getMemDC(), room.tile[i].rc.left, room.tile[i].rc.top, room.tile[i].rc.right, room.tile[i].rc.bottom);
       // IMAGE->frameRender("objectTile", getMemDC(), room.tile[i].rcTile.left, room.tile[i].rcTile.top, room.tile[i].objFrame.x, room.tile[i].objFrame.y);
      //  IMAGE->frameRender("monsterTile", getMemDC(), room.tile[i].rcTile.left, room.tile[i].rcTile.top, room.tile[i].monsterFrame.x, room.tile[i].monsterFrame.y);
    }
}

void C_mapTool::tileInit()
{
    for (int i = 0; i < 30 * 20; i++)
    {
      /*  bool isWall = i < 15 || i % TILEX == 0 || i % TILEX == 14 || i > TILEX * TILEY - 15;
        if (isWall) room.tile[i].obj = OBJECT::OBJ_WALL;
        else room.tile[i].type = OBSTACLE_TYPE::NONE;*/
      /*  room.tile[i].monster = MONSTER_TYPE::NONE;

        room.tile[i].objFrame = 0;
        room.tile[i].monsterFrame = 0;*/
    }
}

void C_mapTool::mapToolSetup()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            SetRect(&room.tile[i * 30 + j].rc,
               /* j * TILEWIDTH + MAPSTARTX,
                i * TILEHEIGHT + MAPSTARTY,
                j * TILEWIDTH + TILEWIDTH + MAPSTARTX,
                i * TILEHEIGHT + TILEHEIGHT + MAPSTARTY);*/
                j* 36 ,
                i* 36 ,
                j* 36 + 36 ,
                i* 36 + 36 );
        }
    }
}

void C_mapTool::setMap()
{
    for (int i = 0; i < 30 * 20; i++)
    {
       /* if (PtInRect(&room.tile[i].rcTile, m_ptMouse))
        {
            bool isNonMon = room.tile[i].monsterFrame.x == 0 && room.tile[i].monsterFrame.y == 0;
            bool isWall = room.tile[i].obj == OBJECT::OBJ_WALL;
            if (isNonMon && !isWall)
            {
                room.tile[i].objFrame = { static_cast<float>(SUBWIN->GetObjFrame().x), static_cast<float>(SUBWIN->GetObjFrame().y) };
                room.tile[i].obj = objSelect(SUBWIN->GetObjFrame().x, SUBWIN->GetObjFrame().y);
                InvalidateRect(m_hWnd, NULL, false);
            }
        }*/
        if (PtInRect(&room.tile[i].rc, m_ptMouse))
        {
            //room.tile[i].objFrame = { static_cast<float>(SUBWIN->GetObjFrame().x), static_cast<float>(SUBWIN->GetObjFrame().y) };
           // room.tile[i].obj = objSelect(SUBWIN->GetObjFrame().x, SUBWIN->GetObjFrame().y);
            InvalidateRect(m_hWnd, NULL, false);
        }
    }

   /* for (int i = 0; i < TILEX * TILEY; i++)
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
    }*/

    if (PtInRect(&RectMake({ 0, 0 }, WINSIZEX, WINSIZEY), m_ptMouse))
        room.roomType = (ROOM)SUBWINDOW->GetRoomFrame().x;
}

bool C_mapTool::save(const char* fileName)
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

bool C_mapTool::load(const char* fileName)
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

OBSTACLE_TYPE C_mapTool::objSelect(int frameX, int frameY)
{
	return OBSTACLE_TYPE();
}

MONSTER_TYPE C_mapTool::monsterSelect(int frameX, int frameY)
{
	return MONSTER_TYPE();
}
