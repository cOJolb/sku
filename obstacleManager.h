#pragma once
#include "singleton.h"
class C_obstacle;
typedef vector<C_obstacle*> vObstacle;
typedef vector<C_obstacle*>::iterator viObstacle;

class obstacleManager : public Singleton<obstacleManager>
{
private:
	vObstacle v_obstacle;
	viObstacle vi_obstacle;


public:
	obstacleManager();
	~obstacleManager();

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	void createObstacle(OBSTACLE_TYPE _type, vector2 _pt);
	vObstacle getvObstacle() { return v_obstacle; }
	viObstacle getviObstacle(int number);


};

