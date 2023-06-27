#pragma once

// �J�[�\����\��������W
const tnl::Vector3 SEL_CURSOR_POS_TBL[2]{
	{510, 405, 0},                        // Game Start�̈ʒu
	{510, 455, 0}                         // Exit�̈ʒu
};

enum {
	MODE_SEL_TYPE_START,
	MODE_SEL_TYPE_END,
	MODE_SEL_TYPE_MAX
};

const std::string TITLE_LOGO_STR = "  ����񂯂�\n�V���[�e�B���O�I";
const tnl::Vector3 TITLE_LOGO_POS = { 300, 100, 0 };

const std::string SEL_TYPE_START_LOGO_STR = "Game Start";
const std::string SEL_TYPE_END_LOGO_STR = "Exit";

const tnl::Vector3 SEL_TYPE_START_LOGO_POS = { 540, 400, 0 };
const tnl::Vector3 SEL_TYPE_END_LOGO_POS = { 570, 450, 0 };

// ----------------------------------- ���ʉ� --------------------------------------

extern int snd_select_se_hdl;					// �I�����̌��ʉ�

// ---------------------------------------------------------------------------------


extern int g_gpc_sel_cursor_hdl;    // �J�[�\���摜�̊i�[�p
extern tnl::Vector3 g_sel_cursor_pos;  // �J�[�\���̍��W
extern int g_sel_mode;

void sceneTitleInit();

void sceneTitle();