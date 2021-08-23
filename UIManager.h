#pragma once
#include"singleton.h"
class CUI;
class CPlayerUI;
class CMinimap;
class CBossUI;
//typedef vector <CUI*> vUI;
//typedef vector <CUI*>::iterator viUI;
class CPlayer;
class RandomMapGenerator;
class CGurdy;
class UIManager : public Singleton<UIManager>
{
private:
	/*vUI UI;
	viUI iUI;*/
	CPlayerUI* playerUI;
	CMinimap* minimap;
	CBossUI* bossUI;

	CPlayer* player;
	RandomMapGenerator* randomMap;


	bool isRespawnBoss;
public:
	UIManager();
	~UIManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setPlayer(CPlayer* _player) { player = _player; }
	void setrandomMap(RandomMapGenerator* _randomMap) { randomMap = _randomMap; }
	void setRespawn(bool _isrespawn) { isRespawnBoss = _isrespawn; }
	void setboss(CGurdy* _boss);
	CMinimap* getMinimap() { return minimap; }
};

