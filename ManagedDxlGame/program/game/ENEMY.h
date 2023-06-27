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
	int life_;								// �G�̃��C�t
	tnl::Vector3 pos_;
	int enemy_type_stone_gpc_hdl_;			// �G�l�~�[�摜�i�O�[�j
	int enemy_type_scissors_gpc_hdl_;    // �G�l�~�[�摜�i�`���L�j
	int enemy_type_paper_gpc_hdl_;       // �G�l�~�[�摜�i�p�[�j
	int width_;
	int height_;
	bool spawn_flag_;					 // 
	bool attack_flag_;

	E_BULLET bullet_[ENEMY_BULLET_NUM];
	int bullet_count_; // �e�̔��ˊԊu�𒲐��p

	int hand_type_;
	int score_;

	int bomb_anim_hdls_[ENEMY_BOMB_FRAME_SIZE];				// �����G�t�F�N�g
	int anim_frame_;
	bool bomb_anim_flag_;
	float anim_time_count_;

	int expl_snd_se_hdl;									// �����G�t�F�N�g���ʉ�
	int shot_snd_se_hdl;									// �e���˂̌��ʉ�

	void init(int life, int score);
	void scenePlayInit();									// �v���C��ʂ̏�����
	bool getSpawnFlag();									// �G����������Ă��邩�̊m�F
	int getScore();											// �X�R�A���擾
	int getWidth();											// �摜�̕��擾
	float getPositionX();									// x���W�擾
	void spawnEnemy(float spawn_pos_x);						// �G�̐���
	void move();											// �G�^�C�v1�̍s�� 
	void moveType2();										// �G�^�C�v2�̍s��
	void shot(float target_x, float target_y);				// �e�̏���
	void damageLife();										// ���C�t�����炷�A���S����
	void deleteEnemy();										// �G������
	void bombAnim(float delta_time);						// �����̃A�j���[�V��������
	void draw();								// �G�̉摜�\��
};
