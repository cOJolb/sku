#pragma once
class C_mapSetting
{
private:
	S_tagTile tile[30 * 20];
public:
	C_mapSetting();
	~C_mapSetting();

public:
	void init();
	void release();
	void update();
	void render();

public:
	void tileSet(int _number, OBSTACLE_TYPE _type);
	S_tagTile getTile(int number) { return tile[number]; }
};

