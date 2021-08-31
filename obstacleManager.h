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

	vObstacle v_land;
	viObstacle vi_land;

	vObstacle v_wall;
	viObstacle vi_wall;

	S_tagTile tile[tileX * tileY];
public:
	obstacleManager();
	~obstacleManager();

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	void createObstacle(OBSTACLE_TYPE _type, vector2 _pt, int _number);
	vObstacle getvObstacle() { return v_obstacle; }
	viObstacle getviObstacle(int number);
	vObstacle getvLand() { return v_land; }
	viObstacle getviLand(int number);
	vObstacle getvWall() { return v_wall; }
	viObstacle getviWall(int number);

	void saveTileData(S_tagTile _tile, int number) { tile[number] = _tile; }
	S_tagTile loadTileData(int _number) { return tile[_number]; }
};

