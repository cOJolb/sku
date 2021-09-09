#include "framework.h"
#include "miniMap.h"
#include "enemy.h"
#include "player.h"
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
	//Rectangle(getMemDC(), miniMapRect.left, miniMapRect.top, miniMapRect.right, miniMapRect.bottom);
	IMAGE->findImage("miniMapBack")->alphaFrameRenderCenter(getMemDC(), { WINSIZEX - 150, WINSIZEY - 100 }, 0, 0, 100);
	vitile = vtile.begin();
	for (vitile ; vitile < vtile.end(); vitile++)
	{
		if (vitile->type != OBSTACLE_TYPE::NONE && vitile->type != OBSTACLE_TYPE::START)
		{
			float x = (WINSIZEX - 300) + vitile->tileNumber % 30 * 10;
			float y = (WINSIZEY - 200) + vitile->tileNumber / 30 * 10;
			IMAGE->findImage("miniMap")->alphaFrameRenderCenter(getMemDC(), {x+5, y+5 }, 4, 0, 100);
		}
		else if (vitile->type == OBSTACLE_TYPE::NORMALDOOR)
		{
			float x = (WINSIZEX - 300) + vitile->tileNumber % 30 * 10;
			float y = (WINSIZEY - 200) + vitile->tileNumber / 30 * 10;
			IMAGE->findImage("miniMap")->alphaFrameRenderCenter(getMemDC(), { x + 5, y + 5 }, 1, 0, 100);
		}
	}
	for (int i = 0; i < ENEMY->getvEnemy().size(); i++)
	{
		//vector2 enemyPt = (*ENEMY->getviEnemy(i))->getPt();
		//vector2 enemyCollider = (*ENEMY->getviEnemy(i))->getCollider()->getSize();
		/*int enemyX = enemyPt.x / tileSize;
		int enemyY = (enemyPt.y + enemyCollider.y / 2 -3) / tileSize;*/
		float gamesizex = GameSizeX;
		float gamesizey = GameSizeY;
		float enemyptx = (*ENEMY->getviEnemy(i))->getPt().x;
		float enemypty = (*ENEMY->getviEnemy(i))->getPt().y  + (*ENEMY->getviEnemy(i))->getCollider()->getSize().y/2 - 18;
		float X = enemyptx / (gamesizex /300.0f) + (gamesizex - 300);
		float Y = enemypty / (gamesizey /200.0f) + (gamesizey - 200);

		/*RECT miniEnemy = RectMake((WINSIZEX - 300) + enemyX * 10, (WINSIZEY - 200) + enemyY * 10, 10, 10);
		Rectangle(getMemDC(), miniEnemy.left, miniEnemy.top, miniEnemy.right, miniEnemy.bottom);*/
		IMAGE->findImage("miniMap")->alphaFrameRenderCenter(getMemDC(), { X,Y }, 3, 0, 100);
	}
	//int playerX = PLAYERDATA->getPlayerData()->getPt().x / tileSize;
	//int playerY = PLAYERDATA->getPlayerData()->getPt().y / tileSize;

	float gamesizex = GameSizeX;
	float gamesizey = GameSizeY;
	float playerx = PLAYERDATA->getPlayerData()->getPt().x;
	float playery = PLAYERDATA->getPlayerData()->getPt().y;
	float pX = playerx / (gamesizex / 300.0f) + (gamesizex - 300);
	float pY = playery / (gamesizey / 200.0f) + (gamesizey - 200);

	/*miniPlayer = RectMake((WINSIZEX - 300) + playerX * 10, (WINSIZEY - 200) + playerY *10, 10, 10);
	Rectangle(getMemDC(), miniPlayer.left, miniPlayer.top, miniPlayer.right, miniPlayer.bottom);*/

	IMAGE->findImage("miniMap")->alphaFrameRenderCenter(getMemDC(), { pX,pY }, 2, 0, 100);

	
}
