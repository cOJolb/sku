#pragma once
#include"singleton.h"

class CStage;
class stageManager : public Singleton<stageManager>
{
private:
	vector<CStage*> vStage;
	vector<CStage*>::iterator viStage;
	CStage* curStage;
	int curStageIdx;
public:
	stageManager();
	~stageManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void changeStage(int stageNum);

	vector<CStage*> getvStage() { return vStage; }
	CStage* getCurStage() { return curStage; }
	int getCurStageIdx() { return curStageIdx; }
};