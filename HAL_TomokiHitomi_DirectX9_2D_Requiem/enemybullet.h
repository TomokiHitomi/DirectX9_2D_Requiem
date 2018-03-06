//=============================================================================
//
// �G�l�~�[�o���b�g00���� [enemybullet.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

#include "main.h"
#include <time.h>

// �}�N����`
#define NUM_ENEMYBULLET						(2)					// �|���S����

#define TEXTURE_GAME_ENEMYBULLET	_T("data/TEXTURE/enemybullet.png")	// �G�l�~�[�o���b�g0000�p�摜
#define TEXTURE_ENEMYBULLET_SIZE_X			(27 * SCREEN_SCALING/2)				// ���e�N�X�`���T�C�Y
#define TEXTURE_ENEMYBULLET_SIZE_Y			(27 * SCREEN_SCALING/2)				// �c�e�N�X�`���T�C�Y

// �����蔻��p�T�C�Y �m�[�}��
#define ENEMYBULLET_CUSTOM_SIZE_NORMAL_X	(22 * SCREEN_SCALING/2)
#define ENEMYBULLET_CUSTOM_SIZE_NORMAL_Y	(22 * SCREEN_SCALING/2)

// �����蔻��p�T�C�Y �X���[��
#define ENEMYBULLET_CUSTOM_SIZE_SMALL_X		(16 * SCREEN_SCALING/2)
#define ENEMYBULLET_CUSTOM_SIZE_SMALL_Y		(16 * SCREEN_SCALING/2)

// �ݒ�l�ȍ~�̃e�N�X�`���̓X���[��
#define ENEMYBULLET_SIZE_SMALL_NUM		(18)


#define TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET	(9)			// �e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET	(3)			// �e�N�X�`�����������iY)

// �A�j���[�V�����p�^�[����
#define ANIM_PATTERN_NU_ENEMYBULLET				(TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET*TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET)

#define ENEMYBULLET_MAX				(1000)		// �G�l�~�[�o���b�g�̍ő吔
#define ENEMYBULLET_ROTATION		(0.0f)		// �G�l�~�[�o���b�g�̉�]��

#define ENEMYBULLET_TYPE_MAX		(9)


// �G�l�~�[�o���b�g360�x����
#define ENEMYBULLET_SPLIT01			(20)
#define ENEMYBULLET_SPLIT02			(20)
#define ENEMYBULLET_SPLIT03			(20)
#define ENEMYBULLET_SPLIT04			(20)
#define ENEMYBULLET_SPLIT05			(20)
#define ENEMYBULLET_SPLIT06			(11)

// �G�l�~�[�o���b�g360�x���炵
#define ENEMYBULLET_SHIFT03			(0.05f)
#define ENEMYBULLET_SHIFT04			(0.05f)
#define ENEMYBULLET_SHIFT06			(0.01f)

// �G�l�~�[�o���b�g���x
#define ENEMYBULLET_SPEED_MAX00		(7)
#define ENEMYBULLET_SPEED_MAX01		(5)
#define ENEMYBULLET_SPEED_MAX02		(5)
#define ENEMYBULLET_SPEED_MAX03		(5)
#define ENEMYBULLET_SPEED_MAX04		(5)
#define ENEMYBULLET_SPEED_MAX05		(5)
#define ENEMYBULLET_SPEED_MAX06		(2)

// �G�l�~�[�o���b�g�̑��x�ύX
#define ENEMYBULLET_SPEEDCHANGE_TIME	(20)
#define ENEMYBULLET_SPEED_CHENGE_DEFAULT		(1.0f)
#define ENEMYBULLET_SPEED_CHANGE				(0.02f * SCREEN_SCALING)
#define ENEMYBULLET_SPEED_CHANGE_MAX			(1.5f)
#define ENEMYBULLET_SPEED_CHANGE_MIN			(-1.5f)

#define ENEMYBULLET_WAY00			(0)			// �G�l�~�[�o���b�gWAY�Ȃ�
#define ENEMYBULLET_WAY01			(1)			// �G�l�~�[�o���b�gWAY01
#define ENEMYBULLET_WAY03			(3)			// �G�l�~�[�o���b�gWAY03
#define ENEMYBULLET_WAY05			(5)			// �G�l�~�[�o���b�gWAY05
#define ENEMYBULLET_WAY07			(7)			// �G�l�~�[�o���b�gWAY07

// �G�l�~�[�o���b�g�^�C�v
#define ENEMYBULLET_TYPE00			(0)			// �G�l�~�[�o���b�g�^�C�v00
#define ENEMYBULLET_TYPE01			(1)			// �G�l�~�[�o���b�g�^�C�v01
#define ENEMYBULLET_TYPE02			(2)			// �G�l�~�[�o���b�g�^�C�v02
#define ENEMYBULLET_TYPE03			(3)			// �G�l�~�[�o���b�g�^�C�v03
#define ENEMYBULLET_TYPE04			(4)			// �G�l�~�[�o���b�g�^�C�v04
#define ENEMYBULLET_TYPE05			(5)			// �G�l�~�[�o���b�g�^�C�v05
#define ENEMYBULLET_TYPE06			(6)			// �G�l�~�[�o���b�g�^�C�v06

// �G�l�~�[�o���b�g�e�N�X�`���[
#define ENEMYBULLET_TEXTURE00		(0)			// �G�l�~�[�o���b�g�e�N�X�`���[00
#define ENEMYBULLET_TEXTURE01		(1)			// �G�l�~�[�o���b�g�e�N�X�`���[01
#define ENEMYBULLET_TEXTURE02		(2)			// �G�l�~�[�o���b�g�e�N�X�`���[02
#define ENEMYBULLET_TEXTURE03		(3)			// �G�l�~�[�o���b�g�e�N�X�`���[03
#define ENEMYBULLET_TEXTURE04		(4)			// �G�l�~�[�o���b�g�e�N�X�`���[04
#define ENEMYBULLET_TEXTURE05		(5)			// �G�l�~�[�o���b�g�e�N�X�`���[05
#define ENEMYBULLET_TEXTURE06		(6)			// �G�l�~�[�o���b�g�e�N�X�`���[06
#define ENEMYBULLET_TEXTURE07		(7)			// �G�l�~�[�o���b�g�e�N�X�`���[07
#define ENEMYBULLET_TEXTURE08		(8)			// �G�l�~�[�o���b�g�e�N�X�`���[08

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// �G�l�~�[�o���b�g00�̍��W
	D3DXVECTOR3				rot;					// �G�l�~�[�o���b�g00�̉�]��
	D3DXVECTOR2				size;					// �G�l�~�[�o���b�g00�̃e�N�X�`���T�C�Y(x,y)
	D3DXVECTOR3				vecTa;					// ����
	D3DXVECTOR3				move;					// �ړ���
	D3DXVECTOR3				vecTargetPos;			// �G�l�~�[�o���b�g�̃^�[�Q�b�g���W
	D3DXVECTOR3				vecOldEnemyPos;			// �G�l�~�[�̋����W

	D3DXVECTOR3				vecMoveChange;			// �ړ������{��

	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	int						nPatternHoming;			// �z�[�~���O�p�^�[���i���o�[
	int						nHomingFlag;			// �G�l�~�[�o���b�g00�̃z�[�~���O�t���O
	int						nDirection;				// �G�l�~�[�o���b�g00�̌���
	int						nTarget;				// �G�l�~�[�o���b�g00�̃^�[�Q�b�g
	int						nBulletType;			// �G�l�~�[�̃o���b�g�^�C�v
	int						nBulletTexture;			// �G�l�~�[�̃o���b�g�e�N�X�`���[
	int						nBulletWay;				// �G�l�~�[�̃o���b�gWAY��
	int						nBulletTime;			// �G�l�~�[�̃o���b�g�o�ߎ���
	int						nSetEnemy;				// �Z�b�g����G�l�~�[

	float					fAngle;					// �G�l�~�[�o���b�g00�̊p�x
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	float					fMoveChange;			// �ړ��������{��
	float					fDistance;				// ����

	bool					bUse;					// �G�l�~�[�o���b�g00�̎g�p�t���O
	bool					bTextureUse;			// �G�l�~�[�o���b�g00�̃e�N�X�`���t���O
	bool					bPatternHomingFlag;		// �z�[�~���O�p�^�[���t���O
}ENEMYBULLET;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEnemybullet(int type);
void UninitEnemybullet(void);
void UpdateEnemybullet(void);
void DrawEnemybullet(void);
ENEMYBULLET *GetEnemybullet(int no);
void SetEnemybullet(int nEnemy, int nBulletSplit);
void InitStatusEnemyBullet(int nBullet);
#endif
