//=============================================================================
//
// �v���C���[���� [player.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

// �}�N����`
#define NUM_PLAYER						(2)		// �|���S����
#define TEXTURE_GAME_PLAYER00		_T("data/TEXTURE/motion.png")	// �v���C���[00�p�摜
#define TEXTURE_PLAYER00_SIZE_X			(200 * SCREEN_SCALING / 2)	// �e�N�X�`���T�C�Y
#define TEXTURE_PLAYER00_SIZE_Y			(150 * SCREEN_SCALING / 2)	// ����
#define TEXTURE_PATTERN_DIVIDE_X_PLAYER	(10)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_PLAYER	(6)		// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define TEXTURE_PATTERN_PLAYER			(3)		// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_PLAYER			(TEXTURE_PATTERN_DIVIDE_X_PLAYER*TEXTURE_PATTERN_DIVIDE_Y_PLAYER)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_PLAYER			(7)		// �A�j���[�V�����̐؂�ւ��J�E���g

// �v���C���[�̏������W
#define PLAYER_POS_X			(200 * SCREEN_SCALING)		// �����ʒuX
#define PLAYER_POS_Y			(670 * SCREEN_SCALING)		// �����ʒuY

// �����蔻��p�T�C�Y
#define PLAYER_CUSTOM_SIZE_X			(10)
#define PLAYER_CUSTOM_SIZE_Y			(50)

#define PLAYER_TUTORIAL_MOVE_X			(450 * SCREEN_SCALING)	// �`���[�g���A�����̈ړ�����

#define PLAYER_MAX						(1)		// �v���C���[�̍ő吔
#define PLAYER_HPMAX					(20)	// �v���C���[�̍ő�HP
#define PLAYER_MANAMAX					(1000)	// �v���C���[�̍ő�MP
#define PLAYER_MANARECOVERY				(3)		// �v���C���[��MP�񕜑��x
#define PLAYER_GROUND					(5)		// �v���C���[�̍ő吔

#define PLAYER_SPEED					(8 * SCREEN_SCALING)		// �v���C���[�̈ړ����x
#define PLAYER_MOVE_NORMAL				(1.0f)	// �v���C���[�̒ʏ�ړ��{��
#define PLAYER_MOVE_SLANT				(0.71f)	// �v���C���[�̎΂߈ړ��{��

#define PLAYER_SLOW						(3 * SCREEN_SCALING)		// �v���C���[�̖��d�͎��̑��x
#define PLAYER_JUMP_POWER				(20 * SCREEN_SCALING)	// �v���C���[�̃W�����v��
#define PLAYER_JUMP_MAX					(2)		// �v���C���[�̘A���W�����v��
#define PLAYER_GRAVITI					(0.7 * SCREEN_SCALING)	// �v���C���[�̏d��
#define PLAYER_GRAVITI_ALERT			(250)	// �c��MP���ݒ�l�������ƃA���[�g

#define PLAYER_ALPHA_MAX				(255)	// �v���C���[�̍ő�A���t�@�l
#define PLAYER_INVISIBLE_MAX			(50)	// �v���C���[���G����
#define PLAYER_INVISIBLE_FREQUENCY		(5)		// �v���C���[���G���̓_�ő��x

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// �ړ���
	D3DXVECTOR3				rot;					// ��]��
	D3DXVECTOR2				size;					// �e�N�X�`���T�C�Y(x,y)
	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	int						nDirection;				// ����
	int						nAlphaCount;			// �A���t�@�l�̃J�E���g
	int						nInvisibleCount;		// ���G�J�E���g
	int						nJumpFlag;				// �W�����v�t���O

	float					fHitPoint;				// HP
	float					fManaPoint;				// MP
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	float					fGravity;				// �d��
	float					fAcceleration;			// �W�����v�����x
	float					fMoveSlow;				// �ړ�����
	float					fMove;					// �ړ����x

	bool					bUse;					// �v���C���[�t���O
	bool					bGravityFlag;			// �d�̓t���O
	bool					bParameterUse;			// �p�����[�^�t���O
	bool					bAlphaFlag;				// �����x�t���O
	bool					bInvisibleFlag;			// ���G�t���O
}PLAYER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SetPlayerVoice(int nVoice);
PLAYER *GetPlayer(int no);


#endif
