#include "framework.h"
#include "CMap.h"
#include "mapManager.h"

mapManager::mapManager()
{
}

mapManager::~mapManager()
{
	Safe_Delete_Vector(vNormalRoom);
	Safe_Delete_Vector(vBossRoom);
	Safe_Delete_Vector(vShopRoom);
	Safe_Delete_Vector(vRewardRoom);
}

HRESULT mapManager::init()
{
	for (int i = 0; i < (UINT)FILE_TYPE::END; i++)
		maxRoomNum[i] = 0;


	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile("save/normal/*.map", &fd);

	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			char folderPath[64] = "save/normal/";
			strcat(folderPath, fd.cFileName);
			CMap* tempRoom = new CMap(folderPath);
			vNormalRoom.push_back(tempRoom);
			maxRoomNum[(UINT)FILE_TYPE::NORMAL]++;
		} while (FindNextFile(hFind, &fd));
	}

	hFind = FindFirstFile("save/boss/*.map", &fd);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			char folderPath[64] = "save/boss/";
			strcat(folderPath, fd.cFileName);
			CMap* tempRoom = new CMap(folderPath);
			vBossRoom.push_back(tempRoom);
			maxRoomNum[(UINT)FILE_TYPE::BOSS]++;
		} while (FindNextFile(hFind, &fd));
	}

	hFind = FindFirstFile("save/shop/*.map", &fd);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			char folderPath[64] = "save/shop/";
			strcat(folderPath, fd.cFileName);
			CMap* tempRoom = new CMap(folderPath);
			vShopRoom.push_back(tempRoom);
			maxRoomNum[(UINT)FILE_TYPE::SHOP]++;
		} while (FindNextFile(hFind, &fd));
	}

	hFind = FindFirstFile("save/reward/*.map", &fd);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			char folderPath[64] = "save/reward/";
			strcat(folderPath, fd.cFileName);
			CMap* tempRoom = new CMap(folderPath);
			vShopRoom.push_back(tempRoom);
			maxRoomNum[(UINT)FILE_TYPE::REWARD]++;
		} while (FindNextFile(hFind, &fd));
	}

	FindClose(hFind);
	return S_OK;
}

void mapManager::release()
{
	Safe_Delete_Vector(vNormalRoom);
	Safe_Delete_Vector(vBossRoom);
	Safe_Delete_Vector(vShopRoom);
	Safe_Delete_Vector(vRewardRoom);
}

void mapManager::render()
{
}