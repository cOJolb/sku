#pragma once
#include "CUI.h"

class RandomMapGenerator;
class CMinimap : public CUI
{
private:
	tagMinimap map[100];
	RandomMapGenerator* rnd;
	int curRoomIdx;
public:
	CMinimap();
	~CMinimap();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setRND(RandomMapGenerator* _rnd) { rnd = _rnd; }
	tagMinimap* getMinimap() { return map; }
	void mapAttrSetting();
	void eraseMinimap();
};