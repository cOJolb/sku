#pragma once
#include "stage.h"
class stageScene : public C_stage
{
private:
	map<string, C_stage*> stageMap;
	//C_stage* firstStage;
	C_stage* curStage;
	C_stage* NextStage;
public:
	stageScene();
	~stageScene();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

public:
	void nextStage();
};

