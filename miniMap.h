#pragma once
#include"gameNode.h"
class C_miniMap : public gameNode
{
private:
	RECT miniMapRect;
	vector<S_tagTile> vtile;
	vector<S_tagTile>::iterator vitile;

	RECT miniPlayer;

public:
	C_miniMap();
	~C_miniMap();

public:
	HRESULT init(S_tagTile _tile);
	void release();
	void update();
	void render();


};

