//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "enemybullet.h"

// �}�N����`
#define NUM_ENEMY		(2)	// �|���S����

#define TEXTURE_GAME_ENEMY00	_T("data/TEXTURE/enemy.png")	// �G�l�~�[00�p�摜
#define TEXTURE_ENEMY00_SIZE_X			(80 * SCREEN_SCALING/2)	// �e�N�X�`���T�C�Y
#define TEXTURE_ENEMY00_SIZE_Y			(80 * SCREEN_SCALING/2)	// ����
	
#define TEXTURE_CHANGE_ENEMY_X			(1.0f)	// �e�N�X�`���T�C�Y�ύX�{��
#define TEXTURE_CHANGE_ENEMY_Y			(1.0f)	// ����
#define TEXTURE_CHANGE_BOSS_ENEMY_X		(1.5f)	// �e�N�X�`���T�C�Y�ύX�{��
#define TEXTURE_CHANGE_BOSS_ENEMY_Y		(1.5f)	// ����

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY	(3)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY	(10)		// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_ENEMY			(TEXTURE_PATTERN_DIVIDE_X_ENEMY*TEXTURE_PATTERN_DIVIDE_Y_ENEMY)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_ENEMY			(15)		// �A�j���[�V�����̐؂�ւ��J�E���g

#define ENEMY_POP_TYPE_MAX				(9)		// �G�l�~�[�^�C�v�̍ő吔

#define ENEMY_POP_POS_X					(SCREEN_HEIGHT/ENEMY_POP_TYPE_MAX)	// �G�l�~�[�^�C�v�̍ő吔

// �G�l�~�[�X�e�[�^�X
#define ENEMY_MAX						(100)	// �ő吔

#define ENEMY_COOLDOWN					(100)	// �G�l�~�[�Ďg�p�N�[���_�E��
#define ENEMY_MOVE_SPEED				(4 * SCREEN_SCALING)		// �G�l�~�[�̈ړ��X�s�[�h
#define ENEMY_ROTATION					(0.0f)	// �G�l�~�[�o���b�g�̉�]��
#define ENEMY_ACTION					(100)	// �A�N�V�����Ԋu

#define ENEMY_HPMAX						(70)	// �ő�HP
#define STRONG_ENEMY_HPMAX				(120)	// �ő�HP�i���G�j
#define BOSS_ENEMY_HPMAX				(8000)	// �ő�HP�i�{�X�j


// �V���b�g�J�E���g
#define ENEMY_SHOT00					(20)
#define ENEMY_SHOT01					(60)
#define ENEMY_SHOT02					(60)
#define ENEMY_SHOT03					(60)
#define ENEMY_SHOT04					(60)
#define ENEMY_SHOT05					(20)
#define ENEMY_SHOT06					(60)

// �V���b�g�Ԋu
#define ENEMY_SHOT_ACTION00				(4)
#define ENEMY_SHOT_ACTION05				(4)
#define ENEMY_SHOT_ACTION06				(6)

// �G�l�~�[�̏o���^�C�v
#define ENEMY_POP_TYPE00				(0)
#define ENEMY_POP_TYPE01				(1)
#define ENEMY_POP_TYPE02				(2)
#define ENEMY_POP_TYPE03				(3)
#define ENEMY_POP_TYPE04				(4)
#define ENEMY_POP_TYPE05				(5)

// �G�l�~�[�̈ړ��^�C�v
#define ENEMY_MOVE_TYPE00				(0)
#define ENEMY_MOVE_TYPE01				(1)
#define ENEMY_MOVE_TYPE02				(2)
#define ENEMY_MOVE_TYPE03				(3)
#define ENEMY_MOVE_TYPE04				(4)
#define ENEMY_MOVE_TYPE05				(5)

// �t�@�C���ǂݍ���
#define		FILE_ENEMY_EASY		"data/CSV/enemy_easy.csv"
#define		FILE_ENEMY_NORMAL	"data/CSV/enemy_normal.csv"
#define		FILE_ENEMY_HARD		"data/CSV/enemy_hard.csv"
#define		FILE_DATA_MAX		(12)

enum
{
	ENEMY_NORMAL,
	ENEMY_STRONG,
	ENEMY_BOSS
};

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// �G�l�~�[�̈ړ���
	D3DXVECTOR3				rot;					// �G�l�~�[�̉�]��
	D3DXVECTOR3				vecOldPos;				// �G�l�~�[�̋����W
	D3DXVECTOR3				vecDestination;			// �G�l�~�[�̈ړ���
	D3DXVECTOR3				vecTargetPos;			// �G�l�~�[�̃^�[�Q�b�g���W
	D3DXVECTOR3				vecTa;					// ����
	D3DXVECTOR3				vecMove;				// �ړ���
	D3DXVECTOR2				vecChangeSize;			// �G�l�~�[�̃e�N�X�`���T�C�Y�ύX(x,y)
	D3DXVECTOR2				size;					// �G�l�~�[�̃e�N�X�`���T�C�Y(x,y)

	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	int						nType;					// �K�p�e�N�X�`���^�C�v
	int						nPopType;				// �o���^�C�v
	int						nMoveType;				// �ړ��^�C�v
	int						nBulletType;			// �o���b�g�^�C�v
	int						nBulletShiftAngle;		// �o���b�g�p�x�ύX
	int						nBulletPattern;			// �o���b�g�p�^�[��

	int						nBulletTexture[ENEMYBULLET_TYPE_MAX];		// �o���b�g�̃e�N�X�`���[
	int						nBulletCount[ENEMYBULLET_TYPE_MAX];			// �o���b�g�̔��ː��J�E���g
	int						nBulletSpeed[ENEMYBULLET_TYPE_MAX];			// �o���b�g�̈ړ����x
	int						nBulletSetTime[ENEMYBULLET_TYPE_MAX];		// �o���b�g�̔��ˎ��ԃZ�b�g
	int						nBulletTime[ENEMYBULLET_TYPE_MAX];			// �o���b�g�̔��ˎ���
	int						nBulletAction[ENEMYBULLET_TYPE_MAX];		// �o���b�g�̘A�ˑ��x
	int						nBulletSplit[ENEMYBULLET_TYPE_MAX];			// �o���b�g�̎ˊp����
	int						nBulletSpeedChange[ENEMYBULLET_TYPE_MAX];	// �o���b�g�̈ړ����x�ύX
	float					nBulletOption[ENEMYBULLET_TYPE_MAX];		// �o���b�g�̃I�v�V����(WAY���Ȃ�)

	int						nShotTime;				// �V���b�g�^�C��
	int						nMoveCount;				// �ړ��J�E���g
	int						nMoveFlag;				// �ړ��t���O
	int						nStopFlag;				// ��~�t���O
	int						nActionCount;			// �A�N�V�����J�E���g
	int						nActionFlag;			// �A�N�V�����t���O
	int						nCoolDown;				// �Ďg�p�N�[���_�E��
	int						nSpec;					// �G�l�~�[�̐��\
	int						nPopCount;				// �G�l�~�[�̏o���J�E���g

	float					fHitPoint;				// �G�l�~�[��HP
	float					fBaseAngle;				// ��]�p�p�x�i�Ɓj
	float					fRadius;				// ��]�p���a

	bool					bUse;					// true:�g�p  false:���g�p
	bool					bCalculation;			// �v�Z�t���O
	bool					bParameterUse;			// �p�����[�^�t���O
	bool					bBossReversal;			// �{�X�o���b�g�t�]�t���O
	bool					bBulletStandby[ENEMYBULLET_TYPE_MAX];			// �V���b�g��������
	bool					bBulletFlag[ENEMYBULLET_TYPE_MAX];			// �o���b�g�t���O

	float					fAngle;					// �o���b�g01�̊p�x
}ENEMY;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemy(int type);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void InitStatusEnemy(int nEnemy);
void SetEnemyLevel(int nLevel);
void SetEnemy(int nType, int nPopType, int nMoveType, int nBulletType, int nBulletTexture, int nBulletSpeed, int nBulletSetTime, int nBulletAction, int nBulletSplit, int nBulletSpeedChange, float nBulletOption);
void SetBossEnemy(int nType, int nPopType, int nMoveType, int nBulletType, int nBulletTexture, int nBulletSpeed, int nBulletSetTime, int nBulletAction, int nBulletSplit, int nBulletSpeedChange, float nBulletOption);
ENEMY *GetEnemy(int no);

#endif
