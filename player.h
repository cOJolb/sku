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

class C_player : public C_object 
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

	//vector<C_skul*> vskul;
	//vector<C_skul*>::iterator viskul;

	SKUL_TYPE cur_skul;
	SKUL_TYPE next_skul;

	C_skul* curSkul;
	C_skul* nextSkul;
	C_skul* tempSkul;
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
	void changeSkul();
	
public:
	S_skulInfo getPlayerInfo() { return skulInfo; }
	//vector<C_skul*> getvSkul() { return vskul; }
	//vector<C_skul*>::iterator getviSkul(bool _CurentSkul);
	C_skul* getCurSkul() { return curSkul; }
	C_skul* getNextSkul() { return nextSkul; }
public:
	void setPlayerInfo(S_skulInfo _playerInfo) { skulInfo = _playerInfo; }
	void setCurSkul(SKUL_TYPE _type);
	void setNextSkul(SKUL_TYPE _type);
	//virtual void playerDashMove();
	//void playerAtk();
	//void playerSkillA();
	//void playerSkillS();
	//SKUL_TYPE getSkulType(){return type;}
};

