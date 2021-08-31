#include "framework.h"
#include "createScene.h"

#include"mapTool.h"
#include"subWindowSetting.h"

createScene::createScene()
{
}

createScene::~createScene()
{
}

HRESULT createScene::init()
{
	SUBWIN->init();
	mapTool = new C_mapTool;
	//mapTool->init();
	SUBWIN->SetScene(new C_subWindowSetting);
	SUBWIN->SetMapLink(mapTool);
	RECT rec = RectMake(0,0, GameSizeX, GameSizeY);
	SCENE->setSCENETYPE(SCENE_TYPE::CREATE);
	return S_OK;
}

void createScene::release()
{
}

void createScene::update()
{
	SUBWIN->update();
	mapTool->update();
}

void createScene::render()
{
	SUBWIN->render();
	mapTool->render();
}
