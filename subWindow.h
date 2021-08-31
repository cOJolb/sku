#pragma once
class gameNode;
class C_mapTool;
class C_subWindow : public Singleton<C_subWindow>
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

	C_mapTool* mapTool;
	//TestMonsterScene* test;
public:
	C_subWindow();
	~C_subWindow();

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

	void SetMapLink(C_mapTool* _mapTool) { mapTool = _mapTool; }
	//void SetTestLink(TestMonsterScene* _test) { test = _test; }

	C_mapTool* getMapTool() { return mapTool; }
	//TestMonsterScene* getTest() { return test; }

	HWND getListHandle() { return listFile; }

	void CreateSubWindow();

	void FileListSet();
};