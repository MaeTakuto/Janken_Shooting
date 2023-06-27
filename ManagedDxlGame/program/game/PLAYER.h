#pragma once

// �v���C���[�̒e�̐錾
struct P_BULLET {
	tnl::Vector3 pos;
	int bullet_type_stone_hdl;
	int bullet_type_scissors_hdl;
	int bullet_type_paper_hdl;
	bool flag;
	// int bullet_gpc_hdl;
	int width, height; // �摜�̕��ƍ���

	int hand_type;
};

const int MAX_LIFE = 5;						// �v���C���[���C�t
const int PLAYER_BULLET_NUM = 7;			// �v���C���[�̒e�̔��ː�
const int PLAYER_SPEED = 10;				// �v���C���[�̈ړ����x
const int PSHOT_SPEED = 10;					// �v���C���[�̒e�̔��ˑ��x
const int PLAYER_HAND_TYPE_GPC_SIZE = 1;	// �v���C���[�̃n���h�摜�̃T�C�Y
const float DAMAGE_EFFECT_TIME = 0.05f;		// 
const int DAMAGE_EFFECT_MAX_COUNT = 6;		//
const float INVINCIBLE_TIME_MAX = 1.0f;		//

// �v���C���[�̃N���X
class PLAYER {
public:
	int life_;								// �v���C���[���C�t
	int mouseX;								// �}�E�X��x���W�擾

	int player_type_stone_gpc_hdl_;			// �v���C���[�摜�i�O�[�j
	int player_type_scissors_gpc_hdl_;		// �v���C���[�摜�i�`���L�j
	int player_type_paper_gpc_hdl_;			// �v���C���[�摜�i�p�[�j
	int width_;
	int height_;

	tnl::Vector3 pos_;						// �v���C���[�̈ʒu
	bool life_flag_;						// �v���C���[�̐�������
	int hand_type_;							// �n���h�^�C�v�p

	bool damage_effect_flag_;				// �_���[�W�G�t�F�N�g�̔���
	int damage_effect_count;
	float damage_effect_time_count;

	bool invincible_flag_;					// ���G�t���O
	float invincible_time_;					// ���G���Ԃ̃J�E���g

	int bullet_count_;						// �e�̔��ˊԊu�𒲐��p
	P_BULLET bullet[PLAYER_BULLET_NUM];		// �v���C���[�̒e

	int hand_change_snd_se_hdl;				// �n���h�^�C�v��ς����Ƃ��̌��ʉ�
	int dmg_snd_se_hdl;						// �_���[�W�����������̌��ʉ�

	void init();
	void scenePlayInit();							// �v���C��ʂ̏�����

	int getLife();									// �v���C���[���C�t�擾
	bool getLifeFlag();								// ���C�t�t���O�擾�i��������j

	void move();								    // �v���C���[�̈ړ�����
	void shot();								    // �v���C���[�̒e�̔��ˑ���
	void setBulletFlag(int bullet_num, bool flag);  // �e�̕\���t���O��؂�ւ���
	void damageLife();								// �v���C���[�̃��C�t�����炷
	void damageProcess(float delta_time);			// �_���[�W�G�t�F�N�g
	void draw();									// �v���C���[�֘A�̉摜����
};
