//=============================================================================
//
// BG001���� [bg001.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _BG001_H_
#define _BG001_H_

#include "main.h"

// �}�N����`
#define NUM_BG001		(2)	// �|���S����

#define TEXTURE_GAME_BG001	_T("data/TEXTURE/bg001.png")	// BG001�p�摜
#define TEXTURE_BG001_SIZE_X	((5000 * SCREEN_SCALING) / 2) // �e�N�X�`���T�C�Y
#define TEXTURE_BG001_SIZE_Y	((915 * SCREEN_SCALING) / 2) // ����

#define BG001_POS_X				(TEXTURE_BG001_SIZE_X)	// �������WX
#define BG001_POS_Y				(300 * SCREEN_SCALING)	// �������WY

#define TEXTURE_BG001_R			(100) // �e�N�X�`���J���[��
#define TEXTURE_BG001_G			(100) // �e�N�X�`���J���[��
#define TEXTURE_BG001_B			(100) // �e�N�X�`���J���[��

#define TEXTURE_PATTERN_DIVIDE_X_BG001	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BG001	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BG001			(TEXTURE_PATTERN_DIVIDE_X_BG001*TEXTURE_PATTERN_DIVIDE_Y_BG001)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BG001				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BG001_MAX					(2)	// �ő吔
#define BG001_SPEED					(1.5f * SCREEN_SCALING)	// �X�N���[�����x


/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// BG001�̈ړ���
	D3DXVECTOR3				rot;					// BG001�̉�]��
	D3DXVECTOR2				size;					// BG001�̃e�N�X�`���T�C�Y(x,y)
	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;					// ���a
	bool					bUse;					// true:�g�p  false:���g�p
}BG001;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBg001(int type);
void UninitBg001(void);
void UpdateBg001(void);
void DrawBg001(void);
BG001 *GetBg001(int no);


#endif
