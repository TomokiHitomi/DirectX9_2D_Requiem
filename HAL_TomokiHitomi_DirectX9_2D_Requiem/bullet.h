//=============================================================================
//
// �o���b�g01���� [bullet.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include <time.h>

// �}�N����`
#define NUM_BULLET						(2)					// �|���S����

#define TEXTURE_GAME_BULLET	_T("data/TEXTURE/notes.png")	// �o���b�g�p�摜

#define TEXTURE_BULLET_SIZE_X			(27 * SCREEN_SCALING / 2)				// ���e�N�X�`���T�C�Y
#define TEXTURE_BULLET_SIZE_Y			(27 * SCREEN_SCALING / 2)				// �c�e�N�X�`���T�C�Y

#define TEXTURE_PATTERN_DIVIDE_X_BULLET	(4)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BULLET	(5)			// �A�j���p�^�[���̃e�N�X�`�����������iY)

// �A�j���[�V�����p�^�[����
#define ANIM_PATTERN_NU_BULLET			(TEXTURE_PATTERN_DIVIDE_X_BULLET * TEXTURE_PATTERN_DIVIDE_Y_BULLET)
#define TIME_ANIMATION_BULLET			(4)					// �A�j���[�V�����̐؂�ւ��J�E���g

#define BULLET_MAX						(255)				// �o���b�g01�̍ő吔

#define BULLET01_ROTATION				(0.05f)				// �o���b�g01�̉�]��
#define BULLET01_COOLDOWN				(5)					// �o���b�g01�A�ˑ��x�i���l���傫���ƒx���j

#define BULLET_ALPHA					(200)				// �o���b�g�̓����x

// �o���b�g�̈ړ����x
#define BULLET00_SPEED_MAX				(20 * SCREEN_SCALING)	// �o���b�g00�̍ő呬�x
#define BULLET01_SPEED_MAX				(20 * SCREEN_SCALING)	// �o���b�g01�̍ő呬�x
#define BULLET02_SPEED_MAX				(50 * SCREEN_SCALING)	// �o���b�g02�̍ő呬�x
#define BULLET03_SPEED_MAX				(20 * SCREEN_SCALING)	// �o���b�g03�̍ő呬�x

#define BULLET02_SPEED_ACCELERATOR		(0.2 * SCREEN_SCALING)	// �o���b�g02�̉����x

// �o���b�g�̘A�ˑ��x
#define BULLET00_RELOAD_SPEED			(8)		// �o���b�g00
#define BULLET01_RELOAD_SPEED			(4)		// �o���b�g01
#define BULLET02_RELOAD_SPEED			(4)		// �o���b�g02
#define BULLET03_RELOAD_SPEED			(4)		// �o���b�g03

// �o���b�g�̃Z�b�g���W����
#define BULLET_ADJUSTMENT_X				(20 * SCREEN_SCALING)
#define BULLET_ADJUSTMENT_Y				(-45 * SCREEN_SCALING)

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// �o���b�g01�̍��W
	D3DXVECTOR3				rot;					// �o���b�g01�̉�]��
	D3DXVECTOR2				size;					// �o���b�g01�̃e�N�X�`���T�C�Y(x,y)
	D3DXVECTOR3				vecTa;					// ����
	D3DXVECTOR2				move;					// �ړ���
	D3DXVECTOR3				vecDestination;			// �o���b�g�̈ړ���

	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	int						nBulletType;			// �o���b�g�̃^�C�v
	int						nBulletCount;			// �o���b�g�J�E���g
	int						nAngleType;				// �o���b�g�̊p�x�^�C�v
	int						nPatternHoming;			// �z�[�~���O�p�^�[���i���o�[
	int						nHomingFlag;			// �o���b�g�̃z�[�~���O�t���O
	int						nDirection;				// �o���b�g�̌���
	int						nTarget;				// �o���b�g�̃^�[�Q�b�g

	float					fBulletSpeed;			// �o���b�g�̈ړ����x
	float					fAngle;					// �o���b�g�̊p�x
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a

	bool					bUse;					// �o���b�g�̎g�p�t���O
	bool					bTextureUse;			// �o���b�g�̃e�N�X�`���t���O

}BULLET;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBullet(int type);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
BULLET *GetBullet(int no);
void SetBullet(D3DXVECTOR3 pos, int nBulletType);
void InitStatusBullet(int nBullet);

#endif
