#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "sceneTitle.h"
#include "PLAYER.h"
#include "ENEMY.h"
#include "scenePlay.h"
#include "sceneTutorial.h"
#include "sceneGameOver.h"


PLAYER player;
ENEMY enemy[ENEMY_NUM];
ENEMY enemy_type2[ENEMY_TYPE2_NUM];

float spawn_time_count;				// �G�̃X�|�[�����Ԃ̃J�E���g

float play_time_count;				// �v���C���Ԃ̃J�E���g

float enemy_spawn_time;				// �G�l�~�[�̃X�|�[������

int enemy_spawn_count;				// �G�̍��܂łɏo���������J�E���g

int enemy_defeat_combo;				// �G��A���œ|������

int play_score;						// �v���C�X�R�A


// --------------------------- �w�i ------------------------------
int background_gpc_hdl;							// �w�i
tnl::Vector3 background_pos = { 0, 0, 0 };		// �w�i�̈ʒu
int background_width;							// �w�i�̕�
int background_height;							// �w�i�̍���

// ------------------------ �T�E���h -----------------------------

int play_snd_bgm_hdl;




// ������
void scenePlayInit() {
	spawn_time_count = 0;
	enemy_spawn_count = 0;
	play_time_count = 0.0f;
	enemy_spawn_time = ENEMY_SPAWN_INTTIAL_TIME;								// �G�l�~�[�̃X�|�[�����鎞��
	play_score = 0;

	GetGraphSize(background_gpc_hdl, &background_width, &background_height);

	player.scenePlayInit();     // �v���C���[������

	// �G�@�̏�����
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].scenePlayInit();
	}
	for (int i = 0; i < ENEMY_TYPE2_NUM; i++) {
		enemy_type2[i].scenePlayInit();
	}

	PlaySoundMem(play_snd_bgm_hdl, DX_PLAYTYPE_LOOP, true);
}


// �����蔻��
void checkHit(ENEMY &check_enemy, float delta_time) {

	// �G�Ƀv���C���[�@�̒e������������
	for (int i = 0; i < PLAYER_BULLET_NUM; i++) {
		if ( tnl::IsIntersectRect(check_enemy.pos_, check_enemy.width_, check_enemy.height_, player.bullet[i].pos, player.bullet[i].width, player.bullet[i].height)
			&& player.bullet[i].flag && check_enemy.spawn_flag_ )
		{
			if ( player.bullet[i].hand_type == HAND_TYPE_STONE && check_enemy.hand_type_ == HAND_TYPE_SCISSORS) {
				player.setBulletFlag(i, false);
				check_enemy.damageLife();

				if (!check_enemy.spawn_flag_) {
					play_score += check_enemy.getScore();
				}
			}
			else if (player.bullet[i].hand_type == HAND_TYPE_SCISSORS && check_enemy.hand_type_ == HAND_TYPE_PAPER) {
				player.setBulletFlag(i, false);
				check_enemy.damageLife();

				if (!check_enemy.spawn_flag_) {
					play_score += check_enemy.getScore();
				}
			}
			else if (player.bullet[i].hand_type == HAND_TYPE_PAPER && check_enemy.hand_type_ == HAND_TYPE_STONE) {
				player.setBulletFlag(i, false);
				check_enemy.damageLife();

				if (!check_enemy.spawn_flag_) {
					play_score += check_enemy.getScore();
				}
			}
			else {
				player.setBulletFlag(i, false);
			}
		}
	}

	// �v���C���[�@�ƓG�̓����蔻��
	if ( tnl::IsIntersectRect(check_enemy.pos_, check_enemy.width_, check_enemy.height_, player.pos_, player.width_ / 2 , player.height_ / 2 ) && check_enemy.spawn_flag_ ) {
		check_enemy.deleteEnemy();

		// �v���C���[���C�t�����炷����
		if (!player.invincible_flag_) {
			player.damageLife();
		}
	}

	// �v���C���[�ƓG�̒e�̓����蔻��
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		if (tnl::IsIntersectSphere(check_enemy.bullet_[i].pos, check_enemy.bullet_[i].width / 2, player.pos_, player.width_ / 2) 
			&& check_enemy.bullet_[i].flag) {
			check_enemy.bullet_[i].flag = false;

			// �v���C���[���C�t�����炷����
			if (!player.invincible_flag_) {
				player.damageLife();
			}
		}
	}
}


// �v���C�V�[���̕`��
void scenePlayDraw() {

	SetFontSize(30);

	// �v���C���[���C�t�\��
	DrawStringEx(800, 100, -1, "�v���C���[���C�t�F%d", player.getLife());

	// �X�R�A�\��
	DrawStringEx(800, 150, -1, "SCORE = %d", play_score);

	// �v���C���ԕ\��
	DrawStringEx(800, 200, -1, "�v���C���� = %.1f", play_time_count);

	/*
	DrawStringEx(800, 300, -1, "spawn_time_count = %f", spawn_time_count);
	DrawStringEx(800, 350, -1, "enemy_spawn_count = %d", enemy_spawn_count);
	DrawStringEx(800, 400, -1, "�X�|�[���Ԋu = %.1f", enemy_spawn_time);
	*/


	// �w�i�\��
	DrawGraph(background_pos.x, background_pos.y, background_gpc_hdl, false);
	DrawGraph(background_pos.x, background_pos.y - background_height, background_gpc_hdl, false);

	// ��������@�\��
	DrawGraph(PLAY_HAND_TYPE_STONE_POS.x, PLAY_HAND_TYPE_STONE_POS.y, t_hand_type_stone_hdl, true);
	DrawStringEx(PLAY_HAND_TYPE_STONE_POS.x + 100, PLAY_HAND_TYPE_STONE_POS.y + 50, -1, ":  A�L�[");

	DrawGraph(PLAY_HAND_TYPE_SCISSORS_POS.x , PLAY_HAND_TYPE_SCISSORS_POS.y, t_hand_type_scissors_hdl, true);
	DrawStringEx(PLAY_HAND_TYPE_SCISSORS_POS.x + 100, PLAY_HAND_TYPE_SCISSORS_POS.y + 50, -1, ":  W�L�[");

	DrawGraph(PLAY_HAND_TYPE_PAPER_POS.x, PLAY_HAND_TYPE_PAPER_POS.y, t_hand_type_paper_hdl, true);
	DrawStringEx(PLAY_HAND_TYPE_PAPER_POS.x + 100, PLAY_HAND_TYPE_PAPER_POS.y + 50, -1, ":  D�L�[");

	// �v���C���[�\��
	player.draw();


	// �G�l�~�[�\��
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].draw();
	}

	// �G�l�~�[�^�C�v2�\��
	for (int i = 0; i < ENEMY_TYPE2_NUM; i++) {
		enemy_type2[i].draw();
	}
}


// �v���C�V�[�����̏���
void scenePlay(float delta_time) {

	play_time_count += delta_time;
	spawn_time_count += delta_time;

	// �w�i�ړ�
	background_pos.y += 2.0f;
	if (background_pos.y > (float)background_height ) {
		background_pos.y = 0;
	}

	// �v���C���[����
	if (player.getLifeFlag()) {
		player.move();
		player.shot();


		player.damageProcess(delta_time);

	}
	
	/*
	// �G�^�C�v2�̃f�o�b�O�p
	for (int i = 0; i < ENEMY_TYPE2_NUM; i++) {
		if (spawn_time_count > enemy_spawn_time && enemy_type2[i].getSpawnFlag() == false && !enemy_type2[i].bomb_anim_flag_)
		{
			float spawn_pos_x = (float)GetRand(6);
			enemy_type2[i].spawnEnemy(spawn_pos_x);
			spawn_time_count = 0;
			break;
		}
	}
	*/
	
	
	
	// �G�̃X�|�[��
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (spawn_time_count > enemy_spawn_time && enemy[i].getSpawnFlag() == false && !enemy[i].bomb_anim_flag_)
		{
			float spawn_pos_x = (float)GetRand(6);
			enemy[i].spawnEnemy(spawn_pos_x);
			spawn_time_count = 0;
			enemy_spawn_count++;

			// �X�|�[�����Ԃ̌���
			if((int)play_time_count % (int)ENEMY_SPAWN_DECREASE_TIME == 0) {
				if (enemy_spawn_time > ENEMY_SPAWN_TIME_MIN) {
					enemy_spawn_time -= 0.2f;
				}
			}
			break;
		}
	}

	// �G�^�C�v 2 �̃X�|�[��
	for (int i = 0; i < ENEMY_TYPE2_NUM; i++) {
		if (enemy_spawn_count >= 5 && enemy_type2[i].getSpawnFlag() == false && !enemy_type2[i].bomb_anim_flag_)
		{
			// �����_���ȍ��W�𐶐�
			float spawn_pos_x;
			bool isOverlap;
			do {
				spawn_pos_x = (float)GetRand(6);

				// �����̓G�ƍ��W���d�����Ă��邩�`�F�b�N
				isOverlap = false;
				for (int j = 0; j < ENEMY_TYPE2_NUM; j++) {
					if (i != j && spawn_pos_x * enemy_type2[i].getWidth() + enemy_type2[i].getWidth() == enemy_type2[j].getPositionX() && enemy_type2[j].getSpawnFlag()) {
						isOverlap = true;
						break;
					}
				}
			} while (isOverlap);

			// �X�|�[�������Ȃ�
			enemy_type2[i].spawnEnemy(spawn_pos_x);
			enemy_spawn_count = 0;
			break;
		}
	}
	

	// �G�̍s��
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy[i].getSpawnFlag() && !enemy[i].bomb_anim_flag_) {
			enemy[i].move();
			checkHit(enemy[i], delta_time);    // �����蔻��
		}

		// �G�@�̔�������
		if (enemy[i].bomb_anim_flag_) {
			enemy[i].bombAnim(delta_time);
		}
	}

	// �G�^�C�v2�̍s��
	for (int i = 0; i < ENEMY_TYPE2_NUM; i++) {
		if (enemy_type2[i].getSpawnFlag() && !enemy_type2[i].bomb_anim_flag_) {
			enemy_type2[i].moveType2();
		}

		enemy_type2[i].shot(player.pos_.x, player.pos_.y);
		checkHit(enemy_type2[i], delta_time);    // �����蔻��


		// �G�@�̔�������
		if (enemy_type2[i].bomb_anim_flag_) {
			enemy_type2[i].bombAnim(delta_time);
		}
	}


	// �摜�\��
	scenePlayDraw();

	/*
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		g_scene_id = SCENE_ID_TITLE;
		StopSoundMem(play_snd_bgm_hdl);
	}
	*/


	// �v���C���[���S���̏���
	if (!player.getLifeFlag()) {
		sceneGameOverInit();
		g_scene_id = SCENE_ID_GAMEOVER;
		StopSoundMem(play_snd_bgm_hdl);
	}

}