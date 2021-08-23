#include "framework.h"
#include"AniAddList.h"

AniAddList::AniAddList()
{
	//sound..
	SOUND->addSound("flysound", "sound/fly.wav", false, true);
	SOUND->addSound("getitemsound", "sound/getitem.wav", false, false);
	SOUND->addSound("gurdyfiresound", "sound/gurdyfire.wav", false, false);
	SOUND->addSound("gurdyflysound", "sound/gurdyfly.wav", false, false);
	SOUND->addSound("gurdylittleflysound", "sound/gurdylittlefly.wav", false, false);
	SOUND->addSound("hoppersound", "sound/hopperjump.wav", false, false);
	SOUND->addSound("mulligansound", "sound/mulligan.wav", false, false);
	SOUND->addSound("tearfiresound", "sound/tearfire.wav", false, false);
	SOUND->addSound("getitem", "sound/getitem.wav", false, false);
	SOUND->addSound("getbasicitem", "sound/itempickup.wav", false, false);
	SOUND->addSound("mainmenubgm", "sound/title screen.ogg", true, true);
	SOUND->addSound("selectobj", "sound/setobject.wav", false, false);
	SOUND->addSound("selectmenu", "sound/selectmenu.wav", false, false);



	SOUND->addSound("poopsound", "sound/poop.wav", false, false);
	SOUND->addSound("bombsound", "sound/bomb.wav", false, false);
	SOUND->addSound("rockbrokensound", "sound/rockbroke.wav", false, false);
	SOUND->addSound("playerdiebgm", "sound/youdied.ogg", true, true);
	SOUND->addSound("playerdiesound", "sound/isaacDies.wav", false, false);
	SOUND->addSound("playerhurt", "sound/hurtgrunt.wav", false, false);
	SOUND->addSound("bgm", "sound/background.ogg", true, true);
	SOUND->addSound("bossfight", "sound/bossfight.ogg", true, true);
	SOUND->addSound("playerhurt2", "sound/hurt1.wav", false, false);
	SOUND->addSound("miniondeathssound", "sound/miniondeaths.wav", false, false);
	SOUND->addSound("tearblocksound", "sound/tearblock.wav", false, false);
	SOUND->addSound("wormsound", "sound/worm.wav", false, false);
	SOUND->addSound("bossdiesound", "sound/bossdie.wav", false, true);
	//=================== map ====================================================================================
	//=================== map ====================================================================================
	IMAGE->addImage("basement_first", "images/map/basement_first.bmp", MAPSIZEX, MAPSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("basement_normal", "images/map/basement_normal.bmp", MAPSIZEX, MAPSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("basement_boss", "images/map/basement_boss.bmp", MAPSIZEX, MAPSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("shop", "images/map/shop.bmp", MAPSIZEX, MAPSIZEY, true, RGB(255, 0, 255));

	IMAGE->addFrameImage("objectTile", "images/map/objectTile.bmp", TILEWIDTH * 6, TILEHEIGHT * 3, 6, 3, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("monsterTile", "images/map/monsterTile.bmp", TILEWIDTH * 7, TILEHEIGHT, 7, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("roomTile", "images/map/roomTile.bmp", TILEWIDTH * 3, TILEHEIGHT, 3, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("fireTilePlace", "images/map/fireplace.bmp", 64*1.5, 32*1.5, 2, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("fireTileEffect", "images/map/fire.bmp", 240*1.5, 50*1.5, 5, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("fireTileEffect2", "images/map/fire.bmp", 240*1.2, 50*1.2, 5, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("fireTileEffect3", "images/map/fire.bmp", 240*0.9, 50*0.9, 5, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("fireTileEffect4", "images/map/fire.bmp", 240*0.6, 50*0.6, 5, 1, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("fireEffect", "fireTileEffect", 0, 4, 10, false, true);
	ANIMATION->addAnimation("fireEffect2", "fireTileEffect2", 0, 4, 10, false, true);
	ANIMATION->addAnimation("fireEffect3", "fireTileEffect3", 0, 4, 10, false, true);
	ANIMATION->addAnimation("fireEffect4", "fireTileEffect4", 0, 4, 10, false, true);
	ANIMATION->start("fireEffect");
	ANIMATION->start("fireEffect2");
	ANIMATION->start("fireEffect3");
	ANIMATION->start("fireEffect4");
	IMAGE->addFrameImage("minimapRoom", "images/map/minimap_room.bmp", MINIMAPROOMX * 3, MINIMAPROOMY, 3, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("minimapMark", "images/map/minimap_special.bmp", MINIMAPROOMX * 5, MINIMAPROOMY, 5, 1, true, RGB(255, 0, 255));

	IMAGE->addFrameImage("normalDoor", "images/map/door_01_normaldoor.bmp", TILEWIDTH * 4 + 420, TILEHEIGHT * 2 + 160, 4, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("poop", "images/map/poop.bmp", 160 * 2, 32 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGE->addImage("goal", "images/map/goal.bmp", TILEWIDTH, TILEHEIGHT, true, RGB(255, 0, 255));
	//====================================item=========================================================================
	//====================================item=========================================================================
	IMAGE->addImage("itemshadow", "images/shadow.bmp", 30, 10, true, RGB(255, 0, 255));

	IMAGE->addFrameImage("heartitem", "images/item/heart.bmp", 90, 30, 3, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("bomb", "images/item/bomb.bmp", 30 * 1.5, 30 * 1.5, 1, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("key", "images/item/key.bmp", 30 * 1.5, 30 * 1.5, 1, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("passiveitem", "images/item/passiveitem.bmp", 150*2, 30*2, 5, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("coin", "images/item/coin.bmp", 180, 30, 6, 1, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("coinani", "coin", 0, 5, 10, false, true);
	//================================================effect ==============================================================
	//================================================effect ==============================================================
	EFFECT->addEffect("explosion", "images/effect/explosion.bmp", 384 * 1.5, 384 * 1.5, 96 * 1.5, 96 * 1.5, 1, 0.45f, 100);
	EFFECT->addEffect("playerbulleteffect", "images/effect/tears_effect.bmp", 256 * 1.5, 256 * 1.5, 64 * 1.5, 64 * 1.5, 1, 0.4f, 100);
	EFFECT->addEffect("enemybulleteffect", "images/effect/enemy_tears_effect.bmp", 256 * 1.5, 256 * 1.5, 64 * 1.5, 64 * 1.5, 1, 0.4f, 100);
	EFFECT->addEffect("poofeffect", "images/effect/poof.bmp", 128 * 1.5, 128 * 1.5, 32 * 1.5, 32 * 1.5, 1, 0.4f, 100);
	EFFECT->addEffect("enemydie", "images/effect/enemy_destroy_effect.bmp", 256 * 1.5, 256 * 1.5, 64 * 1.5, 64 * 1.5, 1, 0.4f, 100);
	EFFECT->addEffect("gurdydie", "images/effect/gurdyDieLong.bmp", 1350 * 2, 150 * 2, 150 * 2, 150 * 2, 1, 0.4f, 100);
	EFFECT->addEffect("bossdie", "images/effect/bossdie.bmp", 1000 * 2, 200 * 2, 200 * 2, 200 * 2, 1, 0.3f, 100);
	EFFECT->addEffect("bossdiebase", "images/effect/bossdiebase.bmp", 2400 * 2, 200 * 2, 200 * 2, 200 * 2, 1, 0.3f, 100);

	IMAGE->addFrameImage("smallblood", "images/effect/smallblood.bmp", 180, 30, 6, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("blood", "images/effect/blood.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("bigblood", "images/effect/bigblood.bmp", 600, 100, 6, 1, true, RGB(255, 0, 255));
	//=================================UI============================================================================
	//=================================UI============================================================================
	IMAGE->addFrameImage("hpUI", "images/UI/HpUI.bmp", 48 * 2, 16 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("basicitemUI", "images/UI/haveitemUI.bmp", 60 * 2, 20 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("number", "images/UI/number.bmp", 200, 20, 10, 1, true, RGB(255, 0, 255));
	IMAGE->addImage("bossFront", "images/UI/bosshealthbar_front.bmp", 110 * 2, 8 * 2, true, RGB(255, 0, 255));
	IMAGE->addImage("bossBack", "images/UI/bosshealthbar_back.bmp", 134 * 2, 21 * 2, true, RGB(255, 0, 255));
	//=================== bullet ====================================================================================
	//=================== bullet ====================================================================================
	IMAGE->addFrameImage("bullet", "images/bullets.bmp", 256, 128, 9, 4, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("enemybullet", "bullet", 0, 13, 10, false, false);

	IMAGE->addImage("FlyBullet", "images/enemybullet.bmp", 15 * 13, 15, true, RGB(255, 0, 255));
	IMAGE->addImage("HostBullet", "images/enemybullet.bmp", 15 * 13, 15, true, RGB(255, 0, 255));
	IMAGE->addImage("GurdyBullet", "images/enemybullet.bmp", 15 * 13, 15, true, RGB(255, 0, 255));
	IMAGE->addImage("FlyBulletShadow", "images/shadow.bmp", 15, 5, true, RGB(255, 0, 255));
	IMAGE->addImage("HostBulletShadow", "images/shadow.bmp", 15, 5, true, RGB(255, 0, 255));
	IMAGE->addImage("GurdyBulletShadow", "images/shadow.bmp", 15, 5, true, RGB(255, 0, 255));
	//=================== player ====================================================================================
	//=================== player ====================================================================================
	IMAGE->addImage("shadow", "images/shadow.bmp", 150, 50, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("isaacBody", "images/player/player_body.bmp", 216 * 2, 86 * 2, 6, 3, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("mulliganbody", "images/enemy/mulliganbody.bmp", 300 * 1.5, 90 * 1.5, 10, 3, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("playerbody", "images/enemy/mulliganbody.bmp", 300 * 2, 90 * 2, 10, 3, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("isaac", "images/player/player_head.bmp", 256 * 2, 32 * 2, 8, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("isaacEvent", "images/player/player_event.bmp", 200 * 2, 150 * 2, 4, 3, true, RGB(255, 0, 255));

	ANIMATION->addAnimation("down_head", "isaac", 0, 1, 10, false, false);
	ANIMATION->addAnimation("right_head", "isaac", 2, 3, 10, false, false);
	ANIMATION->addAnimation("up_head", "isaac", 4, 5, 10, false, false);
	ANIMATION->addAnimation("left_head", "isaac", 6, 7, 10, false, false);
	int playeridle[] = { 0 };
	ANIMATION->addAnimation("playeridlehead", "isaac", playeridle, 1, 10, false);
	ANIMATION->addAnimation("playerrightbody", "playerbody", 10, 19, 10, false, true);
	ANIMATION->addAnimation("playerleftbody", "playerbody", 20, 29, 10, false, true);
	ANIMATION->addAnimation("playerupbody", "playerbody", 0, 9, 10, false, true);
	ANIMATION->addAnimation("playerdownbody", "playerbody", 0, 9, 10, false, true);
	int mulliganidle[] = { 0 };
	ANIMATION->addAnimation("playeridlebody", "playerbody", mulliganidle, 1, 10, false);
	IMAGE->addImage("shadow", "images/shadow.bmp", 10, 10, true, RGB(255, 0, 255));

	int playerDie[] = { 3 };
	ANIMATION->addAnimation("playerisDie", "isaacEvent", playerDie, 1, 10, false);
	int playerDamage[] = { 6 };
	ANIMATION->addAnimation("playerisDamage", "isaacEvent", playerDamage, 1, 10, false);
	ANIMATION->addAnimation("playerGetItem", "isaacEvent", 4, 5, 10, false);
	ANIMATION->addAnimation("playerThumbsUp", "isaacEvent", 1, 2, 10, false);

	//==================================mulligan=================================================================
	//==================================mulligan=================================================================
	IMAGE->addFrameImage("mulliganhead", "images/enemy/mulliganhead.bmp", 240 * 1.5, 70 * 1.5, 6, 2, true, RGB(255, 0, 255));

	ANIMATION->addAnimation("righthead", "mulliganhead", 0, 5, 10, false, true);
	ANIMATION->addAnimation("rightbody", "mulliganbody", 10, 19, 10, false, true);

	ANIMATION->addAnimation("lefthead", "mulliganhead", 6, 11, 10, false, true);
	ANIMATION->addAnimation("leftbody", "mulliganbody", 20, 29, 10, false, true);

	ANIMATION->addAnimation("upbody", "mulliganbody", 0, 9, 10, false, true);
	ANIMATION->addAnimation("downbody", "mulliganbody", 0, 9, 10, false, true);


	ANIMATION->addAnimation("mulliganidle", "mulliganbody", mulliganidle, 1, 10, false);

	//================================================warm========================================
	//================================================warm========================================
	IMAGE->addFrameImage("worm", "images/enemy/worm.bmp", 260 / 1.3, 320 / 1.3, 4, 5, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("rightworm", "worm", 0, 3, 10, false, true);
	ANIMATION->addAnimation("upworm", "worm", 4, 7, 10, false, true);
	ANIMATION->addAnimation("downworm", "worm", 8, 11, 10, false, true);
	ANIMATION->addAnimation("leftworm", "worm", 16, 19, 10, false, true);

	int down[] = { 12 };
	ANIMATION->addAnimation("downwormAtk", "worm", down, 1, 10, true);
	int right[] = { 13 };
	ANIMATION->addAnimation("rightwormAtk", "worm", right, 1, 10, true);
	int left[] = { 14 };
	ANIMATION->addAnimation("leftwormAtk", "worm", left, 1, 10, true);
	int up[] = { 15 };
	ANIMATION->addAnimation("upwormAtk", "worm", up, 1, 10, true);

	//==========================================================host============================================
	//==========================================================host============================================
	IMAGE->addFrameImage("host", "images/enemy/host.bmp", 105 * 1.5, 44 * 1.5, 3, 1, true, RGB(255, 0, 255));
	int idle[] = { 0 };
	ANIMATION->addAnimation("hostidle", "host", idle, 1, 10, false);
	int trace[] = { 1 };
	ANIMATION->addAnimation("hosttrace", "host", trace, 1, 10, false);
	int atk[] = { 2 };
	ANIMATION->addAnimation("hostatk", "host", atk, 1, 10, false);

	//==============================================hopper===========================================
	//==============================================hopper===========================================
	IMAGE->addFrameImage("hopper", "images/enemy/hopper.bmp", 180 * 1.5, 30 * 1.5, 6, 1, true, RGB(255, 0, 255));
	int hopperidle[] = { 0 };
	ANIMATION->addAnimation("idlehopper", "hopper", hopperidle, 1, 10, true);
	ANIMATION->addAnimation("jumphopper", "hopper", 0, 3, 10, false, false);
	ANIMATION->addAnimation("downhopper", "hopper", 4, 5, 10, false, false);

	//==============================================fly===========================================
	//==============================================fly===========================================
	IMAGE->addFrameImage("fly", "images/enemy/fly.bmp", 120 * 1.3, 240 * 1.3, 4, 8, true, RGB(255, 0, 255));

	ANIMATION->addAnimation("rightfly", "fly", 0, 1, 10, false, true);
	ANIMATION->addAnimation("rightAtkfly", "fly", 2, 15, 10, false, false);
	int arrleft[] = { 18, 19 };
	ANIMATION->addAnimation("leftfly", "fly", arrleft, 2, 10, true);
	int arrleftAtk[] = { 17, 16, 23,22,21,20,27,26,25,24,31,30,29,28 };
	ANIMATION->addAnimation("leftAtkfly", "fly", arrleftAtk, 14, 10, false);

	//=========================gurdy==========================================================================
	//=========================gurdy==========================================================================
	IMAGE->addFrameImage("gurdybody", "images/boss/gurdy_body.bmp", 450 * 2, 150 * 2, 3, 1, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("gurdybodybeat", "gurdybody", 0, 2, 4, false, true);
	int gurdyIdlebody[] = { 0 };
	ANIMATION->addAnimation("gurdybodyidle", "gurdybody", gurdyIdlebody, 1, 10, false);
	IMAGE->addFrameImage("gurdyface", "images/boss/gurdy_face.bmp", 360 * 2, 160 * 2, 6, 4, true, RGB(255, 0, 255));
	int gurdyIdleface[] = { 2 };
	ANIMATION->addAnimation("gurdyfaceidle", "gurdyface", 0, 2, 10, false, false);

	int gurdyatkready[] = { 5, 4, 3 };
	ANIMATION->addAnimation("gurdyatkready", "gurdyface", gurdyatkready, 3, 10, false);

	ANIMATION->addAnimation("gurdydownatkready", "gurdyface", 3, 5, 10, false, false);
	ANIMATION->addAnimation("gurdydownatk", "gurdyface", 16, 17, 10, false, true);
	ANIMATION->addAnimation("gurdydownatkclose", "gurdyface", gurdyatkready, 3, 10, false);

	ANIMATION->addAnimation("gurdyleftatkready", "gurdyface", 5, 7, 10, false, false);
	ANIMATION->addAnimation("gurdyleftatk", "gurdyface", 12, 13, 10, false, true);
	int gurdyleftclose[] = { 7,6,5 };
	ANIMATION->addAnimation("gurdyleftatkclose", "gurdyface", gurdyleftclose, 3, 10, false);

	int gurdyrightready[] = { 11, 10 , 9 };
	ANIMATION->addAnimation("gurdyrightatkready", "gurdyface", gurdyrightready, 3, 10, false);
	ANIMATION->addAnimation("gurdyrightatk", "gurdyface", 14, 15, 10, false, true);
	ANIMATION->addAnimation("gurdyrightatkclose", "gurdyface", 9, 11, 10, false, false);

	ANIMATION->addAnimation("gurdysummonflyready", "gurdyface", 18, 20, 10, false, false);
	ANIMATION->addAnimation("gurdysummonfly", "gurdyface", 20, 21, 30, false, true);
	int gurdysummonfly[] = { 22 };
	ANIMATION->addAnimation("gurdysummonflyclose", "gurdyface", gurdysummonfly, 1, 10, false);
	int gurdysummonpooter[] = { 23 };
	ANIMATION->addAnimation("gurdysummonpooter", "gurdyface", gurdysummonpooter, 1, 10, false);

	//=========================smallfly==========================================================================
	//=========================smallfly==========================================================================
	IMAGE->addFrameImage("smallfly", "images/enemy/smallfly.bmp", 38 * 1.5, 14 * 1.5, 2, 1, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("smallflyani", "smallfly", 0, 1, 100, false, true);

	//===================================MainMenu================================================================
	//===================================MainMenu================================================================
	IMAGE->addImage("title", "images/UI/title.bmp", 262 * 2, 78 * 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("title_isaac", "images/UI/titleIsaac.bmp", 270 * 2, 130 * 2, 2, 1, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("title_isaacAni", "title_isaac", 0, 1, 10, false, true);
	IMAGE->addImage("mainMenu", "images/UI/mainmenu.bmp", MAPSIZEX, MAPSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("menu_arrow", "images/UI/menuArrow.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGE->addImage("title_screen", "images/UI/titleScreen.bmp", MAPSIZEX, MAPSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("pause_menu", "images/UI/pauseMenu.bmp", 222 * 3, 194 * 3, true, RGB(255, 0, 255));
	IMAGE->addImage("black", "images/UI/bgblack.bmp", MAPSIZEX, MAPSIZEY, true, RGB(255, 0, 255));
	IMAGE->addImage("deathMenu", "images/UI/deathMenu.bmp", 222 * 3, 194 * 3, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("loading", "images/UI/loadingImage.bmp", 318 * 3, 118 * 3, 2, 1, true, RGB(255, 0, 255));
	ANIMATION->addAnimation("loadingAni", "loading", 0, 1, 10, false, true);
}
AniAddList::~AniAddList()
{
}
