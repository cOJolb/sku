#include "framework.h"
#include "enemyManager.h"
#include "enemy.h"
#include "knight.h"

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	viEnemy = vEnemy.begin();
	for (viEnemy; viEnemy != vEnemy.end(); ++viEnemy)
	{
		(*viEnemy)->update();
	}
}

void enemyManager::render()
{
	viEnemy = vEnemy.begin();
	for (viEnemy; viEnemy != vEnemy.end(); ++viEnemy)
	{
		(*viEnemy)->render();
	}
}

void enemyManager::respawnEnemy(UNIT_TYPE _type, vector2 _pt)
{
	C_enemy* monster;
	switch (_type)
	{
	case UNIT_TYPE::KNIGHT:
		monster = new C_knight(_pt);
		break;

	default:
		return;
		break;
	}

	vEnemy.push_back(monster);
}

vienemy enemyManager::getviEnemy(int number)
{
	viEnemy = vEnemy.begin() + number;
	return viEnemy;
}
