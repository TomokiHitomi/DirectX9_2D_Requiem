//=============================================================================
//
// �^�C�g������ [rankboard.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _RANKBOARD_H_
#define _RANKBOARD_H_

#include "main.h"

// �}�N����`
#define NUM_RANKBOARD		(2)	// �|���S����

#define TEXTURE_GAME_RANKBOARD00	_T("data/TEXTURE/rankboard.png")	// �^�C�g��00�p�摜
#define TEXTURE_RANKBOARD00_SIZE_X	(225 * SCREEN_SCALING/2)	// �e�N�X�`���T�C�Y
#define TEXTURE_RANKBOARD00_SIZE_Y	(290 * SCREEN_SCALING/2)	// ����
#define RANKBOARD_POS_X			(1050 * SCREEN_SCALING)	// �������WX
#define RANKBOARD_POS_Y			(530 * SCREEN_SCALING)	// �������WY

#define TEXTURE_PATTERN_DIVIDE_X_RANKBOARD	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_RANKBOARD	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_RANKBOARD			(TEXTURE_PATTERN_DIVIDE_X_RANKBOARD*TEXTURE_PATTERN_DIVIDE_Y_RANKBOARD)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_RANKBOARD				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define RANKBOARD_MAX					(1)	// �g�[�^���X�R�A�{�[�h�̍ő吔
#define RANKBOARD_MAX					(1)	// �g�[�^���X�R�A�{�[�h�̍ő吔


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
}RANKBOARD;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRankboard(int type);
void UninitRankboard(void);
void UpdateRankboard(void);
void DrawRankboard(void);
RANKBOARD *GetRankboard(int no);


#endif
