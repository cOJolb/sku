#pragma once
#include"singleton.h"

class CBullet;
class CCollider;
typedef vector<CBullet*> vBullet;
typedef vector<CBullet*>::iterator viBullet;
class BulletManager : public Singleton<BulletManager>
{
private :
	
private:
	vBullet _vBullet;
	viBullet _viBullet;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float _angle, float _speed, vector2 _pt, float _height, float _distance, float _damage, CHARACTER _type, int size, string _bulletType);
	void move();
	void removeBullet(viBullet iter);
	void eraserBullet(int number) { _vBullet.erase(_vBullet.begin() + number); }
	void eraserAll();

	vBullet getvBullet() { return _vBullet; }
	viBullet getviBullet(int number);
};