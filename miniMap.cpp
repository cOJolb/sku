#include "framework.h"
#include "miniMap.h"

C_miniMap::C_miniMap()
{
	miniMapRect = RectMake(WINSIZEX - 300, WINSIZEY - 200, 300, 200);
}

C_miniMap::~C_miniMap()
{
}

HRESULT C_miniMap::init(S_tagTile _tile)
{
	//for (int i = 0; i < 30*20; i++)
	//{
	///*	if (_tile[i].type != OBSTACLE_TYPE::NONE)
	//	{
	//		S_tagTile tile;
	//		tile = _tile[i];
	//		vtile.push_back(tile);
	//	}*/
	//	S_tagTile tile;
	//	tile = _tile[i];
	//	vtile.push_back(tile);
	//}
	S_tagTile tile;
	tile = _tile;
	vtile.push_back(tile);

	return S_OK;
}

void C_miniMap::release()
{
}

void C_miniMap::update()
{

}

void C_miniMap::render()
{
	Rectangle(getMemDC(), miniMapRect.left, miniMapRect.top, miniMapRect.right, miniMapRect.bottom);
	vitile = vtile.begin();
	for (vitile ; vitile < vtile.end(); vitile++)
	{
		if (vitile->type != OBSTACLE_TYPE::NONE)
		{
			float x = (WINSIZEX - 300) + vitile->tileNumber % 30 * 10;
			float y = (WINSIZEY - 200) + vitile->tileNumber / 30 * 10;
			RECT rec;
			rec = RectMake(x, y, 10, 10);
			Rectangle(getMemDC(), rec.left, rec.top, rec.right, rec.bottom);
		}
	}
	int playerX = PLAYERDATA->getPlayerData().playerPt.x / 36;
	int playerY = PLAYERDATA->getPlayerData().playerPt.y / 36;

	miniPlayer = RectMake((WINSIZEX - 300) + playerX * 10, (WINSIZEY - 200) + playerY *10, 10, 10);
	Rectangle(getMemDC(), miniPlayer.left, miniPlayer.top, miniPlayer.right, miniPlayer.bottom);
}
