#pragma once

enum {
	GO_SEQ_LOGO_DRAW,
	GO_SEQ_SCORE_UPDATE,
	GO_SEQ_RESULT
};

enum {
	DRAW_RESULT_LOGO,
	DRAW_SCORE_LOGO,
	DRAW_HIGHSCORE_LOGO,
	DRAW_LOGO_MAX
};

const std::string GAMEOVER_LOGO_STR = "RESULT";
const tnl::Vector3 GAMEOVER_LOGO_POS = { 500, 100, 0 };

const tnl::Vector3 HIGHSCORE_LOGO_POS = { 400, 400, 0 };

const float RESULT_DRAW_TIME_MAX = 0.7f;

extern int high_score;

void sceneGameOverInit();
void sceneGameOver(float delta_time);