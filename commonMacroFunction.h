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
inline void RectangleMake(HDC hdc, RECT rect)
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
	*brush = (HBRUSH)SelectObject(hdc, *brush);
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

enum class MONSTER_TYPE
{
	NONE,
	FLY,
	HOPPER,
	HOST,
	MULLIGAN,
	WORM,
	GURDY,
	SMALLFLY
};

// ============================================= MapInfo ===================================================
// ============================================= MapInfo ===================================================
const int TILEWIDTH = 60;
const int TILEHEIGHT = 70;

const int TILEX = 15;
const int TILEY = 9;

const int TILESIZEX = TILEX * TILEWIDTH;
const int TILESIZEY = TILEY * TILEHEIGHT;

const int OBJECTTILEX = 6;
const int OBJECTTILEY = 3;

const int MONSTERTILEX = 7;
const int MONSTERTILEY = 1;

const int ROOMTILEX = 3;
const int ROOMTILEY = 1;

const int MAPSIZEX = 1009 /*50*/;
const int MAPSIZEY = 729 /*50*/;

const int MAPSTARTX = 52;
const int MAPSTARTY = 52;

const int SUBWINSIZEX = 420;
const int SUBWINSIZEY = 520;

const int ROOMMAXSIZE = 100;

const int MINIMAPSIZEX = 300;
const int MINIMAPSIZEY = 300;

const int MINIMAPROOMX = 25;
const int MINIMAPROOMY = 25;

const int MAPCOLLISIONSTARTX = MAPSTARTX + TILEWIDTH;
const int MAPCOLLISIONSTARTY = MAPSTARTY + TILEHEIGHT;
const int MAPCOLLISIONX = TILESIZEX - TILEWIDTH * 2;
const int MAPCOLLISIONY = TILESIZEY - TILEHEIGHT * 2;

enum class TILE_ATTR
{
	UNMOVABLE,
	ONLYBULLET,
	ONLYBOMB
};

enum class ROOM_TYPE_ATTR
{
	NONEROOM,
	CURROOM,
	NONCHECK,
	VISITROOM
};

enum class ROOM_MARK_ATTR
{
	NONEMARK,
	BOSS,
	SHOP,
	REWARD,
	SECRET
};

// map object
enum class OBJECT
{
	OBJ_GOAL,
	OBJ_POOP,
	OBJ_SPIKE,
	OBJ_ROCK,
	OBJ_STEEL,
	OBJ_FIREPLACE,

	OBJ_LT_PIT,
	OBJ_MT_PIT,
	OBJ_RT_PIT,

	OBJ_L_PIT,
	OBJ_M_PIT,
	OBJ_R_PIT,

	OBJ_LB_PIT,
	OBJ_MB_PIT,
	OBJ_RB_PIT,

	OBJ_WALL,

	OBJ_TOPDOOR,
	OBJ_LEFTDOOR,
	OBJ_RIGHTDOOR,
	OBJ_BOTTOMDOOR,

	OBJ_NONE,

	OBJ_CLOSETOPDOOR,
	OBJ_CLOSELEFTDOOR,
	OBJ_CLOSERIGHTDOOR,
	OBJ_CLOSEBOTTOMDOOR
};

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

// un-develop
enum class ITEM_TYPE
{
	ITEM_BOMB,
	ITEM_KEY,
	ITEM_COIN,
	ITEM_HEART,
	ITEM_HALF_HEART,
	ITEM_THEINNEREYE,
	ITEM_MOMSLIPSTICK,
	ITEM_PENTAGRAM,
	ITEM_BLOODBAG,
	ITEM_SPEEDBALL,
	ITEM_NONE
};
enum class USE_ITEM
{
	BOMB,
	NONE
};
// sub-window button function
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

enum class CHARACTER
{
	PLAYER,
	MONSTER
};

enum class MINIMAP_ATTR
{
	ROOM,
	MARK
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

enum class DOOR_DIRECTION
{
	TOP,
	LEFT,
	RIGHT,
	BOTTOM,
	END
};

enum class FILE_TYPE
{
	NORMAL,
	BOSS,
	SHOP,
	REWARD,
	END
};

struct tagTile
{
	OBJECT obj;
	MONSTER_TYPE monster;
	RECT rcTile;

	Vec2 objFrame;
	Vec2 monsterFrame;
	Vec2 pt;
};

struct tagSampleTile
{
	RECT rcTile;
	Vec2 frame;
};

struct tagOBJAttribute
{
	int strength;
};

struct tagRoom
{
	tagTile tile[TILEX * TILEY];
	ROOM roomType;
};

struct tagMinimap
{
	RECT rc;
	Vec2 pt;
	ROOM_TYPE_ATTR roomAttr;
	ROOM_MARK_ATTR markAttr;
};

// ============================================= MapInfo ===================================================
// ============================================= MapInfo ===================================================