#include"framework.h"
#include"imageList.h"

C_imageList::C_imageList()
{
	IMAGE->addFrameImage("skul", "images/skul/skul_little_bone.bmp", 3780, 2500, 27, 25, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("skulRightIdle", "skul", 0, 3, 7, false, true);
	ANIMATION->addAnimation("skulRightMove", "skul", 27, 34, 7, false, true);
	int sdr[] = { 54 };
	ANIMATION->addAnimation("skulRightDash", "skul", sdr, 7, false);
	
	ANIMATION->addAnimation("skulLeftIdle", "skul", 297, 300, 7, false, true);
	ANIMATION->addAnimation("skulLeftMove", "skul", 324, 331, 7, false, true);
	int sdl[] = { 351 };
	ANIMATION->addAnimation("skulLeftDash", "skul", sdl, 7, false);

	ANIMATION->addAnimation("skulRightJump", "skul", 648, 651, 7, false, true);
	ANIMATION->addAnimation("skulRightFall", "skul", 649, 653, 7, false, false);
	ANIMATION->addAnimation("skulLeftJump", "skul", 659, 660, 7, false, true);
	ANIMATION->addAnimation("skulLeftFall", "skul", 658, 654, 7, false, false);

	IMAGE->addFrameImage("tile", "images/tile/tile.bmp", 216, 144, 6, 4, true, RGB(255, 0, 255));
}

C_imageList::~C_imageList()
{
}

void C_imageList::release()
{
	IMAGE->deleteAll();
}
