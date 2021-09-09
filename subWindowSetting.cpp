#include "framework.h"
#include "subWindowSetting.h"

C_subWindowSetting::C_subWindowSetting()
{
	mapToolSetup();
}

C_subWindowSetting::~C_subWindowSetting()
{
}

HRESULT C_subWindowSetting::init()
{
	return E_NOTIMPL;
}

void C_subWindowSetting::release()
{
}

void C_subWindowSetting::update()
{
    if (SUBWIN->GetIsActive() && InputManager->isStayKeyDown(VK_LBUTTON)) setMap();

    if (currentIdx != SUBWIN->GetFrameIndex())
    {
        currentIdx = SUBWIN->GetFrameIndex();
        mapToolSetup();
    }
}

void C_subWindowSetting::render(HDC hdc)
{
    TCHAR currentSelect[64];
    wsprintf(currentSelect, "monster : {%d,%d}  obj : {%d,%d}  room : {%d,%d}",
        SUBWIN->GetMonsterFrame().x, SUBWIN->GetMonsterFrame().y, SUBWIN->GetObjFrame().x, SUBWIN->GetObjFrame().y,
        SUBWIN->GetRoomFrame().x, SUBWIN->GetRoomFrame().y);
    TextOut(hdc, 10, 270, currentSelect, strlen(currentSelect));

    Rectangle(hdc, 0, 300, 420, 520);

    switch (SUBWIN->GetFrameIndex())
    {
    case 0:
        for (int i = 0; i < MonsterTileY; i++)
        {
            for (int j = 0; j < MonsterTileX; j++)
            {
                Rectangle(hdc, monsterTile[i * MonsterTileX + j].rc.left,
                    monsterTile[i * MonsterTileX + j].rc.top,
                    monsterTile[i * MonsterTileX + j].rc.right,
                    monsterTile[i * MonsterTileX + j].rc.bottom);
            }
        }
        IMAGE->render("monsterTile", hdc, 0, 300);
        break;
    case 1:
        for (int i = 0; i < ObstacleTileY; i++)
        {
            for (int j = 0; j < ObstacleTileX; j++)
            {
                Rectangle(hdc, objTile[i * ObstacleTileX + j].rc.left,
                    objTile[i * ObstacleTileX + j].rc.top,
                    objTile[i * ObstacleTileX + j].rc.right,
                    objTile[i * ObstacleTileX + j].rc.bottom);
            }
        }
        IMAGE->render("tile", hdc, 0, 300);
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
        break;
    case 3:
        break;
    }
}

void C_subWindowSetting::mapToolSetup()
{
    memset(objTile, 0, sizeof(objTile));
    memset(monsterTile, 0, sizeof(monsterTile));
    //memset(roomTile, 0, sizeof(roomTile));

    switch (currentIdx)
    {
    case 0:
        for (int i = 0; i < MonsterTileY; i++)
        {
            for (int j = 0; j < MonsterTileX; j++)
            {
                monsterTile[i * MonsterTileX + j].frame.x = j;
                monsterTile[i * MonsterTileX + j].frame.y = i;

                monsterTile[i * MonsterTileX + j].rc =
                    RectMake(
                        tileSize * j, 300 + tileSize * i,
                        tileSize, tileSize);
            }
        }
        break;
    case 1:
        for (int i = 0; i < ObstacleTileY; i++)
        {
            for (int j = 0; j < ObstacleTileX; j++)
            {
                objTile[i * ObstacleTileX + j].frame.x = j;
                objTile[i * ObstacleTileX + j].frame.y = i;

                objTile[i * ObstacleTileX + j].rc =
                    RectMake(
                        tileSize * j, 300 + tileSize * i,
                        tileSize, tileSize);
            }
        }
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
    for (int i = 0; i < ObstacleTileX * ObstacleTileY; i++)
    {
        if (PtInRect(&objTile[i].rc, SUBWIN->GetMousePos()))
        {
            SUBWIN->SetObjFrame(PointMake(objTile[i].frame.x, objTile[i].frame.y));
        }
    }
    for (int i = 0; i < MonsterTileX * MonsterTileY; i++)
    {
        if (PtInRect(&monsterTile[i].rc, SUBWIN->GetMousePos()))
        {
            SUBWIN->SetMonsterFrame(PointMake(monsterTile[i].frame.x, monsterTile[i].frame.y));
            SUBWIN->SetObjFrame(PointMake(4, 2));
        }
    }
}
