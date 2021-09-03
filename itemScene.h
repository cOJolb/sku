#pragma once
#include "gameNode.h"
#include "testScene.h"
struct S_choice
{
	vector2 pt;
	RECT rc;
	ITEM_TYPE type;
};
class itemScene : public gameNode
{
private:
	S_choice setter;
	vector<S_choice> vChoice;
	vector<S_choice>::iterator viChoice;
	int selectItem;
	int removeCount;
public:
	itemScene();
	~itemScene();

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:

};

