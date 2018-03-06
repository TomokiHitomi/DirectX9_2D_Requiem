//=============================================================================
//
// HOWTOPLAY���� [howtoplay.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _HOWTOPLAY_H_
#define _HOWTOPLAY_H_

#include "main.h"

// �}�N����`
#define NUM_HOWTOPLAY		(2)	// �|���S����

#define TEXTURE_GAME_HOWTOPLAY	_T("data/TEXTURE/howtoplay.png")	// HOWTOPLAY�p�摜
#define TEXTURE_HOWTOPLAY_SIZE_X	(700 * SCREEN_SCALING/2) // �e�N�X�`���T�C�Y
#define TEXTURE_HOWTOPLAY_SIZE_Y	(700 * SCREEN_SCALING/2) // ����

#define HOWTOPLAY_POS_X				(920 * SCREEN_SCALING)				// �������WX
#define HOWTOPLAY_POS_Y				(SCREEN_CENTER_Y)	// �������WY

#define TEXTURE_HOWTOPLAY_R			(255) // �e�N�X�`���J���[��
#define TEXTURE_HOWTOPLAY_G			(255) // �e�N�X�`���J���[��
#define TEXTURE_HOWTOPLAY_B			(255) // �e�N�X�`���J���[��

#define TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_HOWTOPLAY			(TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY*TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_HOWTOPLAY				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define HOWTOPLAY_MAX					(1)	// HOWTOPLAY�̍ő吔


/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// HOWTOPLAY�̈ړ���
	D3DXVECTOR3				rot;					// HOWTOPLAY�̉�]��
	D3DXVECTOR2				size;					// HOWTOPLAY�̃e�N�X�`���T�C�Y(x,y)
	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bUse;					// true:�g�p  false:���g�p
}HOWTOPLAY;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitHowtoplay(int type);
void UninitHowtoplay(void);
void UpdateHowtoplay(void);
void DrawHowtoplay(void);
HOWTOPLAY *GetHowtoplay(int no);


#endif
