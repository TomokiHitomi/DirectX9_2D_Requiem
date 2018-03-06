//=============================================================================
//
// BG000���� [bg000.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _BG000_H_
#define _BG000_H_

#include "main.h"

// �}�N����`
#define NUM_BG000		(2)	// �|���S����

#define TEXTURE_GAME_BG000	_T("data/TEXTURE/bg000.png")	// BG000�p�摜
#define TEXTURE_BG000_SIZE_X	(SCREEN_WIDTH / 2) // �e�N�X�`���T�C�Y
#define TEXTURE_BG000_SIZE_Y	(SCREEN_HEIGHT / 2) // ����

#define TEXTURE_BG000_R			(255) // �e�N�X�`���J���[��
#define TEXTURE_BG000_G			(255) // �e�N�X�`���J���[��
#define TEXTURE_BG000_B			(255) // �e�N�X�`���J���[��

#define TEXTURE_PATTERN_DIVIDE_X_BG000	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BG000	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BG000			(TEXTURE_PATTERN_DIVIDE_X_BG000*TEXTURE_PATTERN_DIVIDE_Y_BG000)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BG000				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BG000_MAX					(1)	// BG000�̍ő吔


/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// BG000�̈ړ���
	D3DXVECTOR3				rot;					// BG000�̉�]��
	D3DXVECTOR2				size;					// BG000�̃e�N�X�`���T�C�Y(x,y)
	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bUse;					// true:�g�p  false:���g�p
}BG000;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBg000(int type);
void UninitBg000(void);
void UpdateBg000(void);
void DrawBg000(void);
BG000 *GetBg000(int no);


#endif
