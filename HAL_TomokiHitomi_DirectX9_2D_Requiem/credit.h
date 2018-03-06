//=============================================================================
//
// CREDIT���� [credit.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _CREDIT_H_
#define _CREDIT_H_

#include "main.h"

// �}�N����`
#define NUM_CREDIT		(2)	// �|���S����

#define TEXTURE_GAME_CREDIT	_T("data/TEXTURE/credit.png")	// CREDIT�p�摜
#define TEXTURE_CREDIT_SIZE_X	(1280 * SCREEN_SCALING/2) // �e�N�X�`���T�C�Y
#define TEXTURE_CREDIT_SIZE_Y	(648 * SCREEN_SCALING/2) // ����

#define CREDIT_POS_X				(SCREEN_CENTER_X)			// �������WX
#define CREDIT_POS_Y				(SCREEN_CENTER_Y)			// �������WY

#define TEXTURE_CREDIT_R			(255) // �e�N�X�`���J���[��
#define TEXTURE_CREDIT_G			(255) // �e�N�X�`���J���[��
#define TEXTURE_CREDIT_B			(255) // �e�N�X�`���J���[��

#define TEXTURE_PATTERN_DIVIDE_X_CREDIT	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_CREDIT	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_CREDIT			(TEXTURE_PATTERN_DIVIDE_X_CREDIT*TEXTURE_PATTERN_DIVIDE_Y_CREDIT)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_CREDIT				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define CREDIT_MAX					(1)	// CREDIT�̍ő吔


/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// CREDIT�̈ړ���
	D3DXVECTOR3				rot;					// CREDIT�̉�]��
	D3DXVECTOR2				size;					// CREDIT�̃e�N�X�`���T�C�Y(x,y)
	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bUse;					// true:�g�p  false:���g�p
}CREDIT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCredit(int type);
void UninitCredit(void);
void UpdateCredit(void);
void DrawCredit(void);
void SetCredit(void);
CREDIT *GetCredit(int no);


#endif
