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
			setter.pt = { 500,500 };
			setter.rc = RectMakeCenter(setter.pt, 30, 30);
			setter.type = ITEM_TYPE::SKUL;
			break;
		case 1:
			setter.pt = { 550,500 };
			setter.rc = RectMakeCenter(setter.pt, 30, 30);
			setter.type = ITEM_TYPE::SKUL;
			break;
		case 2:
			setter.pt = { 600,600 };
			setter.rc = RectMakeCenter(setter.pt, 30, 30);
			setter.type = ITEM_TYPE::ACTIVE;
			break;
		default:
			vector2 pt;
			pt.x = 300 + (i-3) % 3 * 50;
			pt.y = 200 + (i-3) / 3 * 50;
			setter.pt = pt;
			setter.rc = RectMakeCenter(pt, 30, 30);
			setter.type = ITEM_TYPE::PASSIVE;
			break;
		}
		vChoice.push_back(setter);
	}
	selectItem = 0;
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
		SCENE->changeScene("test");
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
	
}

void itemScene::render()
{
	SCENE->getSceneList().find("test")->second->render();
	Rectangle(getMemDC(), 100, 100, 1000, 600);

	viChoice = vChoice.begin() + selectItem;
	RECT setterBox = viChoice->rc;
	Rectangle(getMemDC(), setterBox.left, setterBox.top, setterBox.right, setterBox.bottom);
	if (ITEM->getvEquipItem().size() >= 2)
	{
		for (int i = 0; i < 2; i++)
		{
			vector2 pt;
			pt.x = 300 + i % 3 * 50;
			pt.y = 200 + i / 3 * 50;
			(*ITEM->getviEquipItem(i))->render(pt);
		}
	}
	else
	{
		for (int i = 0; i < ITEM->getvEquipItem().size(); i++)
		{
			vector2 pt;
			pt.x = 300 + i % 3 * 50;
			pt.y = 200 + i / 3 * 50;
			(*ITEM->getviEquipItem(i))->render(pt);
		}
	}
	
	/*for (int i = 0; i < 12; i++)
	{
		viChoice = vChoice.begin() + i;
		RECT setterBox = viChoice->rc;
		Rectangle(getMemDC(), setterBox.left, setterBox.top, setterBox.right, setterBox.bottom);
	}*/
}
