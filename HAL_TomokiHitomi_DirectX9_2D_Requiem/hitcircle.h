//=============================================================================
//
// �q�b�g�T�[�N������ [hitcircle.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _HITCIRCLE_H_
#define _HITCIRCLE_H_

#include "main.h"

// �}�N����`
#define NUM_HITCIRCLE						(2)		// �|���S����
#define TEXTURE_GAME_HITCIRCLE00		_T("data/TEXTURE/hit.png")	// �q�b�g�T�[�N��00�p�摜
#define TEXTURE_HITCIRCLE00_SIZE_X			(20 * SCREEN_SCALING/2)	// �e�N�X�`���T�C�Y
#define TEXTURE_HITCIRCLE00_SIZE_Y			(20 * SCREEN_SCALING/2)	// ����
#define TEXTURE_PATTERN_DIVIDE_X_HITCIRCLE	(1)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_HITCIRCLE	(1)		// �A�j���p�^�[���̃e�N�X�`�����������iY)

// �����蔻��p�T�C�Y
#define HITCIRCLE_CUSTOM_SIZE_X				(1)
#define HITCIRCLE_CUSTOM_SIZE_Y				(1)

#define ANIM_PATTERN_NUM_HITCIRCLE			(TEXTURE_PATTERN_DIVIDE_X_HITCIRCLE*TEXTURE_PATTERN_DIVIDE_Y_HITCIRCLE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_HITCIRCLE			(4)		// �A�j���[�V�����̐؂�ւ��J�E���g
#define HITCIRCLE_MAX						(1)		// �q�b�g�T�[�N���̍ő吔

// �q�b�g�T�[�N���̃Z�b�g���W����
#define HITCIRCLE_ADJUSTMENT_X				(0)
#define HITCIRCLE_ADJUSTMENT_Y				(-5)

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// �ړ���
	D3DXVECTOR3				rot;					// ��]��
	D3DXVECTOR2				size;					// �e�N�X�`���T�C�Y(x,y)
	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bUse;					// �q�b�g�T�[�N���t���O
}HITCIRCLE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitHitcircle(int type);
void UninitHitcircle(void);
void UpdateHitcircle(void);
void DrawHitcircle(void);
HITCIRCLE *GetHitcircle(int no);


#endif
