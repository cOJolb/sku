#include "framework.h"
#include "CStage.h"
#include "stageManager.h"

stageManager::stageManager() :
	curStage(nullptr), curStageIdx(-1)
{
}

stageManager::~stageManager()
{
}

HRESULT stageManager::init()
{
	CStage* tempStage0 = new CStage;
	//CStage* tempStage1 = new CStage;
	vStage.push_back(tempStage0);
	//vStage.push_back(tempStage1);
	curStageIdx = 0;
	curStage = vStage[curStageIdx];
	curStage->enter();
	return S_OK;
}

void stageManager::release()
{
	Safe_Delete_Vector(vStage);
}

void stageManager::update()
{
	curStage->update();
}

void stageManager::render()
{
	curStage->render();
}

void stageManager::changeStage(int stageNum)
{
	assert(curStageIdx != stageNum);

	curStage->exit();
	assert(vStage.size() > stageNum);

	curStageIdx = stageNum;
	curStage = vStage[curStageIdx];

	curStage->enter();
}
