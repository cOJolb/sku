#pragma once
//===============================================
//commonMacroFunction(필요한 부분은 직접만들어써라)
//===============================================

//포인트
inline POINT PointMake(int x, int y)
{
	POINT pt = { x,y };
	return pt;
}

//선그리기
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//RECT만들기(좌상단 기준)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x,y,x + width,y + height };
	return rc;
}
//RECT만들기(중심점으로 부터)
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2,y - height / 2,x + width / 2,y + height / 2 };
	return rc;
}
//RECT만들기(좌상단 기준)
inline RECT RectMake(vector2 vec, int width, int height)
{
	RECT rc = { vec.x, vec.y, vec.x + width, vec.y + height };
	return rc;
}
//RECT만들기(중심점으로 부터)
inline RECT RectMakeCenter(vector2 vec, int width, int height)
{
	RECT rc = { vec.x - width / 2, vec.y - height / 2, vec.x + width / 2, vec.y + height / 2 };
	return rc;
}

//사각형 그리기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}
inline void RectangleMake(HDC hdc,RECT rect)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//원 그리기
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
inline void ElllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void BeginSolidColor(HDC hdc, HBRUSH* brush, COLORREF color)
{
	*brush = CreateSolidBrush(color);
	*brush = (HBRUSH)SelectObject(hdc,*brush);
}



inline float RectX(RECT rec)
{
	float x = ((rec.right - rec.left) / 2) + rec.left;
	return x;
}
inline float RectY(RECT rec)
{
	float y = ((rec.bottom - rec.top) / 2) + rec.top;
	return y;
}
inline float RectWidth(RECT rec)
{
	float width = rec.right - rec.left;
	return width;
}
inline float RectHeight(RECT rec)
{
	float height = rec.bottom - rec.top;
	return height;
}
inline RECT& movetoRight(RECT& rec, int speed)
{
	OffsetRect(&rec, speed, 0);

	return rec;
}
inline RECT& movetoLeft(RECT& rec, int speed)
{
	OffsetRect(&rec, -speed, 0);
	return rec;
}
inline RECT& movetoUp(RECT& rec, int speed)
{
	OffsetRect(&rec, 0, -speed);
	return rec;
}
inline RECT& movetoDown(RECT& rec, int speed)
{
	OffsetRect(&rec, 0, speed);
	return rec;
}

enum class STATE_TYPE
{
	IDLE,
	TRACE,
	ATTACK,
	DEAD,
};

enum FOWARD
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LEFTTOP,
	RIGHTTOP,
	LEFTDOWN,
	RIGHTDOWN,
	NONE
};

enum class OBSTACLE_TYPE
{
	LT_LAND,
	LTC_LAND,
	RTC_LAND,
	RT_LAND,
	L_LAND,
	LC_LAND,
	RC_LAND,
	R_LAND,
	LB_LAND,
	LBC_LAND,
	RBC_LAND,
	RB_LAND,
	SLAND
};

enum class SKUL_TYPE
{
	SKUL,
	CLOWN
};

enum class UNIT_TYPE
{
	PLAYER,
	KNIGHT
};

enum class MONSTER_TYPE
{
	BOSS,
	MINION
};

enum class ITEM_TYPE
{
	SKUL,
	PASSIVE,
	ACTIVE
};

enum class PASSIVEITEM
{
	BOOTS,
	CRISTAL
};

enum class SKULITEM
{
	SKUL,
	CROWN
};

enum class ACTIVEITEM
{
	IM,
	NOT,
	OKAY
};

const int GRAVITY = 10;


struct tagTile
{
	OBSTACLE_TYPE type;
	RECT rcTile;

	Vec2 objFrame;
	Vec2 monsterFrame;
	Vec2 pt;
};

