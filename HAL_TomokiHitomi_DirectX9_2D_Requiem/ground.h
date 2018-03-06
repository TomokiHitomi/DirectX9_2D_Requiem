//=============================================================================
//
// �^�C�g������ [ground.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _GROUND_H_
#define _GROUND_H_

#include "main.h"

// �}�N����`
#define NUM_GROUND		(2)	// �|���S����

#define TEXTURE_GAME_GROUND00	_T("data/TEXTURE/ground.png")	// �^�C�g��00�p�摜
#define TEXTURE_GROUND_SIZE_X	(300 * SCREEN_SCALING/2) // �e�N�X�`���T�C�Y
#define TEXTURE_GROUND_SIZE_Y	(100 * SCREEN_SCALING/2) // ����
#define GROUND_POS_X			(TEXTURE_GROUND_SIZE_X)	// �������WX
#define GROUND_POS_Y			(SCREEN_HEIGHT-10)		// �������WY

#define TEXTURE_GROUND_R			(220) // �e�N�X�`���J���[��
#define TEXTURE_GROUND_G			(220) // �e�N�X�`���J���[��
#define TEXTURE_GROUND_B			(220) // �e�N�X�`���J���[��

#define TEXTURE_PATTERN_DIVIDE_X_GROUND	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_GROUND	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_GROUND			(TEXTURE_PATTERN_DIVIDE_X_GROUND*TEXTURE_PATTERN_DIVIDE_Y_GROUND)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_GROUND				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define GROUND_MAX					(6)		// �^�C�g���̍ő吔
#define GROUND_SPEED				(1.5f * SCREEN_SCALING)	// �X�N���[�����x

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
}GROUND;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGround(int type);
void UninitGround(void);
void UpdateGround(void);
void DrawGround(void);
GROUND *GetGround(int no);


#endif
