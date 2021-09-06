#include "framework.h"
#include "itemScene.h"
#include "item.h"
itemScene::itemScene()
{
	for (int i = 0; i < 12; i++)
	{
		switch (i)
		{
		case 0:
			setter.pt = { 310,238 };
			setter.rc = RectMakeCenter(setter.pt, 30, 30);
			setter.type = ITEM_TYPE::SKUL;
			break;
		case 1:
			setter.pt = { 382,238 };
			setter.rc = RectMakeCenter(setter.pt, 30, 30);
			setter.type = ITEM_TYPE::SKUL;
			break;
		case 2:
			setter.pt = { 346,339 };
			setter.rc = RectMakeCenter(setter.pt, 30, 30);
			setter.type = ITEM_TYPE::ACTIVE;
			break;
		default:
			vector2 pt;
			pt.x = 275 + (i-3) % 3 * 71;
			pt.y = 435 + (i-3) / 3 * 54;
			setter.pt = pt;
			setter.rc = RectMakeCenter(pt, 30, 30);
			setter.type = ITEM_TYPE::PASSIVE;
			break;
		}
		vChoice.push_back(setter);
	}
	selectItem = 0;
	removeCount = 0;
}

itemScene::~itemScene()
{
}

HRESULT itemScene::init()
{
	return S_OK;
}

void itemScene::release()
{
}

void itemScene::update()
{
	if (InputManager->isOnceKeyDown(VK_ESCAPE) || InputManager->isOnceKeyDown(VK_TAB))
	{
		SCENE->changeScene("stage");
	}
	
	switch (selectItem)
	{
	case 0:
		if (InputManager->isOnceKeyDown(VK_LEFT)) selectItem++;
		if (InputManager->isOnceKeyDown(VK_UP)) selectItem = 9;
		if (InputManager->isOnceKeyDown(VK_RIGHT)) selectItem ++;
		if (InputManager->isOnceKeyDown(VK_DOWN)) selectItem = 2;
		break;
	case 1:
		if (InputManager->isOnceKeyDown(VK_LEFT)) selectItem--;
		if (InputManager->isOnceKeyDown(VK_UP)) selectItem = 10;
		if (InputManager->isOnceKeyDown(VK_RIGHT)) selectItem--;
		if (InputManager->isOnceKeyDown(VK_DOWN)) selectItem = 2;
		break;
	case 2:
		if (InputManager->isOnceKeyDown(VK_UP)) selectItem = 0;
		if (InputManager->isOnceKeyDown(VK_DOWN)) selectItem = 4;
		break;
	default:
		if (InputManager->isOnceKeyDown(VK_LEFT))
		{
			if (selectItem % 3 == 0)
			{
				selectItem += 2;
			}
			else selectItem--;
		}
		if (InputManager->isOnceKeyDown(VK_UP))
		{
			if (selectItem  <= 5)
			{
				selectItem = 2;
			}
			else selectItem-=3;
		}
		if (InputManager->isOnceKeyDown(VK_RIGHT))
		{
			if (selectItem % 3 == 2)
			{
				selectItem -= 2;
			}
			else selectItem++;
		}
		if (InputManager->isOnceKeyDown(VK_DOWN))
		{
			if (selectItem  >= 9)
			{
				selectItem = 0;
			}
			else selectItem +=3;
		}
		break;
	}
	viChoice = vChoice.begin() + selectItem;
	bool passiveItem = viChoice->type == ITEM_TYPE::PASSIVE;
	bool pushF = InputManager->isStayKeyDown('F');
	if (passiveItem && pushF)
	{
		removeCount++;
		if (removeCount == 50 && ITEM->getvEquipItem().size() > selectItem - 3)
		{
			ITEM->EquipRemove(selectItem - 3);
		}
	}
	else removeCount = 0;
}

void itemScene::render()
{
	SCENE->getSceneList().find("stage")->second->render();
	IMAGE->findImage("inventory")->renderCenter(getMemDC(), { GameSizeX / 2,GameSizeY / 2 });
	viChoice = vChoice.begin() + selectItem;
	RECT setterBox = viChoice->rc;
	Rectangle(getMemDC(), setterBox.left, setterBox.top, setterBox.right, setterBox.bottom);
	//if (ITEM->getvEquipItem().size() >= 9)
	//{
		//for (int i = 0; i < 9; i++)
		//{
		//	vector2 pt;
		//	pt.x = 300 + i % 3 * 50;
		//	pt.y = 200 + i / 3 * 50;
		//	(*ITEM->getviEquipItem(i))->render(pt);
		//}
	//}
	//else
	//{
	IMAGE->findImage(PLAYERDATA->getPlayerData()->getCurSkul()->getUnitName() + "Item")->renderCenter(getMemDC(), { 310,238 });
	if (PLAYERDATA->getPlayerData()->getNextSkul() != nullptr)
		IMAGE->findImage(PLAYERDATA->getPlayerData()->getNextSkul()->getUnitName() + "Item")->renderCenter(getMemDC(), { 382,238 });
	for (int i = 0; i < ITEM->getvEquipItem().size(); i++)
	{
		vector2 pt;
		pt.x = 275 + i % 3 * 71;
		pt.y = 435 + i / 3 * 54;
		(*ITEM->getviEquipItem(i))->render(pt);
	}
	char str[256];
	sprintf_s(str, "%d, %d", m_ptMouse.x , m_ptMouse.y);
	TextOut(getMemDC(), 0, 100, str, strlen(str));

	//}
	
	/*for (int i = 0; i < 12; i++)
	{
		viChoice = vChoice.begin() + i;
		RECT setterBox = viChoice->rc;
		Rectangle(getMemDC(), setterBox.left, setterBox.top, setterBox.right, setterBox.bottom);
	}*/
}
