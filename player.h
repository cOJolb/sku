#pragma once
#include "object.h"
class C_player : public C_object
{
protected:
	float playerSpeed;
	float playerDashSpeed;
	int DashTime;
	int DashDelay;
	int DashCount;
	bool playerDoubleDash;
	bool DashFoward;
	bool isDash;

	bool playerDoubleJump;
	
	bool isLeft;

	string unitName;
	string unitFoward;
	string unitState;

	SKUL_TYPE type;
private:

public:
	C_player();
	virtual~C_player();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
public:
	void playerMove();
	void playerJump();
	void playerDash();
	SKUL_TYPE getSkulType(){return type;}
};

