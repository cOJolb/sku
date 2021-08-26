#pragma once
#include "object.h"
struct S_playerDashInfo
{
	float playerDashSpeed;
	int DashTime;
	int DashDelay;
	int DashCount;
	int DashTerm;
	bool playerDoubleDash;
	bool DashFoward;
	bool isDash;
};
class C_player : public C_object
{
protected:
	float playerSpeed;
	
	S_playerDashInfo playerDashInfo;

	float playerJumpPower;
	bool playerDoubleJump;
	bool playerDashJump;
	int DashJumpCount;

	bool isLeft;

	SKUL_TYPE type;
private:

public:
	C_player();
	virtual~C_player();

public:
	virtual HRESULT init(vector2 _pt);
	virtual void release();
	virtual void update();
	virtual void render();
	
public:
	void playerMove();
	void playerJump();
	void playerDash();
	virtual void playerDashMove();
	void playerDash_Jump();
	void playerAtk();
	void playerSkillA();
	void playerSkillS();
	SKUL_TYPE getSkulType(){return type;}
};

