//=============================================================================
//
// HOWTOPLAY_CONTROLLER���� [howtoplay_controller.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _HOWTOPLAY_CONTROLLER_H_
#define _HOWTOPLAY_CONTROLLER_H_

#include "main.h"

// �}�N����`
#define NUM_HOWTOPLAY_CONTROLLER		(2)	// �|���S����

#define TEXTURE_GAME_HOWTOPLAY_CONTROLLER	_T("data/TEXTURE/howtoplay_controller.png")	// HOWTOPLAY_CONTROLLER�p�摜
#define TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_X	(1280 * SCREEN_SCALING/2) // �e�N�X�`���T�C�Y
#define TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_Y	(720 * SCREEN_SCALING/2) // ����

#define HOWTOPLAY_CONTROLLER_POS_X				(SCREEN_CENTER_X)				// �������WX
#define HOWTOPLAY_CONTROLLER_POS_Y				(SCREEN_CENTER_Y)	// �������WY

#define TEXTURE_HOWTOPLAY_CONTROLLER_R			(255) // �e�N�X�`���J���[��
#define TEXTURE_HOWTOPLAY_CONTROLLER_G			(255) // �e�N�X�`���J���[��
#define TEXTURE_HOWTOPLAY_CONTROLLER_B			(255) // �e�N�X�`���J���[��

#define TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY_CONTROLLER	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY_CONTROLLER	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_HOWTOPLAY_CONTROLLER			(TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY_CONTROLLER*TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY_CONTROLLER)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_HOWTOPLAY_CONTROLLER				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define HOWTOPLAY_CONTROLLER_MAX					(1)	// HOWTOPLAY_CONTROLLER�̍ő吔


/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// HOWTOPLAY_CONTROLLER�̈ړ���
	D3DXVECTOR3				rot;					// HOWTOPLAY_CONTROLLER�̉�]��
	D3DXVECTOR2				size;					// HOWTOPLAY_CONTROLLER�̃e�N�X�`���T�C�Y(x,y)
	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bUse;					// true:�g�p  false:���g�p
}HOWTOPLAY_CONTROLLER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitHowtoplay_controller(int type);
void UninitHowtoplay_controller(void);
void UpdateHowtoplay_controller(void);
void DrawHowtoplay_controller(void);
HOWTOPLAY_CONTROLLER *GetHowtoplay_controller(int no);


#endif
