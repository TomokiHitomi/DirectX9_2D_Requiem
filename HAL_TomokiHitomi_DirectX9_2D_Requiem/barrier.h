//=============================================================================
//
// �t�@���l������ [funnel.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _BARRIER_H_
#define _BARRIER_H_

#include "main.h"
#include <time.h>

// �}�N����`
#define NUM_BARRIER						(2)					// �|���S����

#define TEXTURE_GAME_BARRIER	_T("data/TEXTURE/barrier.png")	// �t�@���l���p�摜

#define TEXTURE_BARRIER_SIZE_X			(100 * SCREEN_SCALING/2)				// ���e�N�X�`���T�C�Y
#define TEXTURE_BARRIER_SIZE_Y			(100 * SCREEN_SCALING/2)				// �c�e�N�X�`���T�C�Y

// �����蔻��p�T�C�Y
#define BARRIER_CUSTOM_SIZE_X	(70 * SCREEN_SCALING/2)
#define BARRIER_CUSTOM_SIZE_Y	(70 * SCREEN_SCALING/2)

#define TEXTURE_PATTERN_DIVIDE_X_BARRIER	(5)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BARRIER	(6)			// �A�j���p�^�[���̃e�N�X�`�����������iY)

// �A�j���[�V�����p�^�[����
#define ANIM_PATTERN_NU_BARRIER			(TEXTURE_PATTERN_DIVIDE_X_BARRIER*TEXTURE_PATTERN_DIVIDE_Y_BARRIER)
#define TIME_ANIMATION_BARRIER			(4)					// �A�j���[�V�����̐؂�ւ��J�E���g

#define BARRIER_MAX						(3)				// �t�@���l���̍ő吔
#define BARRIER_TYPE_MAX					(2)				// �t�@���l���̃^�C�v�ő吔

#define BARRIER_ALPHA_MAX				(255)			// �t�@���l���̍ő僿�l
#define BARRIER_ALPHA					(100)			// �t�@���l���̍ŏ����l
#define BARRIER_ALPHA_MIN				(BARRIER_ALPHA_MAX - BARRIER_ALPHA)			// �t�@���l���̃��l

#define BARRIER01_ROTATION				(0.05f)				// �t�@���l���̉�]��
#define BARRIER01_COOLDOWN				(5)					// �t�@���l���A�ˑ��x�i���l���傫���ƒx���j

// �t�@���l���̈ړ����x
#define BARRIER00_SPEED_MAX				(20)	// �t�@���l��00�̍ő呬�x
#define BARRIER01_SPEED_MAX				(5)	// �t�@���l��01�̍ő呬�x
#define BARRIER02_SPEED_MAX				(50)	// �t�@���l��02�̍ő呬�x

#define BARRIER02_SPEED_ACCELERATOR		(0.2)	// �t�@���l��02�̉����x

// �t�@���l���̘A�ˑ��x
#define BARRIER00_RELOAD_SPEED			(10)	// �t�@���l��00
#define BARRIER01_RELOAD_SPEED			(5)		// �t�@���l��01
#define BARRIER02_RELOAD_SPEED			(5)		// �t�@���l��02

// �t�@���l���o���b�g�̘A�ˑ��x
#define BARRIER_BULLET_RELOAD_SPEED		(4)

#define BARRIER_DISTANCE_MAX				(80 * SCREEN_SCALING)	// �t�@���l���Ɛݒu�Ώۂ̋���
#define BARRIER_INJECTION_SPEED			(2.0f)	// �t�@���l���̎ˏo���x
#define BARRIER_ROTATIONAL_SPEED			(40)	// �t�@���l���̉�]���x

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// �t�@���l��01�̍��W
	D3DXVECTOR3				rot;					// �t�@���l��01�̉�]��
	D3DXVECTOR2				size;					// �t�@���l��01�̃e�N�X�`���T�C�Y(x,y)
	D3DXVECTOR3				vecTa;					// ����
	D3DXVECTOR2				move;					// �ړ���
	D3DXVECTOR3				vecDestination;			// �t�@���l���̈ړ���

	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	int						nBarrierType;			// �t�@���l���̃^�C�v
	int						nBarrierCount;			// �t�@���l���J�E���g
	int						nAngleType;				// �t�@���l���̊p�x�^�C�v
	int						nPatternHoming;			// �z�[�~���O�p�^�[���i���o�[
	int						nHomingFlag;			// �t�@���l���̃z�[�~���O�t���O
	int						nDirection;				// �t�@���l���̌���
	int						nTarget;				// �t�@���l���̃^�[�Q�b�g
	int						nReloadBullet;			// �t�@���l���o���b�g�̃����[�h�J�E���g
	int						nAlpha;					// �t�@���l���̃��l

	float					fBarrierSpeed;			// �t�@���l���̈ړ����x
	float					fAngle;					// �t�@���l���̊p�x
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	float					fDistance;				// �v���C���[�ƃt�@���l���̋���

	bool					bUse;					// �t�@���l���̎g�p�t���O
	bool					bTextureUse;			// �t�@���l���̃e�N�X�`���t���O
	bool					bReload;				// �t�@���l���o���b�g�̃����[�h�t���O

}BARRIER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBarrier(int type);
void UninitBarrier(void);
void UpdateBarrier(void);
void DrawBarrier(void);
BARRIER *GetBarrier(int no);
void SetBarrier(D3DXVECTOR3 pos);
void ReleaseBarrier(void);
void InitStatusBarrier(int nBarrier);

#endif
