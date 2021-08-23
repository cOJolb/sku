#pragma once
#include"singleton.h"

class CMapSetting;
class TestMonsterScene;


class Window :public Singleton<Window>
{
private:
	HWND hWnd;
	static POINT ptMouse;

	image* backBuffer;
	gameNode* currentScene;

	HWND btnDraw;
	HWND btnInit;

	HWND btnSave;
	HWND btnLoad;

	HWND btnExit;
	HWND editStr;

	HWND listFile;
	HWND btnRemoveFile;

	HWND btnMonsterTile;
	HWND btnObjectTile;
	HWND btnRoomTile;

	static CTRL currentCTRL;
	POINT objFrame;
	POINT monsterFrame;
	POINT roomFrame;

	int clickIndex;
	int fileCnt;

	bool isActive;

	CMapSetting* map;
	TestMonsterScene* test;
public:
	Window();
	~Window();

	void init();
	void release();
	void update();
	void render();

	void SetScene(gameNode* scene);

	static LRESULT CALLBACK WndLogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HWND GetHwnd() { return hWnd; }

	static POINT GetMousePos() { return ptMouse; }

	static CTRL GetCTRL() { return currentCTRL; }
	void SetCTRL(CTRL ctrl) { currentCTRL = ctrl; }

	void SetIsActive(bool isActive) { this->isActive = isActive; }
	bool GetIsActive() { return isActive; }

	void SetMonsterFrame(POINT frame) { monsterFrame = frame; }
	POINT GetMonsterFrame() { return monsterFrame; }

	void SetObjFrame(POINT frame) { objFrame = frame; }
	POINT GetObjFrame() { return objFrame; }

	void SetRoomFrame(POINT frame) { roomFrame = frame; }
	POINT GetRoomFrame() { return roomFrame; }

	void SetFrameIndex(int index) { clickIndex = index; }
	int GetFrameIndex() { return clickIndex; }

	void SetMapLink(CMapSetting* _map) { map = _map; }
	void SetTestLink(TestMonsterScene* _test) { test = _test; }

	CMapSetting* getMap() { return map; }
	TestMonsterScene* getTest() { return test; }

	HWND getListHandle() { return listFile; }

	void CreateSubWindow();

	void FileListSet();
};