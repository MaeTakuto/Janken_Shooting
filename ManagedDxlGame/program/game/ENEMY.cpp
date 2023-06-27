#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "PLAYER.h"
#include "ENEMY.h"
#include "scenePlay.h"


// 初期化
void ENEMY::init(int life, int score) {
	life_ = life;
	pos_ = { 640, 400, 0 };
	hand_type_ = HAND_TYPE_STONE;
	spawn_flag_ = false;
	attack_flag_ = false;

	enemy_type_stone_gpc_hdl_ = LoadGraph("graphics/stone.png");       // プレイヤー画像（グー）
	enemy_type_scissors_gpc_hdl_ = LoadGraph("graphics/scissors.png");    // プレイヤー画像（チョキ）
	enemy_type_paper_gpc_hdl_ = LoadGraph("graphics/paper.png");       // プレイヤー画像（パー）
	GetGraphSize(enemy_type_stone_gpc_hdl_, &width_, &height_);
	/*
	width_ *= ENEMY_HAND_TYPE_GPC_SIZE;
	height_ *= ENEMY_HAND_TYPE_GPC_SIZE;
	*/
	
	bullet_count_ = 0;

	int bullet_temp = LoadGraph("graphics/enemy_bullet.bmp");
	int w, h;

	GetGraphSize(bullet_temp, &w, &h);

	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		bullet_[i].flag = false;
		bullet_[i].gpc_hdl = bullet_temp;
		bullet_[i].width = w;
		bullet_[i].height = h;
		bullet_[i].dx = 0;
		bullet_[i].dy = 0;
	}

	score_ = score;

	LoadDivGraph("graphics/explode.png", 10, 10, 1, 100, 100, bomb_anim_hdls_);
	anim_frame_ = 0;
	bomb_anim_flag_ = false;
	anim_time_count_ = 0.0f;

	expl_snd_se_hdl = LoadSoundMem("sound/enemy_explode_se.mp3");
	shot_snd_se_hdl = LoadSoundMem("sound/enemy_shot_se.mp3");

	bullet_count_ = 0;
}


// プレイ画面の初期化
void ENEMY::scenePlayInit() {
	life_ = ENEMY_MAX_LIFE;  // 敵機ライフの設定
	pos_ = { 640, 400, 0 };

	spawn_flag_ = false;
	anim_frame_ = 0;
	bomb_anim_flag_ = false;
	anim_time_count_ = 0.0f;

	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		bullet_[i].flag = false;
		bullet_[i].dx = 0;
		bullet_[i].dy = 0;
	}
}

bool ENEMY::getSpawnFlag() {
	return spawn_flag_;
}

// 
int ENEMY::getScore() {
	return score_;
}

// 
int ENEMY::getWidth() {
	return width_;
}

// x座標取得
float ENEMY::getPositionX() {
	return pos_.x;
}

// 敵スポーン
void ENEMY::spawnEnemy(float spawn_pos_x) {
	spawn_flag_ = true;
	pos_.y = ENEMY_SPAWN_POS_Y;
	pos_.x = spawn_pos_x * width_ + width_;
	life_ = ENEMY_MAX_LIFE;
	hand_type_ = GetRand(HAND_TYPE_PAPER);
}

// 敵機の行動 1
void ENEMY::move() {
	pos_.y += ENEMY_SPEED;

	// if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) life_ = ENEMY_MAX_LIFE;
	
	if (pos_.y >= 750) {
		spawn_flag_ = false;
	}
}

// 敵機タイプ2の行動
void ENEMY::moveType2() {

	if (pos_.y >= 100) {
		attack_flag_ = true;
	}
	else {
		pos_.y += ENEMY_TYPE2_SPEED;
		attack_flag_ = false;
	}
}

// 敵機の弾発射
void ENEMY::shot(float target_x, float target_y) {
	bullet_count_++;

	int bullet_num_count = 0;

	// 弾の発射させる処理
	if (attack_flag_ && spawn_flag_) {
		for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
			if (bullet_[i].flag == false && bullet_count_ % 10 == 0) {
				PlaySoundMem(shot_snd_se_hdl, DX_PLAYTYPE_BACK);
				bullet_[i].flag = true;
				bullet_[i].pos = pos_;
				bullet_count_ = 0;
				bullet_[i].dx = target_x - bullet_[i].pos.x;
				bullet_[i].dy = target_y - bullet_[i].pos.y;
				bullet_[i].angle = atan2(bullet_[i].dy, bullet_[i].dx);
				break;
			}
		}
	}

	// 弾を移動させる処理
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		if (bullet_[i].flag) {
			bullet_[i].pos.y += sin(bullet_[i].angle) * ESHOT_SPEED;
			bullet_[i].pos.x += cos(bullet_[i].angle) * ESHOT_SPEED;
			if (bullet_[i].pos.y > 700)
				bullet_[i].flag = false;
		}
	}

	/*
	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		if (!bullet_[i].flag)
		{
			bullet_num_count++;
			if (bullet_num_count == ENEMY_BULLET_NUM)
			{
				attack_flag_ = false;
				bullet_num_count = 0;
			}
		}
	}
	*/

}

// ライフを減らす、死亡判定
void ENEMY::damageLife() {
	life_--;
	if (life_ <= 0) {
		deleteEnemy();
	}
}

void ENEMY::deleteEnemy() {
	spawn_flag_ = false;
	bomb_anim_flag_ = true;
	PlaySoundMem(expl_snd_se_hdl, DX_PLAYTYPE_BACK);
}

// 爆発アニメーション処理
void ENEMY::bombAnim(float delta_time) {

	anim_time_count_ += delta_time;
	if (anim_time_count_ > 0.1f) {
		anim_frame_++;
		anim_time_count_ = 0;

		if (anim_frame_ == ENEMY_BOMB_FRAME_SIZE) {
			bomb_anim_flag_ = false;
			anim_frame_ = 0;
		}
	}

}

// 敵機画像表示
void ENEMY::draw() {
	if (spawn_flag_) {
		if (hand_type_ == HAND_TYPE_STONE) {
			DrawRotaGraph(pos_.x, pos_.y, ENEMY_HAND_TYPE_GPC_SIZE, 0, enemy_type_stone_gpc_hdl_, true);
		}
		else if (hand_type_ == HAND_TYPE_SCISSORS) {
			DrawRotaGraph(pos_.x, pos_.y, ENEMY_HAND_TYPE_GPC_SIZE, 0, enemy_type_scissors_gpc_hdl_, true);
		}
		else {
			DrawRotaGraph(pos_.x, pos_.y, ENEMY_HAND_TYPE_GPC_SIZE, 0, enemy_type_paper_gpc_hdl_, true);
		}
	}

	for (int i = 0; i < ENEMY_BULLET_NUM; i++) {
		if (bullet_[i].flag) {
			DrawRotaGraph(bullet_[i].pos.x, bullet_[i].pos.y + ( height_ / 2 ), 1, 0, bullet_[i].gpc_hdl, true);
		}
	}

	if (bomb_anim_flag_) {
		DrawRotaGraph(pos_.x, pos_.y, 1.0f, 0, bomb_anim_hdls_[anim_frame_], true);
	}

}