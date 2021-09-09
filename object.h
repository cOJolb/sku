#pragma once
#include"gameNode.h"
#include"collider.h"

const int GRAVITY = 10;

struct S_unitImageInfo
{
	string unitName;
	string unitFoward;
	string unitState;
};

class C_fsm;
class C_object : public gameNode
{
protected:
	animation* ani;
	image* objectImage;
	BYTE ap;

	vector2 pt;
	vector2 prevPt;
	C_collider* collider;

	HRGN Bump;
	HRGN hrgnRc;
	bool getOut;
	LPRECT lpRect;

	LPRECT testLP;
	RECT testRc;

	RECT rc;
	RECT futureRc;
	RECT futureRcL;
	RECT futureRcT;
	RECT futureRcR;
	RECT futureRcB;
	RECT futureRL;
	RECT futureRT;
	RECT futureRR;
	RECT futureRB;


	C_fsm* ai;
	vector<C_fsm*> vAi;

	S_unitImageInfo unitImageInfo;
	//string prevState;
	/*list<int> searchList;
	list<int>::iterator searchListI;*/

	int hp;
	int maxHp;
	int damage;

	float jumpPower;
	bool isJump;
	float unitDamage;
	int atkDelay;

	bool wallCollision;
	bool landCollision;
	bool floorCollision;

	int frameX;
	int startFrameX;
	int maxFrameX;
	int frameY;
	int delay;
	bool isStart;

	FRAME_TYPE frameType;
private:
	/*RECT tile;
	bool NONEtile;*/
public:
	C_object();
	virtual~C_object();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:
	C_fsm* getAi() { return ai; }
	void AI_init(C_object* _object, UNIT_TYPE _type);
	void AI_update();
	STATE_TYPE getstate();

public:
	vector2 getPt() { return pt; }
	C_collider* getCollider() { return collider; }
	bool getIsJump() { return isJump; }
	S_unitImageInfo getImageInfo() { return unitImageInfo; }
	animation* getAni() { return ani; }
	int getAtkDelay() { return atkDelay; }
	int gethp() { return hp; }
	int getmaxHp() { return maxHp; }
	int getMaxFrameX() { return IMAGE->findImage(unitImageInfo.unitName + unitImageInfo.unitState)->getMaxFrameX(); }
	int getDamage() { return damage; }

public:
	void setPt(vector2 _pt) { pt = _pt; }
	void setUnitImageInfo(string _name, string _Foward, string _state);
	void setAni(animation* _ani) { ani = _ani; }
	void sethp(int _hp) { hp = _hp; }
	void setFutureRc(RECT _rc) { futureRc = _rc; }
	void setStart(bool _isStart) { isStart = _isStart; }

	void setFrameX(int _frameX) { frameX = _frameX; }
	void setFrameRender(FRAME_TYPE _type) { frameType = _type; }
	void setFrameMaxMin(int _min, int _max);
	void setAlpha(BYTE _alpha) { ap = _alpha; }

	void setState(STATE_TYPE _type);
public:
	bool isCollision(C_collider* _left, C_collider* _right);
	bool isCollision(RECT _left, RECT _right);
	//void Jump();
	void Gravity();
	void isLand();
	void isBump();
	void isClogged();
	void isWall();
	void ptUpdate() { prevPt = pt; }
	void futureRcLTRB();
	

	
	
	

	
	
	
};

