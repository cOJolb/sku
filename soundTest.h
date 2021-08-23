#pragma once
#include"gameNode.h"
class soundTest : public gameNode
{
public:
	soundTest();
	~soundTest();


	HRESULT init();
	void release();
	void update();


};

