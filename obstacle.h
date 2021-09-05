#pragma once
#include "object.h"
class C_obstacle : public C_object
{
private:
	int obstacleNumber;
	OBSTACLE_TYPE type;
	vector2 frame;

	bool isUnmovable;
	bool isDownJump;
	bool isLand;
	bool isDoor;
	string doorType;
public:
	C_obstacle();
	C_obstacle(vector2 _pt, OBSTACLE_TYPE _type);
	~C_obstacle();
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
public:
	void setObstacleValue();
	void setValue(bool _isUnmovable, bool _isDownJump , bool _isLand);
	bool getUnMovable() { return isUnmovable; }
	bool getDownJump() { return isDownJump; }
	bool getisLand() { return isLand; }
	bool getisDoor() { return isDoor; }
	int getObstacleNumber() { return obstacleNumber; }

	RECT getRc() { return rc; }
};

