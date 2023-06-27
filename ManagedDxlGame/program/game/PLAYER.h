#pragma once

// プレイヤーの弾の宣言
struct P_BULLET {
	tnl::Vector3 pos;
	int bullet_type_stone_hdl;
	int bullet_type_scissors_hdl;
	int bullet_type_paper_hdl;
	bool flag;
	// int bullet_gpc_hdl;
	int width, height; // 画像の幅と高さ

	int hand_type;
};

const int MAX_LIFE = 5;						// プレイヤーライフ
const int PLAYER_BULLET_NUM = 7;			// プレイヤーの弾の発射数
const int PLAYER_SPEED = 10;				// プレイヤーの移動速度
const int PSHOT_SPEED = 10;					// プレイヤーの弾の発射速度
const int PLAYER_HAND_TYPE_GPC_SIZE = 1;	// プレイヤーのハンド画像のサイズ
const float DAMAGE_EFFECT_TIME = 0.05f;		// 
const int DAMAGE_EFFECT_MAX_COUNT = 6;		//
const float INVINCIBLE_TIME_MAX = 1.0f;		//

// プレイヤーのクラス
class PLAYER {
public:
	int life_;								// プレイヤーライフ
	int mouseX;								// マウスのx座標取得

	int player_type_stone_gpc_hdl_;			// プレイヤー画像（グー）
	int player_type_scissors_gpc_hdl_;		// プレイヤー画像（チョキ）
	int player_type_paper_gpc_hdl_;			// プレイヤー画像（パー）
	int width_;
	int height_;

	tnl::Vector3 pos_;						// プレイヤーの位置
	bool life_flag_;						// プレイヤーの生存判定
	int hand_type_;							// ハンドタイプ用

	bool damage_effect_flag_;				// ダメージエフェクトの判定
	int damage_effect_count;
	float damage_effect_time_count;

	bool invincible_flag_;					// 無敵フラグ
	float invincible_time_;					// 無敵時間のカウント

	int bullet_count_;						// 弾の発射間隔を調整用
	P_BULLET bullet[PLAYER_BULLET_NUM];		// プレイヤーの弾

	int hand_change_snd_se_hdl;				// ハンドタイプを変えたときの効果音
	int dmg_snd_se_hdl;						// ダメージが入った時の効果音

	void init();
	void scenePlayInit();							// プレイ画面の初期化

	int getLife();									// プレイヤーライフ取得
	bool getLifeFlag();								// ライフフラグ取得（生存判定）

	void move();								    // プレイヤーの移動操作
	void shot();								    // プレイヤーの弾の発射操作
	void setBulletFlag(int bullet_num, bool flag);  // 弾の表示フラグを切り替える
	void damageLife();								// プレイヤーのライフを減らす
	void damageProcess(float delta_time);			// ダメージエフェクト
	void draw();									// プレイヤー関連の画像生成
};
