#pragma once
#include "object.h"
class C_bullet : public C_object
{
private:
	bool playerBullet;
	bool justOne;
	bool isLeft;

	float angle;				// 발사 각도
	float speed;				// 발사 속도
	//float fallingHeight;		// 발사 후 떨어지는 높이
	float distance;				// 발사 후 떨어지는 시점
	vector2 firePt;				// 발사 시작 점
	bool bulletOverDistance;
	bool bulletOverCount;

	int count;
	int bulletCount;
	int maxCount;
	string bulletType;
public:
	C_bullet();
	C_bullet(vector2 _pt, vector2 _size, int _damage, float _speed, float _angle, int _distance,int _count, string _bulletType, bool _playerBullet, bool _justOne, bool _isLeft);
	~C_bullet();

public:
	virtual HRESULT init(vector2 _pt);
	virtual void release();
	virtual void update();
	virtual void render();

public:
	bool getOverDistance() { return bulletOverDistance; }
	bool getOverCount() { return bulletOverCount; }
	bool getPlayerBullet() { return playerBullet; }
	bool getJustOne() { return justOne; }
	void move();
};

