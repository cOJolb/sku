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
	bool isLeft;
	bool DashFoward;

	bool isSkulChange;
	bool atkReady;
	bool isAtk;
	bool isAtk2;
	bool isJumpAtk;
	bool skillA;
	bool skillB;

	bool isDash;
	bool playerDoubleDash;
	bool playerDoubleJump;
	bool playerDashJump;
	bool DontMove;

	int DashDelay;
	int DashCount;
	int DashJumpCount;
	int atkCount;
	int jumpAtkCount;
	int skill1Count;
	int skill2Count;
	int changeCount;

	S_skulInfo skulInfo;

	//vector<C_skul*> vskul;
	//vector<C_skul*>::iterator viskul;

	SKUL_TYPE cur_skul;
	SKUL_TYPE next_skul;

	C_skul* curSkul;
	C_skul* nextSkul;
	C_skul* tempSkul;

	bool NextLevel;
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
	void playerJumpAtk();
	void playerSkill1();
	void playerSkill2();

	void changeSkul();
	
public:
	S_skulInfo getPlayerInfo() { return skulInfo; }

	C_skul* getCurSkul() { return curSkul; }
	C_skul* getNextSkul() { return nextSkul; }
	bool getNextLevel() { return NextLevel; }
	bool getHaveTwoSkill() { return skulInfo.haveTwoSkill; }
	bool getisLeft() { return isLeft; }
	float getSkillACoolTime();
	float getSkillBCoolTime();
	float getChangeCoolTime();
public:
	void setPlayerInfo(S_skulInfo _playerInfo) { skulInfo = _playerInfo; }
	void setCurSkul(SKUL_TYPE _type);
	void setNextSkul(SKUL_TYPE _type);
	void setNextLevel(bool _istrue) { NextLevel = _istrue; }

};

