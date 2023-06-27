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

float spawn_time_count;				// 敵のスポーン時間のカウント

float play_time_count;				// プレイ時間のカウント

float enemy_spawn_time;				// エネミーのスポーン時間

int enemy_spawn_count;				// 敵の今までに出現した数カウント

int enemy_defeat_combo;				// 敵を連続で倒した数

int play_score;						// プレイスコア


// --------------------------- 背景 ------------------------------
int background_gpc_hdl;							// 背景
tnl::Vector3 background_pos = { 0, 0, 0 };		// 背景の位置
int background_width;							// 背景の幅
int background_height;							// 背景の高さ

// ------------------------ サウンド -----------------------------

int play_snd_bgm_hdl;




// 初期化
void scenePlayInit() {
	spawn_time_count = 0;
	enemy_spawn_count = 0;
	play_time_count = 0.0f;
	enemy_spawn_time = ENEMY_SPAWN_INTTIAL_TIME;								// エネミーのスポーンする時間
	play_score = 0;

	GetGraphSize(background_gpc_hdl, &background_width, &background_height);

	player.scenePlayInit();     // プレイヤー初期化

	// 敵機の初期化
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].scenePlayInit();
	}
	for (int i = 0; i < ENEMY_TYPE2_NUM; i++) {
		enemy_type2[i].scenePlayInit();
	}

	PlaySoundMem(play_snd_bgm_hdl, DX_PLAYTYPE_LOOP, true);
}


// 当たり判定
void checkHit(ENEMY &check_enemy, float delta_time) {

	// 敵にプレイヤー機の弾が当たった時
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

	// プレイヤー機と敵の当たり判定
	if ( tnl::IsIntersectRect(check_enemy.pos_, check_enemy.width_, check_enemy.height_, player.pos_, player.width_ / 2 , player.height_ / 2 ) && check_enemy.spawn_flag_ ) {
		check_enemy.deleteEnemy();

		// プレイヤーライフを減らす処理
		if (!player.invincible_flag_) {
			player.damageLife();
		}
	}

	// プレイヤーと敵の弾の当たり判定
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		if (tnl::IsIntersectSphere(check_enemy.bullet_[i].pos, check_enemy.bullet_[i].width / 2, player.pos_, player.width_ / 2) 
			&& check_enemy.bullet_[i].flag) {
			check_enemy.bullet_[i].flag = false;

			// プレイヤーライフを減らす処理
			if (!player.invincible_flag_) {
				player.damageLife();
			}
		}
	}
}


// プレイシーンの描画
void scenePlayDraw() {

	SetFontSize(30);

	// プレイヤーライフ表示
	DrawStringEx(800, 100, -1, "プレイヤーライフ：%d", player.getLife());

	// スコア表示
	DrawStringEx(800, 150, -1, "SCORE = %d", play_score);

	// プレイ時間表示
	DrawStringEx(800, 200, -1, "プレイ時間 = %.1f", play_time_count);

	/*
	DrawStringEx(800, 300, -1, "spawn_time_count = %f", spawn_time_count);
	DrawStringEx(800, 350, -1, "enemy_spawn_count = %d", enemy_spawn_count);
	DrawStringEx(800, 400, -1, "スポーン間隔 = %.1f", enemy_spawn_time);
	*/


	// 背景表示
	DrawGraph(background_pos.x, background_pos.y, background_gpc_hdl, false);
	DrawGraph(background_pos.x, background_pos.y - background_height, background_gpc_hdl, false);

	// 操作説明　表示
	DrawGraph(PLAY_HAND_TYPE_STONE_POS.x, PLAY_HAND_TYPE_STONE_POS.y, t_hand_type_stone_hdl, true);
	DrawStringEx(PLAY_HAND_TYPE_STONE_POS.x + 100, PLAY_HAND_TYPE_STONE_POS.y + 50, -1, ":  Aキー");

	DrawGraph(PLAY_HAND_TYPE_SCISSORS_POS.x , PLAY_HAND_TYPE_SCISSORS_POS.y, t_hand_type_scissors_hdl, true);
	DrawStringEx(PLAY_HAND_TYPE_SCISSORS_POS.x + 100, PLAY_HAND_TYPE_SCISSORS_POS.y + 50, -1, ":  Wキー");

	DrawGraph(PLAY_HAND_TYPE_PAPER_POS.x, PLAY_HAND_TYPE_PAPER_POS.y, t_hand_type_paper_hdl, true);
	DrawStringEx(PLAY_HAND_TYPE_PAPER_POS.x + 100, PLAY_HAND_TYPE_PAPER_POS.y + 50, -1, ":  Dキー");

	// プレイヤー表示
	player.draw();


	// エネミー表示
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].draw();
	}

	// エネミータイプ2表示
	for (int i = 0; i < ENEMY_TYPE2_NUM; i++) {
		enemy_type2[i].draw();
	}
}


// プレイシーン内の処理
void scenePlay(float delta_time) {

	play_time_count += delta_time;
	spawn_time_count += delta_time;

	// 背景移動
	background_pos.y += 2.0f;
	if (background_pos.y > (float)background_height ) {
		background_pos.y = 0;
	}

	// プレイヤー処理
	if (player.getLifeFlag()) {
		player.move();
		player.shot();


		player.damageProcess(delta_time);

	}
	
	/*
	// 敵タイプ2のデバッグ用
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
	
	
	
	// 敵のスポーン
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (spawn_time_count > enemy_spawn_time && enemy[i].getSpawnFlag() == false && !enemy[i].bomb_anim_flag_)
		{
			float spawn_pos_x = (float)GetRand(6);
			enemy[i].spawnEnemy(spawn_pos_x);
			spawn_time_count = 0;
			enemy_spawn_count++;

			// スポーン時間の減少
			if((int)play_time_count % (int)ENEMY_SPAWN_DECREASE_TIME == 0) {
				if (enemy_spawn_time > ENEMY_SPAWN_TIME_MIN) {
					enemy_spawn_time -= 0.2f;
				}
			}
			break;
		}
	}

	// 敵タイプ 2 のスポーン
	for (int i = 0; i < ENEMY_TYPE2_NUM; i++) {
		if (enemy_spawn_count >= 5 && enemy_type2[i].getSpawnFlag() == false && !enemy_type2[i].bomb_anim_flag_)
		{
			// ランダムな座標を生成
			float spawn_pos_x;
			bool isOverlap;
			do {
				spawn_pos_x = (float)GetRand(6);

				// 既存の敵と座標が重複しているかチェック
				isOverlap = false;
				for (int j = 0; j < ENEMY_TYPE2_NUM; j++) {
					if (i != j && spawn_pos_x * enemy_type2[i].getWidth() + enemy_type2[i].getWidth() == enemy_type2[j].getPositionX() && enemy_type2[j].getSpawnFlag()) {
						isOverlap = true;
						break;
					}
				}
			} while (isOverlap);

			// スポーン処理など
			enemy_type2[i].spawnEnemy(spawn_pos_x);
			enemy_spawn_count = 0;
			break;
		}
	}
	

	// 敵の行動
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy[i].getSpawnFlag() && !enemy[i].bomb_anim_flag_) {
			enemy[i].move();
			checkHit(enemy[i], delta_time);    // 当たり判定
		}

		// 敵機の爆発処理
		if (enemy[i].bomb_anim_flag_) {
			enemy[i].bombAnim(delta_time);
		}
	}

	// 敵タイプ2の行動
	for (int i = 0; i < ENEMY_TYPE2_NUM; i++) {
		if (enemy_type2[i].getSpawnFlag() && !enemy_type2[i].bomb_anim_flag_) {
			enemy_type2[i].moveType2();
		}

		enemy_type2[i].shot(player.pos_.x, player.pos_.y);
		checkHit(enemy_type2[i], delta_time);    // 当たり判定


		// 敵機の爆発処理
		if (enemy_type2[i].bomb_anim_flag_) {
			enemy_type2[i].bombAnim(delta_time);
		}
	}


	// 画像表示
	scenePlayDraw();

	/*
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		g_scene_id = SCENE_ID_TITLE;
		StopSoundMem(play_snd_bgm_hdl);
	}
	*/


	// プレイヤー死亡時の処理
	if (!player.getLifeFlag()) {
		sceneGameOverInit();
		g_scene_id = SCENE_ID_GAMEOVER;
		StopSoundMem(play_snd_bgm_hdl);
	}

}