//=============================================================================
//
// �^�C�g������ [title.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

// �}�N����`
#define NUM_TITLE		(2)	// �|���S����

#define TEXTURE_GAME_TITLE00	_T("data/TEXTURE/title_logo.png")	// �^�C�g��00�p�摜
#define TEXTURE_TITLE00_SIZE_X	(800 * SCREEN_SCALING/2) // �e�N�X�`���T�C�Y
#define TEXTURE_TITLE00_SIZE_Y	(1000/3 * SCREEN_SCALING/2) // ����

#define TITLE_POS_X				(SCREEN_CENTER_X)				// �������WX
#define TITLE_POS_Y				(220 * SCREEN_SCALING)			// �������WY

#define TEXTURE_PATTERN_DIVIDE_X_TITLE	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_TITLE	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_TITLE			(TEXTURE_PATTERN_DIVIDE_X_TITLE*TEXTURE_PATTERN_DIVIDE_Y_TITLE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_TITLE				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define TITLE_MAX					(1)	// �^�C�g���̍ő吔

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
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a

	bool					bUse;					// true:�g�p  false:���g�p
}TITLE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(int type);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
TITLE *GetTitle(int no);


#endif
