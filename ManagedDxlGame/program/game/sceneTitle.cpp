#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "sceneTitle.h"
#include "PLAYER.h"
#include "ENEMY.h"
#include "scenePlay.h"

int g_gpc_sel_cursor_hdl;    // カーソル画像の格納用
tnl::Vector3 g_sel_cursor_pos = SEL_CURSOR_POS_TBL[MODE_SEL_TYPE_START];  // カーソルの座標
int g_sel_mode = MODE_SEL_TYPE_START;

// ----------------------------------- 効果音 --------------------------------------

int snd_select_se_hdl;					// 選択時の効果音

// ---------------------------------------------------------------------------------

void sceneTitleInit() {
	g_gpc_sel_cursor_hdl = LoadGraph("graphics/cursor.png");

	snd_select_se_hdl = LoadSoundMem("sound/select_se.mp3");
}

void scenTitleDraw() {
	SetFontSize(TITLE_FONT_SIZE);
	DrawStringEx(TITLE_LOGO_POS.x, TITLE_LOGO_POS.y, -1, TITLE_LOGO_STR.c_str());

	SetFontSize(20);
	DrawStringEx(SEL_TYPE_START_LOGO_POS.x, SEL_TYPE_START_LOGO_POS.y, -1, SEL_TYPE_START_LOGO_STR.c_str());
	DrawStringEx(SEL_TYPE_END_LOGO_POS.x, SEL_TYPE_END_LOGO_POS.y, -1, SEL_TYPE_END_LOGO_STR.c_str());
	DrawRotaGraphF(g_sel_cursor_pos.x, g_sel_cursor_pos.y, 0.1, 8, g_gpc_sel_cursor_hdl, true);
}

void sceneTitle() {

	scenTitleDraw();

	// DrawStringEx(posX, posY, -1, SEL_TYPE_END_LOGO_STR.c_str());

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP))
	{
		PlaySoundMem(snd_select_se_hdl, DX_PLAYTYPE_BACK);

		g_sel_mode--;
		if (g_sel_mode < MODE_SEL_TYPE_START) g_sel_mode = MODE_SEL_TYPE_END;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN))
	{
		PlaySoundMem(snd_select_se_hdl, DX_PLAYTYPE_BACK);

		g_sel_mode++;
		if (g_sel_mode >= MODE_SEL_TYPE_MAX) g_sel_mode = MODE_SEL_TYPE_START;
	}
	g_sel_cursor_pos = SEL_CURSOR_POS_TBL[g_sel_mode];

	// Enter Keyを押したときの処理
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		PlaySoundMem(snd_decide_se_hdl, DX_PLAYTYPE_BACK);
		
		if (g_sel_mode == MODE_SEL_TYPE_START)
		{
			g_scene_id = SCENE_ID_TUTORIAL;
		}
		else if (g_sel_mode == MODE_SEL_TYPE_END)
		{
			DxLib_End();
		}
	}
}