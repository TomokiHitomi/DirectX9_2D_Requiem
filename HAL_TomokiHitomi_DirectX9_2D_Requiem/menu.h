//=============================================================================
//
// �^�C�g������ [menu.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _MENU_H_
#define _MENU_H_

#include "main.h"

// �}�N����`
#define NUM_MENU		(2)	// �|���S����

#define TEXTURE_GAME_MENU00	_T("data/TEXTURE/menu.png")	// �^�C�g��00�p�摜
#define TEXTURE_MENU00_SIZE_X	(400 * SCREEN_SCALING/2) // �e�N�X�`���T�C�Y
#define TEXTURE_MENU00_SIZE_Y	(80 * SCREEN_SCALING/2) // ����
#define MENU_POS_X			(SCREEN_CENTER_X)	// �������WX
#define MENU_POS_Y			(380 * SCREEN_SCALING)				// �������WY
#define MENU_SPACING		(75 * SCREEN_SCALING)

#define TEXTURE_PATTERN_DIVIDE_X_MENU	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_MENU	(4)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_MENU			(TEXTURE_PATTERN_DIVIDE_X_MENU*TEXTURE_PATTERN_DIVIDE_Y_MENU)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_MENU				(1)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define MENU_MAX					(4)	// �^�C�g���̍ő吔
#define MENU_SELECT_PRESS			(40)	// ���j���[��������J�n�^�C��
#define MENU_SELECT_SPEED			(7)		// ���j���|�������葬�x

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
}MENU;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMenu(int type);
void UninitMenu(void);
void UpdateMenu(void);
void DrawMenu(void);
void SetMenu(void);
void ReleaseMenu(void);
MENU *GetMenu(int no);


#endif
