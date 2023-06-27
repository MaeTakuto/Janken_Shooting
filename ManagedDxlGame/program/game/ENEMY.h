#pragma once

const int ENEMY_MAX_LIFE = 3;
const int ENEMY_BOMB_FRAME_SIZE = 10;
const float ENEMY_SPEED = 3.0f;
const float ENEMY_TYPE2_SPEED = 3.0f;

const int ENEMY_BULLET_NUM = 3;
const int ESHOT_SPEED = 5;

const float ENEMY_HAND_TYPE_GPC_SIZE = 1; //0.5f
const float ENEMY_SPAWN_POS_Y = -50.0f;

const int pos[7] = {100, 200, 300, 400, 500, 600, 700};

struct E_BULLET {
	tnl::Vector3 pos;
	int gpc_hdl;
	int width;
	int height;
	int flag;

	float dx;
	float dy;
	float angle;
};

class ENEMY {
public:
	int life_;								// 敵のライフ
	tnl::Vector3 pos_;
	int enemy_type_stone_gpc_hdl_;			// エネミー画像（グー）
	int enemy_type_scissors_gpc_hdl_;    // エネミー画像（チョキ）
	int enemy_type_paper_gpc_hdl_;       // エネミー画像（パー）
	int width_;
	int height_;
	bool spawn_flag_;					 // 
	bool attack_flag_;

	E_BULLET bullet_[ENEMY_BULLET_NUM];
	int bullet_count_; // 弾の発射間隔を調整用

	int hand_type_;
	int score_;

	int bomb_anim_hdls_[ENEMY_BOMB_FRAME_SIZE];				// 爆発エフェクト
	int anim_frame_;
	bool bomb_anim_flag_;
	float anim_time_count_;

	int expl_snd_se_hdl;									// 爆発エフェクト効果音
	int shot_snd_se_hdl;									// 弾発射の効果音

	void init(int life, int score);
	void scenePlayInit();									// プレイ画面の初期化
	bool getSpawnFlag();									// 敵が生成されているかの確認
	int getScore();											// スコアを取得
	int getWidth();											// 画像の幅取得
	float getPositionX();									// x座標取得
	void spawnEnemy(float spawn_pos_x);						// 敵の生成
	void move();											// 敵タイプ1の行動 
	void moveType2();										// 敵タイプ2の行動
	void shot(float target_x, float target_y);				// 弾の処理
	void damageLife();										// ライフを減らす、死亡判定
	void deleteEnemy();										// 敵を消す
	void bombAnim(float delta_time);						// 爆発のアニメーション処理
	void draw();								// 敵の画像表示
};
