#pragma once
#include "object.h"
class C_obstacle : public C_object
{
private:
	OBSTACLE_TYPE type;
	vector2 frame;

	int tileSize;
	bool isUnmovable;
	bool isDownJump;
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
	void setValue(bool _isUnmovable, bool _isDownJump);
	bool getMovable() { return isUnmovable; }
	bool getDownJump() { return isDownJump; }

};

