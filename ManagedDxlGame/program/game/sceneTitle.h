#pragma once

// カーソルを表示する座標
const tnl::Vector3 SEL_CURSOR_POS_TBL[2]{
	{510, 405, 0},                        // Game Startの位置
	{510, 455, 0}                         // Exitの位置
};

enum {
	MODE_SEL_TYPE_START,
	MODE_SEL_TYPE_END,
	MODE_SEL_TYPE_MAX
};

const std::string TITLE_LOGO_STR = "  じゃんけん\nシューティング！";
const tnl::Vector3 TITLE_LOGO_POS = { 300, 100, 0 };

const std::string SEL_TYPE_START_LOGO_STR = "Game Start";
const std::string SEL_TYPE_END_LOGO_STR = "Exit";

const tnl::Vector3 SEL_TYPE_START_LOGO_POS = { 540, 400, 0 };
const tnl::Vector3 SEL_TYPE_END_LOGO_POS = { 570, 450, 0 };

// ----------------------------------- 効果音 --------------------------------------

extern int snd_select_se_hdl;					// 選択時の効果音

// ---------------------------------------------------------------------------------


extern int g_gpc_sel_cursor_hdl;    // カーソル画像の格納用
extern tnl::Vector3 g_sel_cursor_pos;  // カーソルの座標
extern int g_sel_mode;

void sceneTitleInit();

void sceneTitle();