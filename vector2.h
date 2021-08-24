#ifndef __VECTOR2_H__
#define __VECTOR2_H__
#include <Cmath>

struct vector2
{
	float x, y;

public:
	vector2& operator+(const vector2& _rhs)
	{
		x += _rhs.x;
		y += _rhs.y;
		return *this;
	}
	vector2& operator+(const int _rhs)
	{
		x += _rhs;
		y += _rhs;
		return *this;
	}
	vector2& operator+=(const vector2& _rhs)
	{
		x += _rhs.x;
		y += _rhs.y;
		return *this;
	}
	vector2& operator+=(const int _rhs)
	{
		x += _rhs;
		y += _rhs;
		return *this;
	}

	vector2& operator-(const vector2& _rhs)
	{
		x -= _rhs.x;
		y -= _rhs.y;
		return *this;
	}
	vector2& operator-(const int _rhs)
	{
		x -= _rhs;
		y -= _rhs;
		return *this;
	}
	vector2& operator-=(const vector2& _rhs)
	{
		x -= _rhs.x;
		y -= _rhs.y;
		return *this;
	}
	vector2& operator-=(const int _rhs)
	{
		x -= _rhs;
		y -= _rhs;
		return *this;
	}

	vector2& operator/(const int _rhs)
	{
		x /= _rhs;
		y /= _rhs;
		return *this;
	}
	vector2& operator*(const int _rhs)
	{
		x *= _rhs;
		y *= _rhs;
		return *this;
	}

	vector2& operator=(const vector2& _rhs)
	{
		x = _rhs.x;
		y = _rhs.y;
		return *this;
	}
	vector2& operator=(const int _rhs)
	{
		x = _rhs;
		y = _rhs;
		return *this;
	}

	// 비교
	bool operator==(const vector2& _rhs) const
	{
		return x == _rhs.x && y == _rhs.y;
	}
	bool operator!=(const vector2& _rhs) const
	{
		return x != _rhs.x || y != _rhs.y;
	}
	// <, <=, >, >=은 기준이 모호

	float Distance(const vector2& _rhs) const
	{
		float distanceX = x - _rhs.x;
		float distanceY = y - _rhs.y;
		return sqrtf(pow(distanceX, 2) + pow(distanceY, 2));
	}


	vector2()
		: x(0.f), y(0.f)
	{}
	vector2(float _x, float _y)
		: x(_x), y(_y)
	{}
	vector2(const POINT& _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}
}typedef Vec2;
#endif