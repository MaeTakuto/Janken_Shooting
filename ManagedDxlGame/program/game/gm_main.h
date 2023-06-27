#pragma once

enum {
	SCENE_ID_TITLE,
	SCENE_ID_TUTORIAL,
	SCENE_ID_PLAY,
	SCENE_ID_GAMEOVER
};

const int TITLE_FONT_SIZE = 80;

extern int g_scene_id;

extern int snd_decide_se_hdl;					// Œˆ’èŽž‚ÌŒø‰Ê‰¹

void gameStart();
void gameMain( float delta_time );
void gameEnd();