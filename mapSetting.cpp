#include "framework.h"
#include "mapSetting.h"

C_mapSetting::C_mapSetting()
{
	/*for (int i = 0; i < tileX*tileY; i++)
	{
		tile[i].pt.x = (i % tileX) * tileSize;
		tile[i].pt.y = (i / tileX) * tileSize;
		tile[i].type = OBSTACLE_TYPE::NONE;
		tile[i].tileNumber = i;
	}*/
	for (int i = 0; i < (UINT)FILE_TYPE::END; i++) maxRoomNum[i] = 0;
	loadFolder();
	randomMap = RND->getFromIntTo(0, maxRoomNum[(UINT)FILE_TYPE::NORMAL] -1);
	viroom = vroom.begin() + 0;
	//viroom = vroom.begin() + randomMap;
	for (int i = 0; i < tileX * tileY; i++)
	{
		tile[i] = viroom->tile[i];
		OBSTACLE->saveTileData(tile[i], i);
	}
}

C_mapSetting::~C_mapSetting()
{
}

HRESULT C_mapSetting::init()
{
	for (int i = 0; i < 30 * 20; i++)
	{
		if (tile[i].type != OBSTACLE_TYPE::NONE) OBSTACLE->createObstacle(tile[i].type, tile[i].pt, tile[i].tileNumber);
	}
	return S_OK;
}

void C_mapSetting::release()
{
}

void C_mapSetting::update()
{
}

void C_mapSetting::render()
{
}

void C_mapSetting::load(const char* _fileName)
{
	HANDLE file;
	DWORD read;
	//S_tagRoom load[1];
	file = CreateFile(_fileName,
		GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, roomload, sizeof(S_tagRoom), &read, NULL);
	
	room = roomload[0];
	vroom.push_back(room);

	CloseHandle(file);
}

void C_mapSetting::loadFolder()
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile("save/normal/*.map", &fd);

	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			char folderPath[64] = "save/normal/";
			strcat(folderPath, fd.cFileName);
			load(folderPath);
			maxRoomNum[(UINT)FILE_TYPE::NORMAL]++;
		} while (FindNextFile(hFind, &fd));
	}
}

void C_mapSetting::tileSet(int _number, OBSTACLE_TYPE _type)
{
	tile[_number].type = _type;
}
