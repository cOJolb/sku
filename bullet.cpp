#include "framework.h"
#include "bullet.h"

C_bullet::C_bullet()
{
}

C_bullet::C_bullet(vector2 _pt, vector2 _size, int _damage, float _speed, float _angle, int _distance, int _count, string _bulletType, bool _playerBullet, bool _justOne, bool _isLeft)
{
    angle = _angle;				// 발사 각도
    speed = _speed;				// 발사 속도
    distance = _distance;				// 발사 후 떨어지는 시점
    damage = _damage;			// 총알 데미지
    firePt = _pt;				// 발사 시작 점
    pt = _pt;
    bulletType = _bulletType;
    playerBullet = _playerBullet;
    justOne = _justOne;
    bulletOverDistance = false;
    bulletOverCount = false;
    frameX = 0;
    frameY = 0;
    count = 0;
    maxCount = _count;
    isLeft = _isLeft;
    collider = new C_collider(_pt, _size);
}

C_bullet::~C_bullet()
{
}

HRESULT C_bullet::init(vector2 _pt)
{
    return S_OK;
}

void C_bullet::release()
{
}

void C_bullet::update()
{
    bulletCount++;
    if (bulletCount >= maxCount) { bulletOverCount = true; }
    move();
    if (bulletType != "NONE")
    {
        countUpLoop(frameX, 0, IMAGE->findImage(bulletType + "Bullet")->getMaxFrameX(), count, 10);
    }
    if (isLeft) { frameY = 1; }
}

void C_bullet::render()
{
    if (bulletType != "NONE")
    {
        IMAGE->findImage(bulletType + "Bullet")->frameRenderCenter(getCVOSDC(), pt, frameX, frameY);
    }
}

void C_bullet::move()
{
    if (speed != 0)
    {
        pt.x += cosf(angle) * speed;
        pt.y -= sinf(angle) * speed;
    }
    collider->setPos(pt);
    if (UTIL::getDistance(firePt, pt) >= distance)
    {
        bulletOverDistance = true;
    }
}
