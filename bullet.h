#pragma once
#include "object.h"
class C_bullet : public C_object
{
private:
	bool playerBullet;
public:
	C_bullet();
	~C_bullet();

public:
	virtual HRESULT init(vector2 _pt);
	virtual void release();
	virtual void update();
	virtual void render();

public:
	bool isPlayerBullet() { return playerBullet; }
};

