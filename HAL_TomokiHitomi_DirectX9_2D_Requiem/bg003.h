//=============================================================================
//
// BG003���� [bg003.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _BG003_H_
#define _BG003_H_

#include "main.h"

// �}�N����`
#define NUM_BG003		(2)	// �|���S����

#define TEXTURE_GAME_BG003	_T("data/TEXTURE/bg003.png")	// BG003�p�摜
#define TEXTURE_BG003_SIZE_X	(SCREEN_WIDTH / 2) // �e�N�X�`���T�C�Y
#define TEXTURE_BG003_SIZE_Y	(SCREEN_HEIGHT / 2) // ����

#define TEXTURE_BG003_R			(180) // �e�N�X�`���J���[��
#define TEXTURE_BG003_G			(180) // �e�N�X�`���J���[��
#define TEXTURE_BG003_B			(180) // �e�N�X�`���J���[��

#define TEXTURE_PATTERN_DIVIDE_X_BG003	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BG003	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BG003			(TEXTURE_PATTERN_DIVIDE_X_BG003*TEXTURE_PATTERN_DIVIDE_Y_BG003)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BG003				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BG003_MAX					(1)	// BG003�̍ő吔


/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// BG003�̈ړ���
	D3DXVECTOR3				rot;					// BG003�̉�]��
	D3DXVECTOR2				size;					// BG003�̃e�N�X�`���T�C�Y(x,y)
	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bUse;					// true:�g�p  false:���g�p
}BG003;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBg003(int type);
void UninitBg003(void);
void UpdateBg003(void);
void DrawBg003(void);
void SetBg003(void);
BG003 *GetBg003(int no);


#endif
