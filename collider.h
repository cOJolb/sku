#pragma once
#include"vector2.h"
class C_collider
{
private:
	vector2 pos;
	vector2 size;
public:
	C_collider() : pos({ 0, 0 }), size({ 0, 0 })
	{ }
	C_collider(vector2 _pos, vector2 _size) : pos(_pos), size(_size)
	{ }
	const vector2& getPos() { return pos; }
	void setPos(const vector2& _pos) { pos = _pos; }

	const vector2& getSize() { return size; }
	void setSize(const vector2& _size) { size = _size; }
};