#pragma once
#include"singleton.h"

class C_bullet;
typedef vector<C_bullet*> vBullet;
typedef vector<C_bullet*>::iterator viBullet;
class bulletManager : public Singleton<bulletManager>
{
private:
	vBullet vbullet;
	viBullet vibullet;
public:
	bulletManager();
	~bulletManager();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:
	vBullet getvBullet() { return vbullet; }
	viBullet getviBullet(int number);

public:
	void fire(vector2 _pt, vector2 _size, int _damage, float _speed, float _angle, int _distance, int _count, string _bulletType, bool _playerBullet, bool _justOne, bool _isLeft);
	void eraserBullet(int number) { vbullet.erase(vbullet.begin() + number); }
	void eraserAllBullet() { vbullet.clear(); }
};

