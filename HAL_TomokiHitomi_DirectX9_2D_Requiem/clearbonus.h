//=============================================================================
//
// �^�C�g������ [clearbonus.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _CLEARBONUS_H_
#define _CLEARBONUS_H_

#include "main.h"

// �}�N����`
#define NUM_CLEARBONUS		(2)	// �|���S����

#define TEXTURE_GAME_CLEARBONUS00	_T("data/TEXTURE/clearbonus.png")	// �^�C�g��00�p�摜
#define TEXTURE_CLEARBONUS00_SIZE_X	(390 * SCREEN_SCALING/2)	// �e�N�X�`���T�C�Y
#define TEXTURE_CLEARBONUS00_SIZE_Y	(130 * SCREEN_SCALING/2)	// ����

#define CLEARBONUS_POS_X			(500 * SCREEN_SCALING)	// �������WX
#define CLEARBONUS_POS_Y			(445 * SCREEN_SCALING)	// �������WY

#define TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_CLEARBONUS	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_CLEARBONUS			(TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS*TEXTURE_PATTERN_DIVIDE_Y_CLEARBONUS)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_CLEARBONUS				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define CLEARBONUS_MAX					(1)	// �g�[�^���X�R�A�{�[�h�̍ő吔
#define CLEARBONUS_MAX					(1)	// �g�[�^���X�R�A�{�[�h�̍ő吔


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
}CLEARBONUS;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitClearbonus(int type);
void UninitClearbonus(void);
void UpdateClearbonus(void);
void DrawClearbonus(void);
CLEARBONUS *GetClearbonus(int no);


#endif
