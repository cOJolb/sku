#pragma once
#include"singleton.h"
class gameNode;
class SceneManager : public Singleton<SceneManager>
{
private:
	typedef map<string, gameNode*> sceneList;
	typedef map<string, gameNode*>::iterator isceneList;

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

	gameNode* addScene(string sceneName, gameNode* scene);
	HRESULT changeScene(string sceneName);
};

