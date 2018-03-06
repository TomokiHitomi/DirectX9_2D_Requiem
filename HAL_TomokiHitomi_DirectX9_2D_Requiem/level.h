//=============================================================================
//
// �^�C�g������ [level.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "main.h"

// �}�N����`
#define NUM_LEVEL		(2)	// �|���S����

#define TEXTURE_GAME_LEVEL00	_T("data/TEXTURE/level.png")	// �^�C�g��00�p�摜
#define TEXTURE_LEVEL00_SIZE_X	(400 * SCREEN_SCALING/2) // �e�N�X�`���T�C�Y
#define TEXTURE_LEVEL00_SIZE_Y	(80 * SCREEN_SCALING/2) // ����

#define LEVEL_POS_X			(SCREEN_CENTER_X)	// �������WX
#define LEVEL_POS_Y			(380 * SCREEN_SCALING)				// �������WY
#define LEVEL_SPACING		(75 * SCREEN_SCALING)

#define TEXTURE_PATTERN_DIVIDE_X_LEVEL	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_LEVEL	(4)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_LEVEL			(TEXTURE_PATTERN_DIVIDE_X_LEVEL*TEXTURE_PATTERN_DIVIDE_Y_LEVEL)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_LEVEL				(1)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define LEVEL_MAX					(4)	// �^�C�g���̍ő吔
#define LEVEL_SELECT_PRESS			(40)	// ���j���[��������J�n�^�C��
#define LEVEL_SELECT_SPEED			(7)		// ���j���|�������葬�x

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
	float					fRadius;					// ���a
	bool					bUse;					// true:�g�p  false:���g�p
}LEVEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitLevel(int type);
void UninitLevel(void);
void UpdateLevel(void);
void DrawLevel(void);
void SetLevel(void);
void ReleaseLevel(void);
LEVEL *GetLevel(int no);


#endif
