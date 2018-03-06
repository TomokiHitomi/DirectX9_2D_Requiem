//=============================================================================
//
// FRAME���� [frame.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _FRAME_H_
#define _FRAME_H_

#include "main.h"

// �}�N����`
#define NUM_FRAME		(2)	// �|���S����

#define TEXTURE_GAME_FRAME	_T("data/TEXTURE/frame.png")	// FRAME�p�摜
#define TEXTURE_FRAME_SIZE_X	(1280 * SCREEN_SCALING/2) // �e�N�X�`���T�C�Y
#define TEXTURE_FRAME_SIZE_Y	(720 * SCREEN_SCALING/2) // ����

#define TEXTURE_FRAME_R			(255) // �e�N�X�`���J���[��
#define TEXTURE_FRAME_G			(255) // �e�N�X�`���J���[��
#define TEXTURE_FRAME_B			(255) // �e�N�X�`���J���[��

#define TEXTURE_PATTERN_DIVIDE_X_FRAME	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_FRAME	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_FRAME			(TEXTURE_PATTERN_DIVIDE_X_FRAME*TEXTURE_PATTERN_DIVIDE_Y_FRAME)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_FRAME			(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define FRAME_MAX					(1)	// FRAME�̍ő吔


/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// FRAME�̈ړ���
	D3DXVECTOR3				rot;					// FRAME�̉�]��
	D3DXVECTOR2				size;					// FRAME�̃e�N�X�`���T�C�Y(x,y)
	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bUse;					// true:�g�p  false:���g�p
}FRAME;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFrame(int type);
void UninitFrame(void);
void UpdateFrame(void);
void DrawFrame(void);
FRAME *GetFrame(int no);


#endif
