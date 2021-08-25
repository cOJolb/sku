#include"framework.h"
#include"imageList.h"

C_imageList::C_imageList()
{
	//=========================skul:skul=================================================================================
	//=========================skul:skul=================================================================================
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
	//=========================skul:clown=================================================================================
	//=========================skul:clown=================================================================================
	IMAGE->addFrameImage("clown", "images/skul/skul_clown.bmp", 800, 1600, 8, 16, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("clownRightIdle", "clown", 0, 3, 7, false, true);
	ANIMATION->addAnimation("clownRightMove", "clown", 3, 5, 7, false, true);
	ANIMATION->addAnimation("clownRightDash", "clown", 3, 5, 7, false,true);
	ANIMATION->addAnimation("clownLeftIdle", "clown", 3, 5, 7, false, true);
	ANIMATION->addAnimation("clownLeftMove", "clown", 3, 5, 7, false, true);
	ANIMATION->addAnimation("clownLeftDash", "clown", 3, 5, 7, false, true);
	ANIMATION->addAnimation("clownRightJump", "clown", 3, 5, 7, false, true);
	ANIMATION->addAnimation("clownRightFall", "clown", 3, 5, 7, false, true);
	ANIMATION->addAnimation("clownLeftJump", "clown", 3, 5, 7, false, true);
	ANIMATION->addAnimation("clownLeftFall", "clown", 3, 5, 7, false, true);

	//=========================monster:knight=================================================================================
	//=========================monster:knight=================================================================================
	IMAGE->addFrameImage("knightAttack", "images/monster/SwordMan/Attack.bmp", 312, 128, 4, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("knightHit", "images/monster/SwordMan/Hit.bmp", 92, 102, 2, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("knightIdle", "images/monster/SwordMan/Idle.bmp", 204, 112, 6, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("knightWalk", "images/monster/SwordMan/Walk.bmp", 416, 100, 8, 2, true, RGB(255, 0, 255));

	ANIMATION->addAnimation("knightLeftIdle", "knightIdle", 0, 5, 7, false, true);
	ANIMATION->addAnimation("knightRightIdle", "knightIdle", 6, 11, 7, false, true);
	ANIMATION->addAnimation("knightLeftWalk", "knightWalk", 0, 7, 7, false, true);
	ANIMATION->addAnimation("knightRightWalk", "knightWalk", 8, 15, 7, false, true);
	ANIMATION->addAnimation("knightLeftAttack", "knightAttack", 0, 3, 7, false, false);
	ANIMATION->addAnimation("knightRightAttack", "knightAttack", 4, 7, 7, false, false);
	ANIMATION->addAnimation("knightLeftHit", "knightHit", 0, 1, 7, false, false);
	ANIMATION->addAnimation("knightRightHit", "knightHit", 2, 3, 7, false, false);
	

	IMAGE->addFrameImage("tile", "images/tile/tile.bmp", 216, 144, 6, 4, true, RGB(255, 0, 255));
}

C_imageList::~C_imageList()
{
}

void C_imageList::release()
{
	IMAGE->deleteAll();
}
