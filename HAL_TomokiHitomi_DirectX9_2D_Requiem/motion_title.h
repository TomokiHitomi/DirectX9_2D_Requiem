//=============================================================================
//
// �q�b�g�T�[�N������ [motion_title.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _MOTION_TITLE_H_
#define _MOTION_TITLE_H_

#include "main.h"

// �}�N����`
#define NUM_MOTION_TITLE						(2)		// �|���S����
#define TEXTURE_GAME_MOTION_TITLE		_T("data/TEXTURE/motion_title.png")	// �q�b�g�T�[�N��00�p�摜
#define TEXTURE_MOTION_TITLE00_SIZE_X			(300 * SCREEN_SCALING/2)	// �e�N�X�`���T�C�Y
#define TEXTURE_MOTION_TITLE00_SIZE_Y			(540 * SCREEN_SCALING/2)	// ����
#define TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE	(13)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_MOTION_TITLE	(6)		// �A�j���p�^�[���̃e�N�X�`�����������iY)

#define MOTION_TITLE_POS_X			(350 * SCREEN_SCALING)		// �|���S���̏����ʒuX
#define MOTION_TITLE_POS_Y			(550 * SCREEN_SCALING)		// ����

#define ANIM_PATTERN_NUM_MOTION_TITLE		(TEXTURE_PATTERN_DIVIDE_X_MOTION_TITLE*TEXTURE_PATTERN_DIVIDE_Y_MOTION_TITLE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_MOTION_TITLE			(10)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define MOTION_TITLE_MAX						(1)		// �ő吔�o����

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
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bUse;					// �g�p�t���O
	bool					bFlap;					// �܂�Ԃ�
}MOTION_TITLE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMotion_title(int type);
void UninitMotion_title(void);
void UpdateMotion_title(void);
void DrawMotion_title(void);
void SetMotion_title(void);
MOTION_TITLE *GetMotion_title(int no);


#endif
