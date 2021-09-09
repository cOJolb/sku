#pragma once
#include "object.h"
class C_bullet : public C_object
{
private:
	bool playerBullet;
	bool justOne;
	bool isLeft;

	float angle;				// �߻� ����
	float speed;				// �߻� �ӵ�
	//float fallingHeight;		// �߻� �� �������� ����
	float distance;				// �߻� �� �������� ����
	vector2 firePt;				// �߻� ���� ��
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

