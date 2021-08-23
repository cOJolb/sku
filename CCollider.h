#pragma once
#include"gameNode.h"
class CCollider
{
private:
	vector2 pos;
	vector2 size;
public:
	CCollider() : pos({ 0, 0 }), size({ 0, 0 })
	{ }
	CCollider(Vec2 _pos, Vec2 _size) : pos(_pos), size(_size)
	{ }

	const vector2& getPos() { return pos; }
	void setPos(const vector2& _pos) { pos = _pos; }

	const vector2& getSize() { return size; }
	void setSize(const vector2& _size) { size = _size; }
};