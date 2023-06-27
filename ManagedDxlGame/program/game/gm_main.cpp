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




// �O���[�o���ϐ��錾
int g_scene_id = SCENE_ID_TITLE;

int snd_decide_se_hdl;					// ���莞�̌��ʉ�

// �^�C�g���p ---------------------------------------------------------------------------


// --------------------------------------------------------------------------------------


// �f�o�b�O�p ---------------------------------------------------------------------------

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
// �Q�[���N�����ɂP�x�������s����܂�
void gameStart(){
	snd_decide_se_hdl = LoadSoundMem("sound/button_se.mp3");

	background_gpc_hdl = LoadGraph("graphics/background.png");

	play_snd_bgm_hdl = LoadSoundMem("sound/Es-STAGE2.mp3");

	sceneTitleInit();

	sceneTutorialInit();

	player.init();

	// �G�@�̏�����
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].init(3, 100);
	}

	for (int i = 0; i < ENEMY_TYPE2_NUM; i++) {
		enemy_type2[i].init(3, 300);
	}
	
	sceneGameOverInit();

}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s����܂�
void gameMain(float delta_time) {

	switch (g_scene_id) {
	// �^�C�g���V�[��
	case SCENE_ID_TITLE:
		move();
		sceneTitle();
		break;
	// �������
	case SCENE_ID_TUTORIAL:
		sceneTutorial();
		break;
	// �v���C�V�[��
	case SCENE_ID_PLAY:
		scenePlay(delta_time);
		break;
	// �Q�[���I�[�o�[�V�[��
	case SCENE_ID_GAMEOVER:
		sceneGameOver(delta_time);
		break;
	}
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s����܂�
void gameEnd() {

}
