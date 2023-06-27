#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "sceneTitle.h"
#include "PLAYER.h"
#include "ENEMY.h"
#include "sceneTutorial.h"
#include "scenePlay.h"
#include "sceneGameOver.h"




// グローバル変数宣言
int g_scene_id = SCENE_ID_TITLE;

int snd_decide_se_hdl;					// 決定時の効果音

// タイトル用 ---------------------------------------------------------------------------


// --------------------------------------------------------------------------------------


// デバッグ用 ---------------------------------------------------------------------------

int posX = 350;
int posY = 300;
int Rota = 0;

// --------------------------------------------------------------------------------------

void move() {
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) posY -= 10;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) posY += 10;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) posX -= 10;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) posX += 10;
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) Rota += 1;
}

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart(){
	snd_decide_se_hdl = LoadSoundMem("sound/button_se.mp3");

	background_gpc_hdl = LoadGraph("graphics/background.png");

	play_snd_bgm_hdl = LoadSoundMem("sound/Es-STAGE2.mp3");

	sceneTitleInit();

	sceneTutorialInit();

	player.init();

	// 敵機の初期化
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].init(3, 100);
	}

	for (int i = 0; i < ENEMY_TYPE2_NUM; i++) {
		enemy_type2[i].init(3, 300);
	}
	
	sceneGameOverInit();

}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	switch (g_scene_id) {
	// タイトルシーン
	case SCENE_ID_TITLE:
		move();
		sceneTitle();
		break;
	// 操作説明
	case SCENE_ID_TUTORIAL:
		sceneTutorial();
		break;
	// プレイシーン
	case SCENE_ID_PLAY:
		scenePlay(delta_time);
		break;
	// ゲームオーバーシーン
	case SCENE_ID_GAMEOVER:
		sceneGameOver(delta_time);
		break;
	}
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}
