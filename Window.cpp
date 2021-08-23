#include "framework.h"
#include "Window.h"
#include "gameNode.h"
#include "CMapSetting.h" 

POINT Window::ptMouse = POINT{ 0,0 };
CTRL Window::currentCTRL = CTRL::CTRL_DRAW;
Window::Window()
{
	backBuffer = new image();
	backBuffer->init(SUBWINSIZEX, SUBWINSIZEY);
	fileCnt = 0;
}

Window::~Window()
{
	SAFE_DELETE(backBuffer);
}

void Window::init()
{
	CreateSubWindow();

	isActive = false;

	int startX = 10;
	int startY = 10;
	int btnWidth = 90;
	int btnHeight = 25;

	btnDraw = CreateWindow("button", "그리기",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX, startY, btnWidth, btnHeight, hWnd, HMENU(0), m_hInstance, NULL);

	btnInit = CreateWindow("button", "초기화",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX, startY + 30, btnWidth, btnHeight, hWnd, HMENU(1), m_hInstance, NULL);

	btnSave = CreateWindow("button", "저장",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX + 100, startY, btnWidth, btnHeight, hWnd, HMENU(2), m_hInstance, NULL);

	btnLoad = CreateWindow("button", "불러오기",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX + 100, startY + 30, btnWidth, btnHeight, hWnd, HMENU(3), m_hInstance, NULL);

	btnExit = CreateWindow("button", "그리기 종료",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX + 100, startY + 60, btnWidth, btnHeight, hWnd, HMENU(4), m_hInstance, NULL);

	editStr = CreateWindow("edit", NULL, 
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 
		startX, startY + 100, 190, 25, hWnd, HMENU(5), m_hInstance, NULL);
	SetDlgItemText(hWnd, (int)HMENU(5), "저장 파일 입력 / 확장자 .map");

	listFile = CreateWindow("listbox", NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
		startX + 200, startY, 180, 200, hWnd, HMENU(6), m_hInstance, NULL);
	FileListSet();

	btnRemoveFile = CreateWindow("button", "파일 삭제",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX + 200, startY + 200, btnWidth * 2, btnHeight, hWnd, HMENU(8), m_hInstance, NULL);

	btnMonsterTile = CreateWindow("button", "몬스터",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX, startY + 230, btnWidth, btnHeight, hWnd, HMENU(9), m_hInstance, NULL);

	btnObjectTile = CreateWindow("button", "오브젝트",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX + 100, startY + 230, btnWidth, btnHeight, hWnd, HMENU(10), m_hInstance, NULL);

	btnRoomTile = CreateWindow("button", "방 유형",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		startX + 100 * 2, startY + 230, btnWidth, btnHeight, hWnd, HMENU(11), m_hInstance, NULL);

	objFrame = { 0,0 };
	monsterFrame = { 0,0 };
	clickIndex = 0;
}

void Window::release()
{
}

void Window::update()
{
	if (currentScene != NULL)
	{
		currentScene->update();
	}
}

void Window::render()
{
	HDC hdc = GetDC(hWnd);
	PatBlt(backBuffer->getMemDC(), 0, 0, SUBWINSIZEX, SUBWINSIZEY, WHITENESS);

	if (currentScene != NULL)
	{
		currentScene->render(backBuffer->getMemDC());
	}
	backBuffer->render(hdc);
	ReleaseDC(hWnd, hdc);
}

void Window::SetScene(gameNode* scene)
{
	currentScene = scene;
	currentScene->init();
}

LRESULT Window::WndLogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char saveFileName[100];
	int idx = -1;
	char removeStr[64] = "선택된 항목이 없습니다.";
	char folderPath[64] = "save/";
	char gameFolderPath[64] = "save/normal/";
	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		SUBWIN->SetIsActive(true);
		ptMouse.x = LOWORD(lParam);
		ptMouse.y = HIWORD(lParam);
		break;
	case  WM_COMMAND:
		switch (LOWORD(wParam))
		{
		default:
			switch ((CTRL)LOWORD(wParam))
			{
			case CTRL::CTRL_DRAW:
				currentCTRL = (CTRL)(LOWORD(wParam));
				break;

			case CTRL::CTRL_INIT:
				SUBWIN->getMap()->tileInit();
				break;

			case CTRL::CTRL_SAVE:
				GetDlgItemText(hWnd, (int)HMENU(5), saveFileName, strlen(saveFileName));
				strcat(folderPath, saveFileName);
				if (SUBWIN->getMap()->save(folderPath))
				{
					strcat(gameFolderPath, saveFileName);
					SUBWIN->getMap()->save(gameFolderPath);
					MessageBox(hWnd, "저장 성공", "알림", MB_OK);
					SUBWIN->FileListSet();
				}
				else
					MessageBox(hWnd, "저장 실패", "알림", MB_OK);
				break;

			case CTRL::CTRL_LOAD:
				idx = SendMessage(SUBWIN->getListHandle(), LB_GETCURSEL, 0, 0);
				SendMessage(SUBWIN->getListHandle(), LB_GETTEXT, idx, (LPARAM)saveFileName);
				strcat(folderPath, saveFileName);
				if (SUBWIN->getMap()->load(folderPath))
					MessageBox(hWnd, "불러오기 성공", "알림", MB_OK);
				else
					MessageBox(hWnd, "불러오기 실패", "알림", MB_OK);
				break;

			case CTRL::CTRL_REMOVE:
				idx = SendMessage(SUBWIN->getListHandle(), LB_GETCURSEL, 0, 0);
				SendMessage(SUBWIN->getListHandle(), LB_GETTEXT, idx, (LPARAM)removeStr);
				if (idx != -1)
				{
					if (IDOK == MessageBox(SUBWIN->GetHwnd(), removeStr, 
						"아래의 항목을 삭제하겠습니까?",
						MB_ICONQUESTION | MB_OKCANCEL))
					{
						SendMessage(SUBWIN->getListHandle(), LB_DELETESTRING, idx, 0);
						strcat(folderPath, removeStr);
						strcat(gameFolderPath, removeStr);
						DeleteFile(folderPath);
						DeleteFile(gameFolderPath);
					}
				}
				break;

			case CTRL::CTRL_MONSTER:
			case CTRL::CTRL_OBJECT:
			case CTRL::CTRL_ROOM:
			case CTRL::CTRL_ITEM:
				SUBWIN->SetMonsterFrame({ 0, 0 });
				SUBWIN->SetObjFrame({ 0, 0 });
				SUBWIN->SetFrameIndex(LOWORD(wParam) - 9);
				break;

			case CTRL::CTRL_EXIT:
				SCENE->changeScene("mainMenu");
				DestroyWindow(hWnd);
				break;
			}
			break;
		}
		break;

	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Window::CreateSubWindow()
{
	//로그 윈도우 생성
	int x, y, cx, cy;
	WNDCLASS wc;
	RECT rc;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)Window::WndLogProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "그리기 툴";
	RegisterClass(&wc);
	//부모 윈도우 오른쪽에 위치 하자.
	RECT rcWin;
	GetWindowRect(m_hWnd, &rcWin);

	cx = SUBWINSIZEX;
	cy = SUBWINSIZEY;
	x = rcWin.right;
	y = rcWin.top;

	rc.left = 0;
	rc.top = 0;
	rc.right = cx;
	rc.bottom = cy;

	HWND hParenthWnd = NULL;
	HINSTANCE hInst = NULL;

	hParenthWnd = m_hWnd;
	hInst = GetModuleHandle(NULL);

	hWnd = CreateWindow("그리기 툴", "그리기 툴",
		WS_POPUP | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		x, y, cx, cy, hParenthWnd, NULL, hInst, NULL);

	AdjustWindowRect(&rc, WINSTYLE, FALSE);

	SetWindowPos(hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER);

	ShowWindow(hWnd, SW_SHOW);
}

void Window::FileListSet()
{
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile("save/*.map", &fd);

	for(int i = 0; i < fileCnt; i++)
		SendMessage(listFile, LB_DELETESTRING, 0, 0);
	fileCnt = 0;

	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			fileCnt++;
			SendMessage(listFile, LB_ADDSTRING, 0, (LPARAM)fd.cFileName);
		} while (FindNextFile(hFind, &fd));
	}
	FindClose(hFind);
}