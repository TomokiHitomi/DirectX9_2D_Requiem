//=============================================================================
//
// BG002���� [bg002.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _BG002_H_
#define _BG002_H_

#include "main.h"

// �}�N����`
#define NUM_BG002		(2)	// �|���S����

#define TEXTURE_GAME_BG002	_T("data/TEXTURE/bg002.png")	// BG002�p�摜
#define TEXTURE_BG002_SIZE_X	(SCREEN_WIDTH / 2) // �e�N�X�`���T�C�Y
#define TEXTURE_BG002_SIZE_Y	(SCREEN_HEIGHT / 2) // ����

#define TEXTURE_BG002_R			(180) // �e�N�X�`���J���[��
#define TEXTURE_BG002_G			(180) // �e�N�X�`���J���[��
#define TEXTURE_BG002_B			(180) // �e�N�X�`���J���[��

#define TEXTURE_PATTERN_DIVIDE_X_BG002	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_BG002	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_BG002			(TEXTURE_PATTERN_DIVIDE_X_BG002*TEXTURE_PATTERN_DIVIDE_Y_BG002)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_BG002				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define BG002_MAX					(1)	// BG002�̍ő吔


/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// BG002�̈ړ���
	D3DXVECTOR3				rot;					// BG002�̉�]��
	D3DXVECTOR2				size;					// BG002�̃e�N�X�`���T�C�Y(x,y)
	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bUse;					// true:�g�p  false:���g�p
}BG002;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBg002(int type);
void UninitBg002(void);
void UpdateBg002(void);
void DrawBg002(void);
void SetBg002(void);
BG002 *GetBg002(int no);


#endif
