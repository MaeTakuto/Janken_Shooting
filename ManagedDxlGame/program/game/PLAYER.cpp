#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "PLAYER.h"
#include "ENEMY.h"
#include "scenePlay.h"

int num = 0;

// プレイヤー変数の初期化
void PLAYER::init() {
	player_type_stone_gpc_hdl_ = LoadGraph("graphics/stone.png");         // プレイヤー画像（グー）
	player_type_scissors_gpc_hdl_ = LoadGraph("graphics/scissors.png");
	player_type_paper_gpc_hdl_ = LoadGraph("graphics/paper.png");
	GetGraphSize(player_type_stone_gpc_hdl_, &width_, &height_);

	/*
	width_ *= PLAYER_HAND_TYPE_GPC_SIZE;
	height_ *= PLAYER_HAND_TYPE_GPC_SIZE;
	*/

	life_ = MAX_LIFE;
	life_flag_ = true;
	pos_ = { 640, 670, 0 };
	mouseX = 0;
	hand_type_ = HAND_TYPE_STONE;

	damage_effect_flag_ = false;

	invincible_flag_ = false;
	invincible_time_ = 0.0;

	hand_change_snd_se_hdl =	LoadSoundMem("sound/hand_change_se.mp3");
	dmg_snd_se_hdl =			LoadSoundMem("sound/player_damage_se.mp3");

	bullet_count_ = 0;

	int bullet_temp_stone =		LoadGraph("graphics/player_bullet.bmp");
	int bullet_temp_scissors =	LoadGraph("graphics/player_bullet2.bmp");
	int bullet_temp_paper =		LoadGraph("graphics/player_bullet3.bmp");
	int w, h;

	GetGraphSize(bullet_temp_stone, &w, &h);

	for (int i = 0; i < PLAYER_BULLET_NUM; i++) {
		bullet[i].bullet_type_stone_hdl = bullet_temp_stone;
		bullet[i].bullet_type_scissors_hdl = bullet_temp_scissors;
		bullet[i].bullet_type_paper_hdl = bullet_temp_paper;
		bullet[i].flag = false;
		bullet[i].width = w;
		bullet[i].height = h;
		bullet[i].hand_type = hand_type_;
	}
}

// プレイ画面の初期化
void PLAYER::scenePlayInit()
{
	life_ = MAX_LIFE;				// ライフの初期化
	life_flag_ = true;				// 生存判定
	damage_effect_flag_ = false;
}

// ライフ取得
int PLAYER::getLife() {
	return life_;
}

// ライフフラグ取得
bool PLAYER::getLifeFlag() {
	return life_flag_;
}

void PLAYER::move() {
	/*
	if (tnl::Input::IsKeyDown(eKeys::KB_LEFT)) {
		x_ -= PLAYER_SPEED;
		if (x_ <= 30) x_ = 30;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_RIGHT)) {
		x_ += PLAYER_SPEED;
		if (x_ >= 1250) x_ = 1250;
	}
	*/
	GetMousePoint( &mouseX, 0 ); 
	player.pos_.x = mouseX;
	if (pos_.x <= 30) pos_.x = 30;
	if (pos_.x >= 700) pos_.x = 700;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_W)) {
		hand_type_ = HAND_TYPE_SCISSORS;
		PlaySoundMem(hand_change_snd_se_hdl, DX_PLAYTYPE_BACK);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_A)) {
		hand_type_ = HAND_TYPE_STONE;
		PlaySoundMem(hand_change_snd_se_hdl, DX_PLAYTYPE_BACK);
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_D)) {
		hand_type_ = HAND_TYPE_PAPER;
		PlaySoundMem(hand_change_snd_se_hdl, DX_PLAYTYPE_BACK);
	}
}

void PLAYER::shot() {
	// 弾の発射させる処理
	bullet_count_++;

	for (int i = 0; i < PLAYER_BULLET_NUM; i++) {
		if (bullet[i].flag == false && bullet_count_ % 10 == 0) {
			bullet[i].flag = true;
			bullet[i].hand_type = hand_type_;
			bullet[i].pos = pos_;
			bullet_count_ = 0;
			break;
		}
	}

	// 弾を移動させる処理
	for (int i = 0; i < PLAYER_BULLET_NUM; i++) {
		if (bullet[i].flag) {
			bullet[i].pos.y -= PSHOT_SPEED;
			if (bullet[i].pos.y < 0)
				bullet[i].flag = false;
		}
	}
}

void PLAYER::setBulletFlag(int bullet_num, bool flag)
{
	bullet[ bullet_num ].flag = flag;
	num = bullet_num;
}

// ライフを減らす
void PLAYER::damageLife()
{
	life_--;

	// プレイヤーライフが０になった場合
	if (life_ <= 0) {
		SetDrawBright(255, 255, 255);
		life_flag_ = false;
	}
	PlaySoundMem(dmg_snd_se_hdl, DX_PLAYTYPE_BACK);
	damage_effect_flag_ = true;
	invincible_flag_ = true;
}


void PLAYER::damageProcess(float delta_time) {
	// 無敵処理
	if (invincible_flag_) {
		invincible_time_ += delta_time;

		if (invincible_time_ > INVINCIBLE_TIME_MAX) {
			invincible_flag_ = false;
			invincible_time_ = 0;
		}
	}

	// ダメージが入った時のエフェクト処理
	if (damage_effect_flag_) {
		damage_effect_time_count += delta_time;

		if (damage_effect_time_count > DAMAGE_EFFECT_TIME)
		{
			if (damage_effect_count % 2 == 0)
			{
				SetDrawBright(255, 192, 192);
			}
			else
			{
				SetDrawBright(255, 255, 255);
			}

			damage_effect_count++;
			damage_effect_time_count = 0;

			if (damage_effect_count >= DAMAGE_EFFECT_MAX_COUNT)
			{
				damage_effect_flag_ = false;
				damage_effect_count = 0;
				SetDrawBright(255, 255, 255);
			}
		}
	}
}

void PLAYER::draw()
{
	
	if (hand_type_ == HAND_TYPE_STONE) {
		DrawRotaGraph(pos_.x, pos_.y, PLAYER_HAND_TYPE_GPC_SIZE, 0, player_type_stone_gpc_hdl_, true);
	}
	else if (hand_type_ == HAND_TYPE_SCISSORS) {
		DrawRotaGraph(pos_.x, pos_.y, PLAYER_HAND_TYPE_GPC_SIZE, 0, player_type_scissors_gpc_hdl_, true);
	}
	else {
		DrawRotaGraph(pos_.x, pos_.y, PLAYER_HAND_TYPE_GPC_SIZE, 0, player_type_paper_gpc_hdl_, true);
	}

	// 弾の画像生成
	for (int i = 0; i < PLAYER_BULLET_NUM; i++) {
		if (bullet[i].flag) {
			if (bullet[i].hand_type == HAND_TYPE_STONE) {
				DrawGraph(bullet[i].pos.x - (float)(bullet[i].width / 2), bullet[i].pos.y - (float)(height_ / 2 + (bullet[i].height / 2)), bullet[i].bullet_type_stone_hdl, true);
			}
			else if (bullet[i].hand_type == HAND_TYPE_SCISSORS) {
				DrawGraph(bullet[i].pos.x - (float)(bullet[i].width / 2), bullet[i].pos.y - (float)(height_ / 2 + (bullet[i].height / 2)), bullet[i].bullet_type_scissors_hdl, true);
			}
			else {
				DrawGraph(bullet[i].pos.x - (float)(bullet[i].width / 2), bullet[i].pos.y - (float)(height_ / 2 + (bullet[i].height / 2)), bullet[i].bullet_type_paper_hdl, true);
			}
		}
	}
}