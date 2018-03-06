//=============================================================================
//
// �^�C�g������ [timeboard.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _TIMEBOARD_H_
#define _TIMEBOARD_H_

#include "main.h"

// �}�N����`
#define NUM_TIMEBOARD		(2)	// �|���S����

#define TEXTURE_GAME_TIMEBOARD00	_T("data/TEXTURE/timeboard.png")	// �^�C�g��00�p�摜
#define TEXTURE_TIMEBOARD00_SIZE_X	(396 * SCREEN_SCALING/2) // �e�N�X�`���T�C�Y
#define TEXTURE_TIMEBOARD00_SIZE_Y	(90 * SCREEN_SCALING/2) // ����
#define TIMEBOARD_POS_X			(310 * SCREEN_SCALING)	// �������WX
#define TIMEBOARD_POS_Y			(53 * SCREEN_SCALING)	// �������WY

#define TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_TIMEBOARD	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_TIMEBOARD			(TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD*TEXTURE_PATTERN_DIVIDE_Y_TIMEBOARD)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_TIMEBOARD				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define TIMEBOARD_MAX					(1)	// �X�R�A�{�[�h�̍ő吔


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
	bool					bPosMoveFlag;			// UI�̈ړ��t���O
	bool					bUse;					// true:�g�p  false:���g�p
}TIMEBOARD;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTimeboard(int type);
void UninitTimeboard(void);
void UpdateTimeboard(void);
void DrawTimeboard(void);
TIMEBOARD *GetTimeboard(int no);


#endif
