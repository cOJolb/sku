#include "framework.h"
#include "CMapSettingSub.h"

CMapSettingSub::CMapSettingSub()
{
    mapToolSetup();
}

CMapSettingSub::~CMapSettingSub()
{
}

HRESULT CMapSettingSub::init()
{
    currentIdx = 0;
    mapToolSetup();
    return S_OK;
}

void CMapSettingSub::release()
{ }

void CMapSettingSub::update()
{
    if (SUBWIN->GetIsActive() && InputManager->isStayKeyDown(VK_LBUTTON)) setMap();

    if (currentIdx != SUBWIN->GetFrameIndex())
    {
        currentIdx = SUBWIN->GetFrameIndex();
        mapToolSetup();
    }
}

void CMapSettingSub::render(HDC hdc)
{
    TCHAR currentSelect[64];
    wsprintf(currentSelect, "monster : {%d,%d}  obj : {%d,%d}  room : {%d,%d}", 
        SUBWIN->GetMonsterFrame().x, SUBWIN->GetMonsterFrame().y, SUBWIN->GetObjFrame().x, SUBWIN->GetObjFrame().y,
        SUBWIN->GetRoomFrame().x, SUBWIN->GetRoomFrame().y);
    TextOut(hdc, 10, 270, currentSelect, strlen(currentSelect));

    Rectangle(hdc, 0, 300, SUBWINSIZEX, SUBWINSIZEY);

    switch (SUBWIN->GetFrameIndex())
    {
    case 0:
        for (int i = 0; i < MONSTERTILEY; i++)
        {
            for (int j = 0; j < MONSTERTILEX; j++)
            {
                Rectangle(hdc, monsterTile[i * OBJECTTILEX + j].rcTile.left,
                    monsterTile[i * OBJECTTILEX + j].rcTile.top,
                    monsterTile[i * OBJECTTILEX + j].rcTile.right,
                    monsterTile[i * OBJECTTILEX + j].rcTile.bottom);
            }
        }
        IMAGE->render("monsterTile", hdc, 0, 300);
        break;
    case 1:
        for (int i = 0; i < OBJECTTILEY; i++)
        {
            for (int j = 0; j < OBJECTTILEX; j++)
            {
                Rectangle(hdc, objTile[i * OBJECTTILEX + j].rcTile.left,
                    objTile[i * OBJECTTILEX + j].rcTile.top,
                    objTile[i * OBJECTTILEX + j].rcTile.right,
                    objTile[i * OBJECTTILEX + j].rcTile.bottom);
            }
        }
        IMAGE->render("objectTile", hdc, 0, 300);
        break;
    case 2:
        for (int i = 0; i < ROOMTILEY; i++)
        {
            for (int j = 0; j < ROOMTILEX; j++)
            {
                Rectangle(hdc, roomTile[i * ROOMTILEX + j].rcTile.left,
                    roomTile[i * ROOMTILEX + j].rcTile.top,
                    roomTile[i * ROOMTILEX + j].rcTile.right,
                    roomTile[i * ROOMTILEX + j].rcTile.bottom);
            }
        }
        IMAGE->render("roomTile", hdc, 0, 300);
        break;
    case 3:
        break;
    }
}

void CMapSettingSub::mapToolSetup()
{
    memset(objTile, 0, sizeof(objTile));
    memset(monsterTile, 0, sizeof(monsterTile));
    memset(roomTile, 0, sizeof(roomTile));

    switch (currentIdx)
    {
    case 0:
        for (int i = 0; i < MONSTERTILEY; i++)
        {
            for (int j = 0; j < MONSTERTILEX; j++)
            {
                monsterTile[i * MONSTERTILEX + j].frame.x = j;
                monsterTile[i * MONSTERTILEX + j].frame.y = i;

                monsterTile[i * MONSTERTILEX + j].rcTile =
                    RectMake(
                        TILEWIDTH * j, 300 + TILEHEIGHT * i,
                        TILEWIDTH, TILEHEIGHT);
            }
        }
        break;
    case 1:
        for (int i = 0; i < OBJECTTILEY; i++)
        {
            for (int j = 0; j < OBJECTTILEX; j++)
            {
                objTile[i * OBJECTTILEX + j].frame.x = j;
                objTile[i * OBJECTTILEX + j].frame.y = i;

                objTile[i * OBJECTTILEX + j].rcTile =
                    RectMake(
                        TILEWIDTH * j, 300 + TILEHEIGHT * i,
                        TILEWIDTH, TILEHEIGHT);
            }
        }
        break;
    case 2:
        for (int i = 0; i < ROOMTILEY; i++)
        {
            for (int j = 0; j < ROOMTILEX; j++)
            {
                roomTile[i * OBJECTTILEX + j].frame.x = j;
                roomTile[i * OBJECTTILEX + j].frame.y = i;

                roomTile[i * OBJECTTILEX + j].rcTile =
                    RectMake(
                        TILEWIDTH * j, 300 + TILEHEIGHT * i,
                        TILEWIDTH, TILEHEIGHT);
            }
        }
        break;
    }
}

void CMapSettingSub::setMap()
{
   for (int i = 0; i < OBJECTTILEX * OBJECTTILEY; i++)
   {
        if (PtInRect(&objTile[i].rcTile, SUBWIN->GetMousePos()))
        {
            SUBWIN->SetObjFrame(PointMake(objTile[i].frame.x, objTile[i].frame.y));
        }
   }
   for (int i = 0; i < MONSTERTILEX * MONSTERTILEY; i++)
   {
       if (PtInRect(&monsterTile[i].rcTile, SUBWIN->GetMousePos()))
       {
           SUBWIN->SetMonsterFrame(PointMake(monsterTile[i].frame.x, monsterTile[i].frame.y));
       }
   }
   for (int i = 0; i < ROOMTILEX * ROOMTILEY; i++)
   {
       if (PtInRect(&roomTile[i].rcTile, SUBWIN->GetMousePos()))
       {
           SUBWIN->SetRoomFrame(PointMake(roomTile[i].frame.x, roomTile[i].frame.y));
       }
   }
}
