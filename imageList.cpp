#include"framework.h"
#include"imageList.h"

C_imageList::C_imageList()
{
	IMAGE->addImage("BackGround", "images/map/bg.bmp", GameSizeX, GameSizeY, true, RGB(255, 0, 255));
	IMAGE->addImage("BackGround2", "images/map/bg2.bmp", GameSizeX, GameSizeY, true, RGB(255, 0, 255));
	IMAGE->addImage("BackGround3", "images/map/bg3.bmp", GameSizeX, GameSizeY, true, RGB(255, 0, 255));
	IMAGE->addImage("BackGround4", "images/map/bg4.bmp", GameSizeX, GameSizeY, true, RGB(255, 0, 255));
	IMAGE->addImage("BackGround5", "images/map/bg5.bmp", GameSizeX, GameSizeY, true, RGB(255, 0, 255));
	//UI
	IMAGE->addImage("playerUI", "images/ui/PlayerFrame.bmp", 168*2, 66*2, true, RGB(255, 0, 255));
	IMAGE->addImage("hpBar", "images/ui/HpBar.bmp", 118*2, 10*2, true, RGB(255, 0, 255));
	IMAGE->addImage("enemyHpBar", "images/ui/enemyHpBar.bmp", 30, 8, true, RGB(255, 0, 255));
	IMAGE->addImage("a", "images/skill/a.bmp", 10, 10, true, RGB(255, 0, 255));
	IMAGE->addImage("s", "images/skill/s.bmp", 10, 10, true, RGB(255, 0, 255));
	IMAGE->addImage("coolTime", "images/coolTime.bmp", 36, 36, false, RGB(255, 0, 255));
	IMAGE->addImage("top", "images/top.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGE->addImage("bottom", "images/bottom.bmp", 27, 27, true, RGB(255, 0, 255));
	IMAGE->addImage("right", "images/right.bmp", 27, 27, true, RGB(255, 0, 255));
	IMAGE->addImage("left", "images/left.bmp", 27, 27, true, RGB(255, 0, 255));
	IMAGE->addImage("zxc", "images/zxc.bmp", 75, 25, true, RGB(255, 0, 255));
	IMAGE->addImage("spacebar", "images/spacebar.bmp", 75, 25, true, RGB(255, 0, 255));

	//mapTool
	IMAGE->addFrameImage("monsterTile", "images/monsterMapTool.bmp", 144, 36,4,1, true, RGB(255, 0, 255));
	IMAGE->addImage("miniMapTile", "images/map/miniMapTile.bmp", 10, 10, false, RGB(255, 0, 255));
	IMAGE->addImage("miniMapEnemy", "images/map/miniMapENEMY.bmp", 10, 10, false, RGB(255, 0, 255));
	IMAGE->addImage("miniMapPlayer", "images/map/miniMapPlayer.bmp", 10, 10, false, RGB(255, 0, 255));
	IMAGE->addImage("miniMapDoor", "images/map/miniMapDoor.bmp", 10, 10, false, RGB(255, 0, 255));
	IMAGE->addFrameImage("miniMap", "images/map/miniMap.bmp", 50, 10,5,1, false, RGB(255, 0, 255));
	IMAGE->addFrameImage("miniMapBack", "images/map/miniMapBack.bmp", 300, 200,1,1, false, RGB(255, 0, 255));
	
	
	// main
	IMAGE->addImage("Main", "images/Main.bmp", GameSizeX, GameSizeY, true, RGB(255, 0, 255));
	IMAGE->addImage("anyButton", "images/AnyButton2.bmp", 230, 48, true, RGB(255, 0, 255));
	//end
	IMAGE->addImage("End", "images/end.bmp", GameSizeX, GameSizeY, true, RGB(255, 0, 255));

	IMAGE->addImage("inventory", "images/item/Inventory.bmp", 1067, 600, true, RGB(255, 0, 255));
	//=========================item::goods=================================================================================
	//=========================item::goods=================================================================================
	IMAGE->addImage("gold", "images/item/goldBar.bmp", 20, 20, true, RGB(255, 0, 255));
	
	//=========================item::passive=================================================================================
	//=========================item::passive=================================================================================
	IMAGE->addImage("DimLightDarkcite", "images/item/DimLightDarkcite1.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("MedalOfCarleon", "images/item/MedalOfCarleon1.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("BasicCaerleonSword", "images/item/BasicCaerleonSword1.bmp", 30, 30, true, RGB(255, 0, 255));


	//=========================skul:skul=================================================================================
	//=========================skul:skul================================================================================
	IMAGE->addImage("skulHead", "images/skul/skulImage/LittleBoneHead.bmp", 15, 13, true, RGB(255, 0, 255));
	IMAGE->addImage("skulNow", "images/skul/skulImage/LittleBone3.bmp", 45 * 1.5, 45 * 1.5, true, RGB(255, 0, 255));
	IMAGE->addImage("skulItem", "images/skul/skulImage/LittleBone2.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("skulSecond", "images/skul/skulImage/LittleBone1.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGE->addImage("littleBoneHead", "images/skul/head.bmp", 15, 13, true, RGB(255, 0, 255));
	IMAGE->addImage("skulSkill1", "images/skill/LittleBone1.bmp", 24*1.5, 24*1.5, true, RGB(255, 0, 255));
	IMAGE->addImage("skulSkill2", "images/skill/LittleBone2.bmp", 24*1.5, 24*1.5, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("skul", "images/skul/skul_little_bone.bmp", 3780, 2900, 27, 29, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("skulRightIdle", "skul", 0, 3, 7, false, true);
	ANIMATION->addAnimation("skulRightMove", "skul", 27, 34, 7, false, true);
	int sdr[] = { 54 };
	ANIMATION->addAnimation("skulRightDash", "skul", sdr, 7, false);
	/*EFFECT->addEffect("skulRightDashEffect", "images/skul/dashRight.bmp", 2400/2, 100/2, 100/2, 100/2, 1, 1.0f, 100);
	EFFECT->addEffect("skulLeftDashEffect", "images/skul/dashLeft.bmp", 2400/2, 100/2, 100/2, 100/2, 1, 1.0f, 100);*/
	ANIMATION->addAnimation("skulLeftIdle", "skul", 297, 300, 7, false, true);
	ANIMATION->addAnimation("skulLeftMove", "skul", 324, 331, 7, false, true);
	int sdl[] = { 351 };
	ANIMATION->addAnimation("skulLeftDash", "skul", sdl, 7, false);

	ANIMATION->addAnimation("skulRightJump", "skul", 648, 651, 7, false, true);
	ANIMATION->addAnimation("skulRightFall", "skul", 649, 653, 7, false, false);
	ANIMATION->addAnimation("skulLeftJump", "skul", 659, 660, 7, false, true);
	ANIMATION->addAnimation("skulLeftFall", "skul", 658, 654, 7, false, false);

	ANIMATION->addAnimation("skulLeftFall", "skul", 658, 654, 7, false, false);
	ANIMATION->addAnimation("skulLeftFall", "skul", 658, 654, 7, false, false);

	ANIMATION->addAnimation("skulLeftAtkMotion1", "skul", 408 - 27, 405 - 27, 10, false, false);
	ANIMATION->addAnimation("skulLeftAtkMotion2", "skul", 435 - 27, 432 - 27, 10, false, false);
	ANIMATION->addAnimation("skulRightAtkMotion1", "skul", 108 - 27, 111 - 27, 10, false, false);
	ANIMATION->addAnimation("skulRightAtkMotion2", "skul", 135 - 27, 137 - 27, 10, false, false);
	ANIMATION->addAnimation("skulLeftChange", "skul", 702-27, 708 - 27, 7, false, true);
	ANIMATION->addAnimation("skulRightChange", "skul", 708 - 27, 702 - 27, 7, false, true);
	ANIMATION->addAnimation("skulLeftJumpAtk", "skul", 759 - 27, 756 - 27, 7, false, false);
	ANIMATION->addAnimation("skulRightJumpAtk", "skul", 729 - 27, 732 - 27, 7, false, false);
	ANIMATION->addAnimation("skulLeftSkill1", "skul", 297, 300, 7, false, true);
	ANIMATION->addAnimation("skulRightSkill1", "skul", 0, 3, 7,false, true);

	//=========================skul:clown=================================================================================
	//=========================skul:clown=================================================================================
	IMAGE->addImage("clownHead", "images/skul/skulImage/ClownHead.bmp", 37, 26, true, RGB(255, 0, 255));
	IMAGE->addImage("clownNow", "images/skul/skulImage/Clown3.bmp", 78*1.5, 75 * 1.5, true, RGB(255, 0, 255));
	IMAGE->addImage("clownItem", "images/skul/skulImage/Clown2.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("clownSecond", "images/skul/skulImage/Clown1.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGE->addImage("clownSkill1", "images/skill/ClownSkill1.bmp", 24 * 1.5, 24 * 1.5, true, RGB(255, 0, 255));
	IMAGE->addImage("clownSkill2", "images/skill/ClownSkill2.bmp", 24 * 1.5, 24 * 1.5, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("clown", "images/skul/skul_clown.bmp", 800, 2000, 8, 20, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("clownBullet", "images/skul/dagger.bmp", 11, 8, 1, 2, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("clownRightIdle", "clown", 0, 7, 7, false, true);
	ANIMATION->addAnimation("clownRightMove", "clown", 16, 23, 7, false, true);
	ANIMATION->addAnimation("clownRightDash", "clown", 32, 38, 10, false,true);
	ANIMATION->addAnimation("clownLeftIdle", "clown", 15, 8, 7, false, true);
	ANIMATION->addAnimation("clownLeftMove", "clown", 31, 24, 7, false, true);
	ANIMATION->addAnimation("clownLeftDash", "clown", 46, 40, 10, false, true);
	ANIMATION->addAnimation("clownRightJump", "clown", 128, 131, 7, false, true);
	ANIMATION->addAnimation("clownRightFall", "clown", 132, 135, 7, false, true);
	ANIMATION->addAnimation("clownLeftJump", "clown", 143, 140, 7, false, true);
	ANIMATION->addAnimation("clownLeftFall", "clown", 139, 136, 7, false, true);

	ANIMATION->addAnimation("clownLeftAtkMotion1", "clown", 68-8, 64 - 8, 12, false, false);
	ANIMATION->addAnimation("clownLeftAtkMotion2", "clown", 164 - 8, 160 - 8, 12, false, false);
	ANIMATION->addAnimation("clownRightAtkMotion1", "clown", 56 - 8, 60 - 8, 12, false, false);
	ANIMATION->addAnimation("clownRightAtkMotion2", "clown", 152 - 8, 156 - 8, 12, false, false);
	ANIMATION->addAnimation("clownLeftChange", "clown", 134 - 8, 128 - 8, 7, false, false);
	ANIMATION->addAnimation("clownRightChange", "clown", 120 - 8, 126 - 8, 7, false, false);
	ANIMATION->addAnimation("clownLeftJumpAtk", "clown", 134 - 8, 128 - 8, 7, false, false);
	ANIMATION->addAnimation("clownRightJumpAtk", "clown", 120 - 8, 126 - 8, 7, false, false);
	ANIMATION->addAnimation("clownRightSkill1", "clown", 88 - 8, 93 - 8, 7, false, false);
	ANIMATION->addAnimation("clownLeftSkill1", "clown", 101 - 8, 96 - 8, 7, false, false);
	//=========================skul:warrior=================================================================================
	//=========================skul:warrior=================================================================================
	IMAGE->addImage("warriorHead", "images/skul/skulImage/WarriorHead.bmp", 19, 17, true, RGB(255, 0, 255));
	IMAGE->addImage("warriorNow", "images/skul/skulImage/Warrior3.bmp", 78 * 1.5, 75 * 1.5, true, RGB(255, 0, 255));
	IMAGE->addImage("warriorItem", "images/skul/skulImage/Warrior2.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGE->addImage("warriorSecond", "images/skul/skulImage/Warrior1.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGE->addImage("warriorSkill1", "images/skill/WarriorSkill1.bmp", 24 * 1.5, 24 * 1.5, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("warrior", "images/skul/skul_warrior.bmp", 1650, 3000, 11, 20, true, RGB(255, 0, 255));
	
	ANIMATION->addAnimation("warriorRightIdle", "warrior", 0, 3, 7, false, true);
	ANIMATION->addAnimation("warriorRightMove", "warrior", 22, 29, 7, false, true);
	ANIMATION->addAnimation("warriorRightDash", "warrior", 44, 46, 7, false, true);
	ANIMATION->addAnimation("warriorLeftIdle", "warrior", 14, 11, 7, false, true);
	ANIMATION->addAnimation("warriorLeftMove", "warrior", 40, 33, 7, false, true);
	ANIMATION->addAnimation("warriorLeftDash", "warrior", 57, 55, 7, false, true);
	ANIMATION->addAnimation("warriorRightJump", "warrior", 176, 178, 7, false, true);
	ANIMATION->addAnimation("warriorRightFall", "warrior", 179, 181, 7, false, true);
	ANIMATION->addAnimation("warriorLeftJump", "warrior", 190, 192, 7, false, true);
	ANIMATION->addAnimation("warriorLeftFall", "warrior", 187, 189, 7, false, true);

	ANIMATION->addAnimation("warriorLeftAtkMotion1", "warrior", 95-11, 88 - 11, 7, false, false);
	ANIMATION->addAnimation("warriorLeftAtkMotion2", "warrior", 161 - 11, 154 - 11, 7, false, false);
	ANIMATION->addAnimation("warriorRightAtkMotion1", "warrior", 77 - 11, 85 - 11, 7, false, false);
	ANIMATION->addAnimation("warriorRightAtkMotion2", "warrior", 143 - 11, 150 - 11, 7, false, false);
	ANIMATION->addAnimation("warriorLeftChange", "warrior", 184-11 , 181 -11, 7, false, false);
	ANIMATION->addAnimation("warriorRightChange", "warrior", 165 - 11, 168 - 11, 7, false, false);
	ANIMATION->addAnimation("warriorLeftJumpAtk", "warrior", 226 - 11, 220 - 11, 7, false, false);
	ANIMATION->addAnimation("warriorRightJumpAtk", "warrior", 209 - 11, 215 - 11, 7, false, false);
	ANIMATION->addAnimation("warriorLeftSkill1", "warrior", 184 - 11, 176 - 11, 7, false, false);
	ANIMATION->addAnimation("warriorRightSkill1", "warrior", 165 - 11, 173 - 11, 7, false, false);

	//=========================monster:knight=================================================================================
	//=========================monster:knight=================================================================================
	IMAGE->addFrameImage("knightAttack", "images/monster/SwordMan/Attack2.bmp", 312, 158, 4, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("knightHit", "images/monster/SwordMan/Hit.bmp", 92, 102, 2, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("knightIdle", "images/monster/SwordMan/Idle.bmp", 204, 112, 6, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("knightWalk", "images/monster/SwordMan/Walk.bmp", 416, 100, 8, 2, true, RGB(255, 0, 255));

	ANIMATION->addAnimation("knightLeftIdle", "knightIdle", 0, 5, 7, false, true);
	ANIMATION->addAnimation("knightRightIdle", "knightIdle", 6, 11, 7, false, true);
	ANIMATION->addAnimation("knightLeftWalk", "knightWalk", 0, 7, 7, false, true);
	ANIMATION->addAnimation("knightRightWalk", "knightWalk", 8, 15, 7, false, true);
	
	//ANIMATION->start("knightLeftWalk");
	//ANIMATION->start("knightRightWalk");
	
	ANIMATION->addAnimation("knightLeftAttack", "knightAttack", 0, 3, 7, false, false);
	ANIMATION->addAnimation("knightRightAttack", "knightAttack", 4, 7, 7, false, false);
	ANIMATION->addAnimation("knightLeftHit", "knightHit", 0, 1, 7, false, false);
	ANIMATION->addAnimation("knightRightHit", "knightHit", 2, 3, 7, false, false);
	
	//=========================monster:bigent=================================================================================
   //=========================monster:bigent=================================================================================
	IMAGE->addFrameImage("BigEntAttack", "images/monster/stage1/BigEnt/BigEnt_Attack1.bmp", 980, 112, 7, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("BigEntAttack2", "images/monster/stage1/BigEnt/BigEnt_Attack2.bmp", 536, 115, 4, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("BigEntIdle", "images/monster/stage1/BigEnt/BigEnt_Idle.bmp", 575, 114, 5, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("BigEntBullet", "images/monster/stage1/BigEnt/BigEnt_bullet.bmp", 15, 15, 1, 1, true, RGB(255, 0, 255));

	//=========================monster:bigknight=================================================================================
	//=========================monster:bigknight=================================================================================
	IMAGE->addFrameImage("BigknightAttack", "images/monster/stage1/Hamer/Attack3.bmp", 864, 278, 8, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("BigknightIdle", "images/monster/stage1/Hamer/Idle.bmp", 545, 200, 5, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("BigknightAttack2", "images/monster/stage1/Hamer/Tackle.bmp", 309, 226, 3, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("BigknightWalk", "images/monster/stage1/Hamer/Walk.bmp", 896, 200, 8, 2, true, RGB(255, 0, 255));

	//================================map=================================================
	//================================map=================================================
	IMAGE->addFrameImage("tile", "images/tile/tile.bmp", 252, 144, 7, 4, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("itemDoor", "images/map/itemStage.bmp", 1200, 200, 6, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("skulDoor", "images/map/skulStage.bmp", 1200, 200, 6, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("normalDoor", "images/map/normalStage.bmp", 1200, 200, 6, 1, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("itemDoorAni", "itemDoor", 0, 4, 6, false, true);
	ANIMATION->addAnimation("skulDoorAni", "skulDoor", 0, 4, 6, false, true);
	ANIMATION->addAnimation("normalDoorAni", "normalDoor", 0, 4, 6, false, true);
	ANIMATION->start("itemDoorAni");
	ANIMATION->start("skulDoorAni");
	ANIMATION->start("normalDoorAni");
}

C_imageList::~C_imageList()
{
}

void C_imageList::release()
{
	IMAGE->deleteAll();
}
