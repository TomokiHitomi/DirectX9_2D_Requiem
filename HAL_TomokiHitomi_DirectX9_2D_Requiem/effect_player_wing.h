//=============================================================================
//
// �q�b�g�T�[�N������ [effect_player_wing.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _EFFECT_PLAYER_WING_H_
#define _EFFECT_PLAYER_WING_H_

#include "main.h"

// �}�N����`
#define NUM_EFFECT_PLAYER_WING						(2)		// �|���S����
#define TEXTURE_GAME_EFFECT_PLAYER_WING		_T("data/TEXTURE/effect_player_wing.png")	// �q�b�g�T�[�N��00�p�摜
#define TEXTURE_EFFECT_PLAYER_WING00_SIZE_X			(120 * SCREEN_SCALING/2)	// �e�N�X�`���T�C�Y
#define TEXTURE_EFFECT_PLAYER_WING00_SIZE_Y			(120 * SCREEN_SCALING/2)	// ����
#define TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING	(5)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_WING	(6)		// �A�j���p�^�[���̃e�N�X�`�����������iY)

#define EFFECT_PLAYER_WING_LOOP_MIN					(5)
#define EFFECT_PLAYER_WING_LOOP_MAX					(25)

#define EFFECT_PLAYER_WING_ALPHA_MAX				(255)

#define ANIM_PATTERN_NUM_EFFECT_PLAYER_WING			(TEXTURE_PATTERN_DIVIDE_X_EFFECT_PLAYER_WING*TEXTURE_PATTERN_DIVIDE_Y_EFFECT_PLAYER_WING)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EFFECT_PLAYER_WING			(3)		// �A�j���[�V�����̐؂�ւ��J�E���g
#define EFFECT_PLAYER_WING_MAX						(1)		// �ő吔�o����

// �Z�b�g���W����
#define EFFECT_PLAYER_WING_ADJUSTMENT_X				(0)
#define EFFECT_PLAYER_WING_ADJUSTMENT_Y				(-30 * SCREEN_SCALING)

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
	int						nAlpha;					// ���l
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bLoop;					// ���[�v�t���O
	bool					bUse;					// �A�N�e�B�u�t���O
}EFFECT_PLAYER_WING;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitEffect_player_wing(int type);
void UninitEffect_player_wing(void);
void UpdateEffect_player_wing(void);
void DrawEffect_player_wing(void);
void SetEffect_player_wing();
void ReleaseEffect_player_wing();
EFFECT_PLAYER_WING *GetEffect_player_wing(int no);


#endif
