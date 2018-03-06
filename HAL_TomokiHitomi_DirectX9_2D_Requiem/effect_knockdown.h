//=============================================================================
//
// �q�b�g�T�[�N������ [effect_knockdown.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _EFFECT_KNOCKDOWN_H_
#define _EFFECT_KNOCKDOWN_H_

#include "main.h"

// �}�N����`
#define NUM_EFFECT_KNOCKDOWN						(2)		// �|���S����
#define TEXTURE_GAME_EFFECT_KNOCKDOWN		_T("data/TEXTURE/effect_knockdown.png")	// �q�b�g�T�[�N��00�p�摜
#define TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X			(160 * SCREEN_SCALING/2)	// �e�N�X�`���T�C�Y
#define TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y			(160 * SCREEN_SCALING/2)	// ����
#define TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN	(10)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT_KNOCKDOWN	(10)		// �A�j���p�^�[���̃e�N�X�`�����������iY)

#define ANIM_PATTERN_NUM_EFFECT_KNOCKDOWN			(TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN*TEXTURE_PATTERN_DIVIDE_Y_EFFECT_KNOCKDOWN)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EFFECT_KNOCKDOWN				(3)		// �A�j���[�V�����̐؂�ւ��J�E���g
#define EFFECT_KNOCKDOWN_MAX						(30)		// �ő吔�o����

// �Z�b�g���W����
#define EFFECT_KNOCKDOWN_ADJUSTMENT_X				(0)
#define EFFECT_KNOCKDOWN_ADJUSTMENT_Y				(0)

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
	int						nTypeAnim;				// �A�j���[�V�����^�C�v
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bUse;					// �q�b�g�T�[�N���t���O
}EFFECT_KNOCKDOWN;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect_knockdown(int type);
void UninitEffect_knockdown(void);
void UpdateEffect_knockdown(void);
void DrawEffect_knockdown(void);
void SetEffect_knockdown(D3DXVECTOR3 vecPos, int nType);
EFFECT_KNOCKDOWN *GetEffect_knockdown(int no);


#endif
