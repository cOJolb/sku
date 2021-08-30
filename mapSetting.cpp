#include "framework.h"
#include "mapSetting.h"

C_mapSetting::C_mapSetting()
{
	for (int i = 0; i < 30*20; i++)
	{
		tile[i].pt.x = (i % tileX) * tileSize;
		tile[i].pt.y = (i / tileX) * tileSize;
		tile[i].type = OBSTACLE_TYPE::NONE;
		tile[i].tileNumber = i;
	}
}

C_mapSetting::~C_mapSetting()
{
}

void C_mapSetting::init()
{
	for (int i = 0; i < 30 * 20; i++)
	{
		if (tile[i].type != OBSTACLE_TYPE::NONE) OBSTACLE->createObstacle(tile[i].type, tile[i].pt);
	}
}

void C_mapSetting::release()
{
}

void C_mapSetting::update()
{
}

void C_mapSetting::render()
{
}

void C_mapSetting::tileSet(int _number, OBSTACLE_TYPE _type)
{
	tile[_number].type = _type;
}
