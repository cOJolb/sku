#include"framework.h"
#include"imageList.h"

C_imageList::C_imageList()
{
	IMAGE->addFrameImage("skul", "images/skul/skul_little_bone.bmp", 3780, 2400, 27, 24, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("skulRightMove", "skul", 27, 34, 10, false, true);
	IMAGE->addFrameImage("tile", "images/tile/tile.bmp", 216, 144, 6, 4, true, RGB(255, 0, 255));
}

C_imageList::~C_imageList()
{
}

void C_imageList::release()
{
	IMAGE->deleteAll();
}
