#pragma once
#include"gameNode.h"

#define TILESIZE  32		//오른쪽화면 타일 사이즈
#define TILEX     20		//왼쪽화면타일 사이즈 X
#define TILEY     20		//왼쪽화면타일 사이즈 Y

#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//화면  오른쪽 이미지 타일 갯수
#define SAMPLETILEX 20
#define SAMPLETILEY 8

//맵툴에서 사용할 녀석
enum class CTRL
{
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,
	CTRL_ERASER,
	CTRL_MAP1,
	CTRL_MAP2,
	CTRL_END
};
//지형
enum class TERRAIN
{
	TR_CEMENT,TR_DESERT,TR_GRASS,TR_WATER,TR_END
};
//오브젝트(ex : 지형 위쪽에  배치, 움직이거나 부서지거나하는 변화를 줄수있는 물체)
enum class OBJECT
{
	OBJ_BLOCK1,
	OBJ_BLOCK3,
	OBJ_BLOCKS,
	OBJ_FLAG1,
	OBJ_FLAG2,
	OBJ_TANK1,
	OBJ_TANK2,
	OBJ_NONE
};
//위치 좌표
enum class POS
{
	POS_FLAG1,
	POS_FLAG2,
	POS_TANK1,
	POS_TANK2
};
//타일 구조체
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT  rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;

};
//이미지 타일 구조체
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};
//현재 타일 구조체
struct tagCurrentTile
{
	int x;
	int y;
};
class mapTool : public gameNode
{
private:

	tagCurrentTile _currentTile;
	tagTile _tiles[TILEX * TILESIZEY];
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];

	int _ctrSelect;

	RECT _terrain;
	RECT _object;
	RECT _erase;
	RECT _save;
	RECT _load;



	int _pos[2];


public:
	mapTool();
	~mapTool();

	 HRESULT init();
	 void release();
	 void update();
	 void render(/*HDC hdc*/);

	 void maptoolSetup();
	 void setMap();


	 void save();
	 void load();


	 TERRAIN terrainSelect(int frameX, int frameY);
	 OBJECT objSelect(int frameX, int frameY);
};

