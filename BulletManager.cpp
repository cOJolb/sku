#include "framework.h"
#include "BulletManager.h"
#include "CBullet.h"
#include "CCollider.h"

HRESULT BulletManager::init()
{
	return S_OK;
}

void BulletManager::release()
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		SAFE_DELETE(_vBullet[i]);
	}
	_vBullet.clear();
}

void BulletManager::update()
{
	move();
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->update();
	}
}

void BulletManager::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->render();
	}
}

void BulletManager::fire(float _angle, float _speed, vector2 _pt, float _height, float _distance, float _damage, CHARACTER _type, int size, string _bulletType)
{
	// 총알 클래스 객체 하나를 동적으로 생성해서 초기화한 다음 vector에 추가
	CBullet* tempBullet = new CBullet;
	tempBullet->init(_angle, _speed, _pt, _height, _distance,_damage, _type, size, _bulletType);
	_vBullet.push_back(tempBullet);
}

void BulletManager::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		//(*_viBullet)->move();

		// 총알 RECT가 총알의 그림자 RECT와 충돌이 된다면
		if((*_viBullet)->getRC().bottom >= RectY((*_viBullet)->getshadow()))
		{
			removeBullet(_viBullet);
			break;
		}
	}
}

void BulletManager::removeBullet(viBullet iter)
{
	_vBullet.erase(iter);
}

void BulletManager::eraserAll()
{
	_vBullet.clear();
}

viBullet BulletManager::getviBullet(int number)
{
	_viBullet = _vBullet.begin() + number;
	return _viBullet;
}


