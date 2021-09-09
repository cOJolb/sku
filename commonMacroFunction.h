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
inline int countUp(int& _start, int _end, int& _count , int _delay = 1)
{
	if (_start < _end)
	{
		_count++;
		if (_count % _delay == 0) { _start++; }

		if (_start >= _end)
		{
			_start = _end;
		}
		return _start;
	}
}
inline int countDown(int& _start, int _end, int& _count, int _delay = 1)
{
	if (_start > _end)
	{
		_count++;
		if (_count % _delay == 0) { _start--; }

		if (_start <= _end)
		{
			_start = _end;
		}
		return _start;
	}
}

inline int countUpLoop(int& _number, int _start, int _end,  int& _count, int _delay = 1)
{
	if (_start < _end)
	{
		_count++;
		if (_count % _delay == 0) { _number++; }
		if (_number >= _end)
		{
			_number = _start;
		}
		return _number;
	}
}
inline int countDownLoop(int& _number, int _start, int _end, int& _count , int _delay = 1)
{
	if (_start > _end)
	{
		_count++;
		if (_count % _delay == 0) { _number--; }

		if (_number <= _end)
		{
			_number = _start;
		}
		return _number;
	}
}

bool afterCountstart = false;
inline bool afterCount(bool _isStart, int _count, int _dd = 0)
{
	if (_isStart)
	{
		afterCountstart = true;
	}
	if (afterCountstart)
	{
		_dd++;
		if (_dd == _count) {
			afterCountstart = false;
			return true; 
		}
		else { return false; }
	}
}
const int tileSize = 36;
const int tileX = 30;
const int tileY = 20;
const int GameSizeX = tileSize * tileX;
const int GameSizeY = tileSize * tileY;
const int MiniMapSizeX = 150;
const int MiniMapSizeY = 100;
const int ObstacleTileX = 7;
const int ObstacleTileY = 4;
const int MonsterTileX = 4;
const int MonsterTileY = 1;

enum class ROOM
{
	ROOM_NORMAL,
	ROOM_BOSS,
	ROOM_SHOP,
	ROOM_REWARD,
	ROOM_NONE,
	ROOM_FIRST,
	ROOM_END
};

enum class CTRL
{
	CTRL_DRAW,
	CTRL_INIT,
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_EXIT,
	CTRL_EDIT,
	CTRL_LIST,
	CTRL_SETROOM,
	CTRL_REMOVE,
	CTRL_MONSTER,
	CTRL_OBJECT,
	CTRL_ROOM,
	CTRL_ITEM,
	CTRL_END
};

enum class FILE_TYPE
{
	NORMAL,
	BOSS,
	SHOP,
	REWARD,
	END
};

enum class STATE_TYPE
{
	IDLE,
	TRACE,
	ATTACK,
	DEAD,
	DAMAGE
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
	NONE,
	LT_LAND,
	LTC_LAND,
	RTC_LAND,
	RT_LAND,
	L_FLOOR,
	R_FLOOR,
	L_LAND,
	LC_LAND,
	RC_LAND,
	R_LAND,
	RCA_LAND,
	RA_LAND,
	TL_LAND,
	BL_LAND,
	TR_LAND,
	BR_LAND,
	LB_LAND,
	LBC_LAND,
	RBC_LAND,
	RB_LAND,
	LA_LAND,
	LCA_LAND,
	NORMALDOOR,
	ITEMDOOR,
	SKULDOOR,
	START
};

enum class SKUL_TYPE
{
	SKUL,
	CLOWN,
	WARRIOR
};


enum class UNIT_TYPE
{
	PLAYER,
	KNIGHT,
	BIGKNIGHT,
	BIGENT
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
	ACTIVE,
	GOODS
};

enum class PASSIVEITEM
{
	BOOTS,
	CRISTAL,
	MEDAL,
	SWORD
};

enum class SKULITEM
{
	SKUL,
	CROWN
};

enum class ACTIVEITEM
{
	NONE,
	LITTLEBONEHEAD,
	NOT,
	OKAY
};

enum class GOODSITEM
{
	GOLD
};

enum class FRAME_TYPE
{
	FIX,
	LOOP,
	RANGE,
	RANGELOOP,
	NORMAL
};

struct S_skulInfo
{
	float playerDashSpeed;
	int DashTime;
	int DashTerm;
	float playerSpeed;
	float playerJumpPower;

	bool canDoubleDash;
	bool haveTwoSkill;

	int changeDelay;
	int atkDelay;
	int jumpAtkDelay;
	int DashDelay;
	int skill1Delay;
	int skill2Delay;
	

	int changeCoolTime;
	int atkCoolTime;
	int skill1CoolTime;
	int skill2CoolTime;

	int playerDamage;

	vector2 playerSize;
};

struct S_tagTile
{
	OBSTACLE_TYPE type;
	UNIT_TYPE monstertype;

	int tileNumber;
	RECT rc;

	vector2 objFrame;
	vector2 monsterFrame;
	vector2 pt;
};

struct S_tagSampleTile
{
	RECT rc;
	vector2 frame;
};

struct S_tagRoom
{
	//S_tagTile* tile = new S_tagTile[tileX * tileY];
	S_tagTile tile[tileX * tileY];
	ROOM roomType;

	void release() { delete(tile); }
};

