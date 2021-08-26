#include "framework.h"
#include "mapSetting.h"

C_mapSetting::C_mapSetting()
{
	for (int i = 0; i < 30*20; i++)
	{
		tile[i].pt.x = (i % 30) * 36;
		tile[i].pt.y = (i / 30) * 36;
		tile[i].type = OBSTACLE_TYPE::NONE;
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
