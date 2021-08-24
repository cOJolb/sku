#pragma once
class C_object;
class C_obstacle;
class C_collision
{
public:
	C_collision();
	~C_collision();

	bool isCollision(RECT _left, RECT _right);
	bool tileCollision(C_obstacle* _tile , C_object* _unit);
};

