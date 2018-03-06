//=============================================================================
//
// �q�b�g�T�[�N������ [effect_close.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _EFFECT_CLOSE_H_
#define _EFFECT_CLOSE_H_

#include "main.h"

// �}�N����`
#define NUM_EFFECT_CLOSE						(2)		// �|���S����
#define TEXTURE_GAME_EFFECT_CLOSE		_T("data/TEXTURE/effect_close.png")	// �q�b�g�T�[�N��00�p�摜
#define TEXTURE_EFFECT_CLOSE00_SIZE_X			(1280 * SCREEN_SCALING/2)	// �e�N�X�`���T�C�Y
#define TEXTURE_EFFECT_CLOSE00_SIZE_Y			(480 * SCREEN_SCALING/2)	// ����
#define TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE	(1)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT_CLOSE	(15)		// �A�j���p�^�[���̃e�N�X�`�����������iY)

#define EFFECT_CLOSE_SKIPANIME00	(0)
#define EFFECT_CLOSE_SKIPANIME14	(14)

#define EFFECT_CLOSE_POS_X			(SCREEN_CENTER_X)		// �|���S���̏����ʒuX
#define EFFECT_CLOSE_POS_Y			(SCREEN_CENTER_Y)		// ����

#define ANIM_PATTERN_NUM_EFFECT_CLOSE			(TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE*TEXTURE_PATTERN_DIVIDE_Y_EFFECT_CLOSE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EFFECT_CLOSE			(10)		// �A�j���[�V�����̐؂�ւ��J�E���g
#define EFFECT_CLOSE_MAX						(1)		// �ő吔�o����

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
}EFFECT_CLOSE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect_close(int type);
void UninitEffect_close(void);
void UpdateEffect_close(void);
void DrawEffect_close(void);
void SetEffect_close(void);
EFFECT_CLOSE *GetEffect_close(int no);


#endif
