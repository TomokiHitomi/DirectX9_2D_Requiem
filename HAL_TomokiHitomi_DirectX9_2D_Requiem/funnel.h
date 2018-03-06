//=============================================================================
//
// �t�@���l������ [funnel.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _FUNNEL_H_
#define _FUNNEL_H_

#include "main.h"
#include <time.h>

// �}�N����`
#define NUM_FUNNEL						(2)					// �|���S����

#define TEXTURE_GAME_FUNNEL	_T("data/TEXTURE/funnel.png")	// �t�@���l���p�摜

#define TEXTURE_FUNNEL_SIZE_X			(100 * SCREEN_SCALING/2)				// ���e�N�X�`���T�C�Y
#define TEXTURE_FUNNEL_SIZE_Y			(100 * SCREEN_SCALING/2)				// �c�e�N�X�`���T�C�Y

#define TEXTURE_PATTERN_DIVIDE_X_FUNNEL	(5)			// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_FUNNEL	(6)			// �A�j���p�^�[���̃e�N�X�`�����������iY)

// �A�j���[�V�����p�^�[����
#define ANIM_PATTERN_NU_FUNNEL			(TEXTURE_PATTERN_DIVIDE_X_FUNNEL*TEXTURE_PATTERN_DIVIDE_Y_FUNNEL)
#define TIME_ANIMATION_FUNNEL			(4)					// �A�j���[�V�����̐؂�ւ��J�E���g

#define FUNNEL_MAX						(3)				// �t�@���l���̍ő吔
#define FUNNEL_TYPE_MAX					(2)				// �t�@���l���̃^�C�v�ő吔

#define FUNNEL_ALPHA_MAX				(255)			// �t�@���l���̍ő僿�l
#define FUNNEL_ALPHA					(100)			// �t�@���l���̍ŏ����l
#define FUNNEL_ALPHA_MIN				(FUNNEL_ALPHA_MAX - FUNNEL_ALPHA)			// �t�@���l���̃��l

#define FUNNEL01_ROTATION				(0.05f)				// �t�@���l���̉�]��
#define FUNNEL01_COOLDOWN				(5)					// �t�@���l���A�ˑ��x�i���l���傫���ƒx���j

// �t�@���l���̈ړ����x
#define FUNNEL00_SPEED_MAX				(20)	// �t�@���l��00�̍ő呬�x
#define FUNNEL01_SPEED_MAX				(5)	// �t�@���l��01�̍ő呬�x
#define FUNNEL02_SPEED_MAX				(50)	// �t�@���l��02�̍ő呬�x

#define FUNNEL02_SPEED_ACCELERATOR		(0.2)	// �t�@���l��02�̉����x

// �t�@���l���̘A�ˑ��x
#define FUNNEL00_RELOAD_SPEED			(10)	// �t�@���l��00
#define FUNNEL01_RELOAD_SPEED			(5)		// �t�@���l��01
#define FUNNEL02_RELOAD_SPEED			(5)		// �t�@���l��02

// �t�@���l���o���b�g�̘A�ˑ��x
#define FUNNEL_BULLET_RELOAD_SPEED		(4)

#define FUNNEL_DISTANCE_MAX				(80 * SCREEN_SCALING)	// �t�@���l���Ɛݒu�Ώۂ̋���
#define FUNNEL_INJECTION_SPEED			(2.0f)	// �t�@���l���̎ˏo���x
#define FUNNEL_ROTATIONAL_SPEED			(40)	// �t�@���l���̉�]���x

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
	int						nFunnelType;			// �t�@���l���̃^�C�v
	int						nFunnelCount;			// �t�@���l���J�E���g
	int						nAngleType;				// �t�@���l���̊p�x�^�C�v
	int						nPatternHoming;			// �z�[�~���O�p�^�[���i���o�[
	int						nHomingFlag;			// �t�@���l���̃z�[�~���O�t���O
	int						nDirection;				// �t�@���l���̌���
	int						nTarget;				// �t�@���l���̃^�[�Q�b�g
	int						nReloadBullet;			// �t�@���l���o���b�g�̃����[�h�J�E���g
	int						nAlpha;					// �t�@���l���̃��l

	float					fFunnelSpeed;			// �t�@���l���̈ړ����x
	float					fAngle;					// �t�@���l���̊p�x
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	float					fDistance;				// �v���C���[�ƃt�@���l���̋���

	bool					bUse;					// �t�@���l���̎g�p�t���O
	bool					bTextureUse;			// �t�@���l���̃e�N�X�`���t���O
	bool					bReload;				// �t�@���l���o���b�g�̃����[�h�t���O

}FUNNEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFunnel(int type);
void UninitFunnel(void);
void UpdateFunnel(void);
void DrawFunnel(void);
FUNNEL *GetFunnel(int no);
void SetFunnel(D3DXVECTOR3 pos);
void ReleaseFunnel(void);
void InitStatusFunnel(int nFunnel);

#endif
