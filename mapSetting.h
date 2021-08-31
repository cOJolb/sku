#pragma once
class C_mapSetting
{
private:
	S_tagTile tile[30 * 20];
	S_tagRoom room;
	S_tagRoom roomload[1];
	vector<S_tagRoom> vroom;
	vector<S_tagRoom>::iterator viroom;
	int maxRoomNum[(UINT)FILE_TYPE::END];
	int randomMap;
public:
	C_mapSetting();
	~C_mapSetting();

public:
	HRESULT init();
	void release();
	void update();
	void render();

public:
	void load(const char* _fileName);
	void loadFolder();
public:
	void tileSet(int _number, OBSTACLE_TYPE _type);
	S_tagTile getTile(int number) { return tile[number]; }
	void loadTile(S_tagTile _tile, int number) { tile[number] = _tile; }
};


