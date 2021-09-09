#pragma once
#include "stage.h"
class stageScene : public C_stage
{
private:
	vector<C_stage*> vstage;
	vector<C_stage*>::iterator vistage;
	C_stage* curStage;
	int stageNumber;
	int stageType;
	bool testOnce;
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

