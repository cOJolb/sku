#include "framework.h"
#include "stageScene.h"

stageScene::stageScene()
{
	curStage = new C_stage;
}

stageScene::~stageScene()
{
}

HRESULT stageScene::init()
{
	curStage->init();
	return S_OK;
}

void stageScene::release()
{
	curStage->release();
}

void stageScene::update()
{
	nextStage();
	curStage->update();
}

void stageScene::render()
{
	curStage->render();
}

void stageScene::nextStage()
{
	if (curStage->isNextStage())
	{
		NextStage = new C_stage;
		curStage->release();
		curStage = NextStage;
		curStage->init();
		//SAFE_DELETE(NextStage);
	}
}
