#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "scenePlay.h"
#include "sceneGameOver.h"

float result_draw_time_count;				// ���U���g�\���̎��ԊԊu

int result_draw_count;						// ���U���g�\����

int gameover_seq_id;

int high_score = 0;							// �n�C�X�R�A

int logo_draw_num;							// ���S�\����

bool high_score_flag;

int logo_draw_snd_se_hdl;					// ���S�\�����̌��ʉ�

// ���ʉ����{��( ���x���A�b�v )�g�p
int highscore_snd_se_hdl;					// �n�C�X�R�A�̌��ʉ�

// Springin��(�y�V���[�g�zSF2-��- )�g�p
int scene_go_snd_bgm_hdl;					// �Q�[���I�[�o�[�V�[����BGM

void  sceneGameOverDraw();

void sceneGameOverInit() {
	gameover_seq_id = GO_SEQ_LOGO_DRAW;

	logo_draw_num = 0;

	result_draw_time_count = 0;

	high_score_flag = false;

	logo_draw_snd_se_hdl = LoadSoundMem("sound/hit_se.mp3");

	highscore_snd_se_hdl = LoadSoundMem("sound/highscore_se.mp3");

	scene_go_snd_bgm_hdl = LoadSoundMem("sound/result_bgm.mp3");
}

void  sceneGameOverDraw() {

	SetFontSize(TITLE_FONT_SIZE);
	if (logo_draw_num  > DRAW_RESULT_LOGO)
	DrawStringEx(GAMEOVER_LOGO_POS.x, GAMEOVER_LOGO_POS.y, -1, GAMEOVER_LOGO_STR.c_str());
	
	SetFontSize(30);
	if (logo_draw_num > DRAW_SCORE_LOGO)
		DrawStringEx(480, 350, -1, "SCORE = %6d", play_score);

	if (logo_draw_num > DRAW_HIGHSCORE_LOGO)
		DrawStringEx(HIGHSCORE_LOGO_POS.x, HIGHSCORE_LOGO_POS.y, -1, "HIGH SCORE = %6d", high_score);

	if (high_score_flag)
		DrawStringEx(HIGHSCORE_LOGO_POS.x + 350, HIGHSCORE_LOGO_POS.y, -1, "NEW RECORD !");

	if (gameover_seq_id == GO_SEQ_RESULT) {
		SetFontSize(DEFAULT_FONT_SIZE);
		DrawStringEx(500, 500, -1, "Enter�F�^�C�g���ɖ߂�");
	}

}

// �Q�[���I�[�o�[�V�[���̏���
void sceneGameOver(float delta_time) {

	// ���S�\���V�[�P���X
	if (gameover_seq_id == GO_SEQ_LOGO_DRAW) {
		result_draw_time_count += delta_time;

		if (result_draw_time_count > RESULT_DRAW_TIME_MAX)
		{
			logo_draw_num++;
			result_draw_time_count = 0;
			PlaySoundMem(logo_draw_snd_se_hdl, DX_PLAYTYPE_BACK);

			if (logo_draw_num == DRAW_LOGO_MAX)
				gameover_seq_id = GO_SEQ_SCORE_UPDATE;
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			logo_draw_num = DRAW_LOGO_MAX;
			gameover_seq_id = GO_SEQ_SCORE_UPDATE;
		}
	}
	else if (gameover_seq_id == GO_SEQ_SCORE_UPDATE) {

		result_draw_time_count += delta_time;

		if (result_draw_time_count > RESULT_DRAW_TIME_MAX && !high_score_flag)
		{
			if (play_score > high_score) {

				
				PlaySoundMem(highscore_snd_se_hdl, DX_PLAYTYPE_BACK);

				high_score = play_score;
				high_score_flag = true;
				result_draw_time_count = 0;
			}
			else {
				gameover_seq_id = GO_SEQ_RESULT;
				PlaySoundMem(scene_go_snd_bgm_hdl, DX_PLAYTYPE_LOOP, true);
			}
		}

		if (high_score_flag && !CheckSoundMem(highscore_snd_se_hdl)) {
			PlaySoundMem(scene_go_snd_bgm_hdl, DX_PLAYTYPE_LOOP, true);
			gameover_seq_id = GO_SEQ_RESULT;
		}
	}
	// ���U���g�\���V�[�P���X
	else {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			PlaySoundMem(snd_decide_se_hdl, DX_PLAYTYPE_BACK);
			StopSoundMem(scene_go_snd_bgm_hdl);

			g_scene_id = SCENE_ID_TITLE;
		}
	}

	sceneGameOverDraw();
}