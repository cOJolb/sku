#pragma once
#include "CObject.h"
#include "animation.h"
class CBullet : public CObject
{
private:
	float angle;				// 발사 각도
	float speed;				// 발사 속도
	float fallingHeight;		// 발사 후 떨어지는 높이
	float distance;				// 발사 후 떨어지는 시점
	int BULLETSIZE;				// 총알 크기
	int bulletDamage;			// 총알 데미지
	vector2 firePt;				// 발사 시작 점

	RECT shadow;
	vector2 shadowPt;

	CHARACTER type;

	image* bulletImage;
	animation* bulletAnimation;
	string bulletType;
	string bulletShadow;
public:
	CBullet();
	CBullet(Vec2 _pos, RECT _rc, float _angle, float _speed,float _distance, float _damage, int _height, CHARACTER _type, int size);
	~CBullet();

	virtual HRESULT init(float _angle, float _speed, vector2 _pt, float _height, float _distance, float _damage, CHARACTER _type, float size, string _bulletType);
	virtual void release();
	virtual void update();
	virtual void render();

	void move();

	float getAngle() { return angle; }
	void setAngle(float _angle) { angle = _angle; }

	float getSpeed() { return speed; }
	void setSpeed(float _speed) { speed = _speed; }
	int getDamage() { return bulletDamage; }

	vector2 getFirePt() { return firePt; }
	void setFirePt(vector2 pt) { firePt = pt; }

	RECT getshadow() { return shadow; }

	CHARACTER gettype() { return type; }
};