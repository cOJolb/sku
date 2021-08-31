#include "framework.h"
#include "obstacleManager.h"
#include "obstacle.h"
obstacleManager::obstacleManager()
{
}

obstacleManager::~obstacleManager()
{
}

HRESULT obstacleManager::init()
{
    return S_OK;
}

void obstacleManager::release()
{
}

void obstacleManager::update()
{
	vi_obstacle = v_obstacle.begin();
	for (vi_obstacle; vi_obstacle != v_obstacle.end(); ++vi_obstacle)
	{
		(*vi_obstacle)->update();
	}
}

void obstacleManager::render()
{
	vi_obstacle = v_obstacle.begin();
	for (vi_obstacle; vi_obstacle != v_obstacle.end(); ++vi_obstacle)
	{
		(*vi_obstacle)->render();
	}
}

void obstacleManager::createObstacle(OBSTACLE_TYPE _type, vector2 _pt, int _number)
{
    C_obstacle* obstacle;
    obstacle = new C_obstacle(_pt, _type, _number);
    v_obstacle.push_back(obstacle);
	if (obstacle->getisLand())
	{
		v_land.push_back(obstacle);
	}
	if (obstacle->getUnMovable())
	{
		v_wall.push_back(obstacle);
	}
}

viObstacle obstacleManager::getviObstacle(int number)
{
	vi_obstacle = v_obstacle.begin() + number;
	return vi_obstacle;
}

viObstacle obstacleManager::getviLand(int number)
{
	vi_land = v_land.begin() + number;
	return vi_land;
}

viObstacle obstacleManager::getviWall(int number)
{
	vi_wall = v_wall.begin() + number;
	return vi_wall;
}
