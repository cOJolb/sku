#include "framework.h"
#include "stageScene.h"

stageScene::stageScene()
{
	curStage = new C_stage;
	for (int i = 0; i < 6; i++)
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
	curStage->init(stageNumber);
	//NextStage->init();
	return S_OK;
}

void stageScene::release()
{
	curStage->release();
}

void stageScene::update()
{
	if (stageNumber == 4 && !testOnce)
	{
		testOnce = true;
		SCENE->changeScene("end");
	}
	nextStage();
	curStage->update();
}

void stageScene::render()
{
	IMAGE->findImage("BackGround")->render(getCVOSDC());
	if (stageNumber == 0)
	{
		IMAGE->findImage("zxc")->renderCenter(getCVOSDC(), { 152, GameSizeY / 2 });
		IMAGE->findImage("bottom")->renderCenter(getCVOSDC(), { 200, GameSizeY / 2 });
		IMAGE->findImage("left")->renderCenter(getCVOSDC(), { 225, GameSizeY / 2 });
		IMAGE->findImage("right")->renderCenter(getCVOSDC(), { 250, GameSizeY / 2 });
	}
	curStage->render();
}

void stageScene::nextStage()
{
	//if(curStage->isNextStage())
	if (PLAYERDATA->getPlayerData()->getNextLevel() && stageNumber<4)
	{
		stageNumber++;
		if (stageNumber >= 4) { stageNumber = 4; }
		//vistage = vstage.begin() + stageNumber;
		curStage->curRelease();
		//curStage = (*vistage);
		curStage = vstage[stageNumber];
		curStage->init(stageNumber);

		//NextStage->init();
		//nexttest = true;
	}
}
