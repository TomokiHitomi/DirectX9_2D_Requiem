//=============================================================================
//
// �^�C�g������ [pressenter.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _PRESSENTER_H_
#define _PRESSENTER_H_

#include "main.h"

// �}�N����`
#define NUM_PRESSENTER		(2)	// �|���S����

#define TEXTURE_GAME_PRESSENTER00	_T("data/TEXTURE/pressenter.png")	// �^�C�g��00�p�摜
#define TEXTURE_PRESSENTER00_SIZE_X	(700 * SCREEN_SCALING/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_PRESSENTER00_SIZE_Y	(100 * SCREEN_SCALING/2)		// ����
#define PRESSENTER_POS_X				(500 * SCREEN_SCALING)		// �������WX
#define PRESSENTER_POS_Y				(630 * SCREEN_SCALING)		// �������WY

#define TEXTURE_PATTERN_DIVIDE_X_PRESSENTER	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_PRESSENTER	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_PRESSENTER			(TEXTURE_PATTERN_DIVIDE_X_PRESSENTER*TEXTURE_PATTERN_DIVIDE_Y_PRESSENTER)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_PRESSENTER				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define PRESSENTER_MAX					(1)		// �^�C�g���̍ő吔
#define PRESSENTER_ALPHA_MAX			(255)	// �t�F�[�h�ő�A���t�@�l
#define PRESSENTER_ALPHA_MIN			(150)	// �t�F�[�h�ő�A���t�@�l
#define PRESSENTER_ALPHA_UP_SPEED		(3)		// �t�F�[�h�ő�A���t�@�l
#define PRESSENTER_ALPHA_DOWN_SPEED		(3)		// �t�F�[�h�ő�A���t�@�l

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// �^�C�g���̈ړ���
	D3DXVECTOR3				rot;					// �^�C�g���̉�]��
	D3DXVECTOR2				size;					// �^�C�g���̃e�N�X�`���T�C�Y(x,y)
	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	int						nAlphaCount;			// �t�F�[�h�J�E���g

	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a

	bool					bUse;					// true:�g�p  false:���g�p
	bool					bAlphaFlag;				// �A���t�@�t���O
}PRESSENTER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPressenter(int type);
void UninitPressenter(void);
void UpdatePressenter(void);
void DrawPressenter(void);
PRESSENTER *GetPressenter(int no);


#endif
