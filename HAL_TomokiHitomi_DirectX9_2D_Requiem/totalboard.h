//=============================================================================
//
// �^�C�g������ [totalboard.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _TOTALBOARD_H_
#define _TOTALBOARD_H_

#include "main.h"

// �}�N����`
#define NUM_TOTALBOARD		(2)	// �|���S����

#define TEXTURE_GAME_TOTALBOARD00	_T("data/TEXTURE/totalboard.png")	// �^�C�g��00�p�摜
#define TEXTURE_TOTALBOARD00_SIZE_X	(768 * SCREEN_SCALING/2)	// �e�N�X�`���T�C�Y
#define TEXTURE_TOTALBOARD00_SIZE_Y	(90 * SCREEN_SCALING/2)	// ����
#define TOTALBOARD_POS_X			(490 * SCREEN_SCALING)	// �������WX
#define TOTALBOARD_POS_Y			(530 * SCREEN_SCALING)	// �������WY

#define TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_TOTALBOARD	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_TOTALBOARD			(TEXTURE_PATTERN_DIVIDE_X_TOTALBOARD*TEXTURE_PATTERN_DIVIDE_Y_TOTALBOARD)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_TOTALBOARD				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define TOTALBOARD_MAX					(1)	// �g�[�^���X�R�A�{�[�h�̍ő吔


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
}TOTALBOARD;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTotalboard(int type);
void UninitTotalboard(void);
void UpdateTotalboard(void);
void DrawTotalboard(void);
TOTALBOARD *GetTotalboard(int no);


#endif
