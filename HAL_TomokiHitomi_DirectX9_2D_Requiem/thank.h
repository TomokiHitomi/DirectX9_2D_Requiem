//=============================================================================
//
// �^�C�g������ [thank.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _THANK_H_
#define _THANK_H_

#include "main.h"

// �}�N����`
#define NUM_THANK		(2)	// �|���S����

#define TEXTURE_GAME_THANK00	_T("data/TEXTURE/thank.png")	// �^�C�g��00�p�摜
#define TEXTURE_THANK00_SIZE_X	(1200 * SCREEN_SCALING/2)		// �e�N�X�`���T�C�Y
#define TEXTURE_THANK00_SIZE_Y	(200 * SCREEN_SCALING/2)		// ����
#define THANK_POS_X				(SCREEN_CENTER_X)		// �������WX
#define THANK_POS_Y				(SCREEN_CENTER_Y)		// �������WY

#define TEXTURE_PATTERN_DIVIDE_X_THANK	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_THANK	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_THANK			(TEXTURE_PATTERN_DIVIDE_X_THANK*TEXTURE_PATTERN_DIVIDE_Y_THANK)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_THANK				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define THANK_MAX					(1)		// �^�C�g���̍ő吔
#define THANK_ALPHA_MAX				(255)	// �t�F�[�h�ő�A���t�@�l
#define THANK_ALPHA_SPEED			(5)		// �t�F�[�h�X�s�[�h
#define THANK_SCENE_COUNT			(200)	// �V�[���J�ڂ܂ł̃J�E���g

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
	int						nAlphaCount;			// �t�F�[�h�J�E���g
	int						nSceneCount;			// �V�[���J�ڃJ�E���g

	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a

	bool					bUse;					// true:�g�p  false:���g�p
}THANK;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitThank(int type);
void UninitThank(void);
void UpdateThank(void);
void DrawThank(void);
THANK *GetThank(int no);


#endif
