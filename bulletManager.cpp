#include "framework.h"
#include "bulletManager.h"
#include "bullet.h"
bulletManager::bulletManager()
{
}

bulletManager::~bulletManager()
{
}

HRESULT bulletManager::init()
{
	return S_OK;
}

void bulletManager::release()
{
}

void bulletManager::update()
{
	vibullet = vbullet.begin();
	for (vibullet; vibullet != vbullet.end(); ++vibullet)
	{
		(*vibullet)->update();
	}
	for (int i = 0; i < vbullet.size(); i++)
	{
		vibullet = vbullet.begin() + i;
		if ((*vibullet)->getOverDistance() || (*vibullet)->getOverCount())
		{
			vbullet.erase(vbullet.begin()+i);
			break;
		}
	}
}

void bulletManager::render()
{
	vibullet = vbullet.begin();
	for (vibullet; vibullet != vbullet.end(); ++vibullet)
	{
		(*vibullet)->render();
	}
}

viBullet bulletManager::getviBullet(int number)
{
	vibullet = vbullet.begin() + number;
	return vibullet;
}

void bulletManager::fire(vector2 _pt, vector2 _size, int _damage, float _speed, float _angle, int _distance, int _count, string _bulletType, bool _playerBullet, bool _justOne, bool _isLeft)
{
	C_bullet* fireBullet = new C_bullet(_pt, _size, _damage, _speed, _angle, _distance, _count,_bulletType, _playerBullet, _justOne , _isLeft);
	vbullet.push_back(fireBullet);
}
