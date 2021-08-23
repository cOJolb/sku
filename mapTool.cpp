#include "framework.h"
#include "mapTool.h"
mapTool::mapTool()
{
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	IMAGE->addFrameImage("tilemap", "images/tilemap.bmp", 640, 256, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	maptoolSetup();
	_currentTile.x = 2;
	_currentTile.x = 0;


	_terrain = RectMakeCenter(WINSIZEX / 2 + 100, WINSIZEY / 2, 100, 100);
	_object = RectMakeCenter(WINSIZEX / 2 + 250, WINSIZEY / 2, 100, 100);
	_erase = RectMakeCenter(WINSIZEX / 2 + 400, WINSIZEY / 2, 100, 100);

	_save= RectMakeCenter(WINSIZEX / 2 + 100, WINSIZEY / 2+150, 100, 100);
	_load= RectMakeCenter(WINSIZEX / 2 + 250, WINSIZEY / 2 + 150, 100, 100);
	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	if (InputManager->isStayKeyDown(VK_LBUTTON))setMap();

	if (PtInRect(&_terrain, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON))
	{
		_ctrSelect = static_cast<int>(CTRL::CTRL_TERRAINDRAW);
	}
	else if (PtInRect(&_object, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON))
	{
		_ctrSelect = static_cast<int>(CTRL::CTRL_OBJDRAW);
	}
	else if (PtInRect(&_erase, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON))
	{
		_ctrSelect = static_cast<int>(CTRL::CTRL_ERASER);
	}
	else if (PtInRect(&_save, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON))
	{
		save();
	}
	else if (PtInRect(&_load, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON))
	{
		load();
	}
}

void mapTool::render()
{
	IMAGE->render("tilemap", getMemDC(), WINSIZEX - IMAGE->findImage("tilemap")->getWidth(), 0);


	for (size_t i = 0; i < TILEX* TILEY; i++)
	{
		IMAGE->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

		if (_tiles[i].obj == OBJECT::OBJ_NONE)continue;

		IMAGE->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);

	}
	Rectangle(getMemDC(), _terrain.left, _terrain.top, _terrain.right, _terrain.bottom);
	Rectangle(getMemDC(), _object.left, _object.top, _object.right, _object.bottom);
	Rectangle(getMemDC(), _erase.left, _erase.top, _erase.right, _erase.bottom);
	Rectangle(getMemDC(), _save.left, _save.top, _save.right, _save.bottom);
	Rectangle(getMemDC(), _load.left, _load.top, _load.right, _load.bottom);
}

void mapTool::maptoolSetup()
{
	_ctrSelect = _ctrSelect = static_cast<int>(CTRL::CTRL_TERRAINDRAW);


	//¿À¸¥ÂÊ »ùÇÃ ¸Ê  ¼ÂÆÃ
	for (size_t i = 0; i < SAMPLETILEY; i++)
	{
		for (size_t j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;

			//ÁÂÇ¥°ª¼³Á¤
			SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
				(WINSIZEX - IMAGE->findImage("tilemap")->getWidth()) + j * TILESIZE,
				i * TILESIZE, (WINSIZEX - IMAGE->findImage("tilemap")->getWidth()) + j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}
	//¿ÞÂÊ ¸Ê ¼ÂÆÃ
	for (size_t i = 0; i < TILEY; i++)
	{
		for (size_t j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}
	//Ã³À½ ±ò·Á  ÀÖ´Â Å¸ÀÏ
	for (size_t i = 0; i < TILEX* TILEY; i++)
	{
		_tiles[i].terrainFrameX = 3;
		_tiles[i].terrainFrameY = 0;

		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameX = 0;

		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJECT::OBJ_NONE;
	}
}

void mapTool::setMap()
{

	//¿À¸¥ÂÊ »ùÇÃ
	for (size_t i = 0; i < SAMPLETILEX*SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTiles[i].rcTile, m_ptMouse))
		{
			_currentTile.x = _sampleTiles[i].terrainFrameX;
			_currentTile.y = _sampleTiles[i].terrainFrameY;
			break;
		}
	}
	//¿ÞÂÊ Å¸ÀÏ
	for (size_t i = 0; i < TILEX*TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, m_ptMouse))
		{
			switch ((CTRL)_ctrSelect)
			{

			case CTRL::CTRL_TERRAINDRAW:
			{
				_tiles[i].terrainFrameX = _currentTile.x;
				_tiles[i].terrainFrameY = _currentTile.y;
				_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);

			}
			break;
			case CTRL::CTRL_OBJDRAW:
			{
				_tiles[i].objFrameX = _currentTile.x;
				_tiles[i].objFrameY = _currentTile.y;
				_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
			}
			break;
			default:
				_tiles[i].obj = OBJECT::OBJ_NONE;
				break;
			}
			InvalidateRect(m_hWnd, NULL, false);
			break;
		}
	}
}

void mapTool::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("tileMap.map",
		GENERIC_WRITE, 0, NULL,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	WriteFile(file, _pos, sizeof(int) * 2, &write, NULL);
	CloseHandle(file);

}

void mapTool::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("tileMap.map",
		GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);
}

TERRAIN mapTool::terrainSelect(int frameX, int frameY)
{

	//½Ã¸àÆ®
	if (frameX == 1 && frameY == 0)
	{
		return TERRAIN::TR_CEMENT;
	}
	//»ç¸·
	else if (frameX == 2 && frameY == 0)
	{
		return TERRAIN::TR_DESERT;
	}
	//ÀÜµð
	else if (frameX == 3 && frameY == 0)
	{
		return TERRAIN::TR_GRASS;
	}
	//ÀÜµð
	else if (frameX == 4 && frameY == 0)
	{
		return TERRAIN::TR_WATER;
	}
	return TERRAIN::TR_GRASS;
}

OBJECT mapTool::objSelect(int frameX, int frameY)
{

	if (frameX == 0 && frameY == 0)
	{
		return OBJECT::OBJ_TANK1;
	}
	else if (frameX == 0 && frameY == 8)
	{
		return OBJECT::OBJ_TANK2;
	}
	else if (frameX == 0 && frameY == 1)
	{
		return OBJECT::OBJ_BLOCK1;
	}
	else if (frameX == 0 && frameY == 2)
	{
		return OBJECT::OBJ_BLOCK3;
	}
	else if (frameX == 0 && frameY == 3)
	{
		return OBJECT::OBJ_BLOCKS;
	}

	return OBJECT::OBJ_BLOCK1;

}