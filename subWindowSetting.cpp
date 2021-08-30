#include "framework.h"
#include "subWindowSetting.h"

C_subWindowSetting::C_subWindowSetting()
{
}

C_subWindowSetting::~C_subWindowSetting()
{
}

HRESULT C_subWindowSetting::init()
{
	currentIdx = 0;
	mapToolSetUp();
	return S_OK;
}

void C_subWindowSetting::release()
{
}

void C_subWindowSetting::update()
{
    if (SUBWINDOW->GetIsActive() && InputManager->isStayKeyDown(VK_LBUTTON)) setMap();

    if (currentIdx != SUBWINDOW->GetFrameIndex())
    {
        currentIdx = SUBWINDOW->GetFrameIndex();
        mapToolSetUp();
    }
}

void C_subWindowSetting::render()
{

    TCHAR currentSelect[64];
    wsprintf(currentSelect, "monster : {%d,%d}  obj : {%d,%d}  room : {%d,%d}",
        SUBWINDOW->GetMonsterFrame().x, SUBWINDOW->GetMonsterFrame().y, SUBWINDOW->GetObjFrame().x, SUBWINDOW->GetObjFrame().y,
        SUBWINDOW->GetRoomFrame().x, SUBWINDOW->GetRoomFrame().y);
    TextOut(SUBWINDOW->getDC(), 10, 270, currentSelect, strlen(currentSelect));

    Rectangle(SUBWINDOW->getDC(), 0, 300, SUBWINSIZEX, SUBWINSIZEY);

    switch (SUBWINDOW->GetFrameIndex())
    {
    case 0:
       /* for (int i = 0; i < MONSTERTILEY; i++)
        {
            for (int j = 0; j < MONSTERTILEX; j++)
            {
                Rectangle(hdc, monsterTile[i * OBJECTTILEX + j].rcTile.left,
                    monsterTile[i * OBJECTTILEX + j].rcTile.top,
                    monsterTile[i * OBJECTTILEX + j].rcTile.right,
                    monsterTile[i * OBJECTTILEX + j].rcTile.bottom);
            }
        }
        IMAGE->render("monsterTile", hdc, 0, 300);*/
        Rectangle(SUBWINDOW->getDC(), 0, 200, SUBWINSIZEX, SUBWINSIZEY);
        break;
    case 1:
        /*for (int i = 0; i < OBJECTTILEY; i++)
        {
            for (int j = 0; j < OBJECTTILEX; j++)
            {
                Rectangle(hdc, objTile[i * OBJECTTILEX + j].rcTile.left,
                    objTile[i * OBJECTTILEX + j].rcTile.top,
                    objTile[i * OBJECTTILEX + j].rcTile.right,
                    objTile[i * OBJECTTILEX + j].rcTile.bottom);
            }
        }
        IMAGE->render("objectTile", hdc, 0, 300);*/
        Rectangle(SUBWINDOW->getDC(), 0, 100, SUBWINSIZEX, SUBWINSIZEY);
        break;
    case 2:
        /*for (int i = 0; i < ROOMTILEY; i++)
        {
            for (int j = 0; j < ROOMTILEX; j++)
            {
                Rectangle(hdc, roomTile[i * ROOMTILEX + j].rcTile.left,
                    roomTile[i * ROOMTILEX + j].rcTile.top,
                    roomTile[i * ROOMTILEX + j].rcTile.right,
                    roomTile[i * ROOMTILEX + j].rcTile.bottom);
            }
        }
        IMAGE->render("roomTile", hdc, 0, 300);*/
        Rectangle(SUBWINDOW->getDC(), 0, 50, SUBWINSIZEX, SUBWINSIZEY);
        break;
    case 3:
        break;
    }
}

void C_subWindowSetting::mapToolSetUp()
{
    memset(objTile, 0, sizeof(objTile));
    memset(monsterTile, 0, sizeof(monsterTile));
    memset(roomTile, 0, sizeof(roomTile));

    switch (currentIdx)
    {
    case 0:
       /* for (int i = 0; i < MONSTERTILEY; i++)
        {
            for (int j = 0; j < MONSTERTILEX; j++)
            {
                monsterTile[i * MONSTERTILEX + j].frame.x = j;
                monsterTile[i * MONSTERTILEX + j].frame.y = i;

                monsterTile[i * MONSTERTILEX + j].rcTile =
                    RectMake(
                        36 * j, 300 + 36 * i,
                        36, 36);
            }
        }*/
        break;
    case 1:
        /*for (int i = 0; i < OBJECTTILEY; i++)
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
        }*/
        break;
    case 2:
        /*for (int i = 0; i < ROOMTILEY; i++)
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
        }*/
        break;
    }
}

void C_subWindowSetting::setMap()
{
    for (int i = 0; i < 10; i++)
    {
       /* if (PtInRect(&objTile[i].rcTile, SUBWIN->GetMousePos()))
        {
            SUBWIN->SetObjFrame(PointMake(objTile[i].frame.x, objTile[i].frame.y));
        }*/
    }
    for (int i = 0; i <10; i++)
    {
       /* if (PtInRect(&monsterTile[i].rcTile, SUBWIN->GetMousePos()))
        {
            SUBWIN->SetMonsterFrame(PointMake(monsterTile[i].frame.x, monsterTile[i].frame.y));
        }*/
    }
    for (int i = 0; i < 10; i++)
    {
      /*  if (PtInRect(&roomTile[i].rcTile, SUBWIN->GetMousePos()))
        {
            SUBWIN->SetRoomFrame(PointMake(roomTile[i].frame.x, roomTile[i].frame.y));
        }*/
    }
}
