#pragma once
#include "PLAYER.h"
#include "ENEMY.h"


enum {
	HAND_TYPE_STONE,    // 0
	HAND_TYPE_SCISSORS, // 1
	HAND_TYPE_PAPER,    // 2
	HAND_TYPE_MAX,       // 3
};

const float ENEMY_SPAWN_TIME_MIN = 0.8f;		// �X�|�[�����Ԃ̍ŏ�����
const float ENEMY_SPAWN_INTTIAL_TIME = 2.0f;		// �����X�|�[�����Ԃ̊Ԋu
const int ENEMY_NUM = 6;						// �G�l�~�[1�̍ő吔
const int ENEMY_TYPE2_NUM = 3;					// �G�l�~�[�^�C�v�Q�̍ő吔
const float ENEMY_SPAWN_DECREASE_TIME = 10.0f;	// �G�l�~�[�X�|�[�����Ԃ�Z������Ԋu 

const tnl::Vector3 PLAY_HAND_TYPE_STONE_POS = { 800, 300, 0 };
const tnl::Vector3 PLAY_HAND_TYPE_SCISSORS_POS = { 800, 450, 0 };
const tnl::Vector3 PLAY_HAND_TYPE_PAPER_POS = { 800, 600, 0 };

extern PLAYER player;
extern ENEMY enemy[ENEMY_NUM];
extern ENEMY enemy_type2[ENEMY_TYPE2_NUM];

extern int background_gpc_hdl;    // �w�i


extern int play_snd_bgm_hdl;

extern int play_score;

void scenePlayInit();
void checkHit(ENEMY& check_enemy, float delta_time);
void scenePlay(float delta_time);