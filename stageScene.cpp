#include "framework.h"
#include "stageScene.h"

stageScene::stageScene()
{
	curStage = new C_stage;
	for (int i = 0; i < 5; i++)
	{
		C_stage* tempStage = new C_stage;
		vstage.push_back(tempStage);
	}
	vistage = vstage.begin();
	curStage = (*vistage);
	stageNumber = 0;
	//NextStage = new C_stage;
}

stageScene::~stageScene()
{
}

HRESULT stageScene::init()
{
	curStage->init();
	//NextStage->init();
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
	//if(curStage->isNextStage())
	if (PLAYERDATA->getPlayerData()->getNextLevel())
	{
		stageNumber++;
		vistage = vstage.begin() + stageNumber;
		curStage->curRelease();
		curStage = (*vistage);
		curStage = vstage[stageNumber];
		curStage->init();

		//NextStage->init();
		//nexttest = true;
	}
}
