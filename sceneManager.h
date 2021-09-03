#pragma once
#include"singleton.h"
enum class SCENE_TYPE
{
	CREATE,
	PLAY,
	ITEM
};
class gameNode;
class SceneManager : public Singleton<SceneManager>
{
private:
	typedef map<string, gameNode*> sceneList;
	typedef map<string, gameNode*>::iterator isceneList;
	SCENE_TYPE sceneType;
private:
	static gameNode* _currentScene;
	sceneList _sceneList;
public:
	SceneManager();
	~SceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

public:
	gameNode* addScene(string sceneName, gameNode* scene);
	HRESULT changeScene(string sceneName);

public:
	SCENE_TYPE getSCENETYPE() { return sceneType; }
	sceneList getSceneList() { return _sceneList; }

public:
	void setSCENETYPE(SCENE_TYPE _type) { sceneType = _type; }
	
};

