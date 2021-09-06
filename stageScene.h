#pragma once
#include "stage.h"
class stageScene : public C_stage
{
private:
	//map<string, C_stage*> stageMap;
	vector<C_stage*> vstage;
	vector<C_stage*>::iterator vistage;
	//C_stage* firstStage;
	C_stage* curStage;
	//C_stage* NextStage;
	int stageNumber;

	//bool nexttest;
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

