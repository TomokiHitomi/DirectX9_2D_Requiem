//=============================================================================
//
// �q�b�g�T�[�N������ [effect_player_jump.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _EFFECT_PLAYER_JUMP_H_
#define _EFFECT_PLAYER_JUMP_H_

#include "main.h"

// �}�N����`
#define NUM_EFFECT_PLAYER_JUMP						(2)		// �|���S����
#define TEXTURE_GAME_EFFECT_PLAYER_JUMP		_T("data/TEXTURE/effect_player_jump.png")	// �q�b�g�T�[�N��00�p�摜
#define TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_X			(160 * SCREEN_SCALING/2)	// �e�N�X�`���T�C�Y
#define TEXTURE_EFFECT_PLAYER_JUMP00_SIZE_Y			(60 * SCREEN_SCALING/2)	// ����
#define TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_JUMP	(1)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_JUMP	(7)		// �A�j���p�^�[���̃e�N�X�`�����������iY)

#define ANIM_PATTERN_NUM_EFFECT_PLAYER_JUMP			(TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_JUMP*TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_JUMP)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EFFECT_PLAYER_JUMP			(3)		// �A�j���[�V�����̐؂�ւ��J�E���g
#define EFFECT_PLAYER_JUMP_MAX						(2)		// �ő吔�o����

// �Z�b�g���W����
#define EFFECT_PLAYER_JUMP_ADJUSTMENT_X				(0)
#define EFFECT_PLAYER_JUMP_ADJUSTMENT_Y				(50 * SCREEN_SCALING)

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
}EFFECT_PLAYER_JUMP;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect_player_jump(int type);
void UninitEffect_player_jump(void);
void UpdateEffect_player_jump(void);
void DrawEffect_player_jump(void);
void SetEffect_player_jump(D3DXVECTOR3 vecPos);
EFFECT_PLAYER_JUMP *GetEffect_player_jump(int no);


#endif
