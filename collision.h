#pragma once
#include"singleton.h"
class C_object;
class C_obstacle;
class C_collider;
class C_player;
class C_collision :public Singleton<C_collision>
{
public:
	C_collision();
	~C_collision();

	bool isCollision(RECT _left, RECT _right);
	bool isCollision(C_collider* _left, C_collider* _right);
	bool tileCollision(C_obstacle* _tile , C_object* _unit);
	void stageCollision(C_player* _player );
};

