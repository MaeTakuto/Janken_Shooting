#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "scenePlay.h"
#include "sceneTutorial.h"

int t_hand_type_stone_hdl;
int t_hand_type_scissors_hdl;
int t_hand_type_paper_hdl;

void sceneTutorialInit() {
	t_hand_type_stone_hdl = LoadGraph("graphics/stone.png");
	t_hand_type_scissors_hdl = LoadGraph("graphics/scissors.png");
	t_hand_type_paper_hdl = LoadGraph("graphics/paper.png");
}

void sceneTutorialDraw() {
	SetFontSize(TITLE_FONT_SIZE);
	DrawStringEx(450, 50, -1, "�������");

	DrawGraph(T_HAND_TYPE_STONE_POS.x, T_HAND_TYPE_STONE_POS.y, t_hand_type_stone_hdl, true);
	DrawGraph(T_HAND_TYPE_SCISSORS_POS.x, T_HAND_TYPE_SCISSORS_POS.y, t_hand_type_scissors_hdl, true);
	DrawGraph(T_HAND_TYPE_PAPER_POS.x, T_HAND_TYPE_PAPER_POS.y, t_hand_type_paper_hdl, true);

	SetFontSize(30);
	DrawStringEx(T_HAND_TYPE_STONE_POS.x + 100, T_HAND_TYPE_STONE_POS.y + 50, -1, ":  A�L�[");
	DrawStringEx(T_HAND_TYPE_SCISSORS_POS.x + 100, T_HAND_TYPE_SCISSORS_POS.y + 50, -1, ":  W�L�[");
	DrawStringEx(T_HAND_TYPE_PAPER_POS.x + 100, T_HAND_TYPE_PAPER_POS.y + 50, -1, ":  D�L�[");

	DrawStringEx(700, 250, -1, "���E�ړ��F�}�E�X");
}

void sceneTutorial() {

	// �G���^�[�L�[�Ńv���C��ʂɈړ�
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		PlaySoundMem(snd_decide_se_hdl, DX_PLAYTYPE_BACK);

		g_scene_id = SCENE_ID_PLAY;
		scenePlayInit();
	}

	sceneTutorialDraw();
}