#include "framework.h"
#include "endScene.h"

endScene::endScene()
{
}

endScene::~endScene()
{
}

HRESULT endScene::init()
{
    return S_OK;
}

void endScene::release()
{
}

void endScene::update()
{
    if (InputManager->isOnceKeyDown('N'))
    {
        SCENE->changeScene("stage");
    }
}

void endScene::render()
{
    IMAGE->findImage("End")->render(getMemDC(), 0, 0);

}
