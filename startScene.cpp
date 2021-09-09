#include "framework.h"
#include "startScene.h"


startScene::startScene()
{
}

startScene::~startScene()
{
}

HRESULT startScene::init()
{
    return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
    //if (InputManager->isOnceKeyDown('T')) { SCENE->changeScene("stage"); }
    if (InputManager->KeyDown())
    {
        SCENE->changeScene("stage");
    }

    
}

void startScene::render()
{
    IMAGE->findImage("Main")->render(getMemDC(), 0, 0);
    IMAGE->findImage("anyButton")->renderCenter(getMemDC(), { GameSizeX / 2, GameSizeY / 2 + 150 });

}
