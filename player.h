#pragma once
#include "object.h"
#include "skul.h"
//struct S_playerDashInfo
//{
//	float playerDashSpeed;
//	int DashTime;
//	int DashDelay;
//	int DashCount;
//	int DashTerm;
//	bool playerDoubleDash;
//	bool DashFoward;
//	bool isDash;
//};
//struct S_skulInfo
//{
//	float playerDashSpeed;
//	int DashTime;
//	
//	int DashTerm;
//	float playerSpeed;
//	float playerJumpPower;
//};

class C_player : public C_object ,C_skul
{
protected:
	bool DashFoward;
	int DashCount;
	bool isDash;
	bool playerDoubleDash;
	bool playerDoubleJump;
	bool playerDashJump;
	int DashJumpCount;
	bool isLeft;
	int DashDelay;
	bool isAtk;
	int atkCount;


	S_skulInfo skulInfo;

	vector<C_skul*> vskul;
	vector<C_skul*>::iterator viskul;

	SKUL_TYPE cur_skul;
	SKUL_TYPE next_skul;
	
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
	void playerDash_Jump();
	void playerAtk();
	//virtual void playerDashMove();
	//void playerAtk();
	//void playerSkillA();
	//void playerSkillS();
	//SKUL_TYPE getSkulType(){return type;}
};

