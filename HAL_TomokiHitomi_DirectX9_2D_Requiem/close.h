//=============================================================================
//
// �N���[�Y���� [close.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _CLOSE_H_
#define _CLOSE_H_

#include "main.h"

// �}�N����`
#define NUM_CLOSE		(2)	// �|���S����

#define TEXTURE_GAME_CLOSE00	_T("data/TEXTURE/close.png")	// �N���[�Y00�p�摜
#define TEXTURE_CLOSE00_SIZE_X	(1000 * SCREEN_SCALING / 2) // �e�N�X�`���T�C�Y
#define TEXTURE_CLOSE00_SIZE_Y	(250  * SCREEN_SCALING / 2) // ����

#define CLOSE00_POS_X			(SCREEN_CENTER_X)	// �������WX
#define CLOSE00_POS_Y			(SCREEN_CENTER_Y)	// �������WY

#define TEXTURE_PATTERN_DIVIDE_X_CLOSE	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_CLOSE	(2)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_CLOSE			(TEXTURE_PATTERN_DIVIDE_X_CLOSE*TEXTURE_PATTERN_DIVIDE_Y_CLOSE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_CLOSE				(0)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define CLOSE_MAX					(1)	// �N���[�Y�̍ő吔
#define CLOSE_SE_COUNTMAX			(70)	// SE�Đ��J�E���g
#define CLOSE_COUNTMAX				(630)	// ��ʑJ�ڃJ�E���g


/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// �N���[�Y�̈ړ���
	D3DXVECTOR3				rot;					// �N���[�Y�̉�]��
	D3DXVECTOR2				size;					// �N���[�Y�̃e�N�X�`���T�C�Y(x,y)
	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bClearFlag;				// �N���A�t���O
	bool					bUse;					// true:�g�p  false:���g�p
}CLOSE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitClose(int type);
void UninitClose(void);
void UpdateClose(void);
void DrawClose(void);
CLOSE *GetClose(int no);


#endif
