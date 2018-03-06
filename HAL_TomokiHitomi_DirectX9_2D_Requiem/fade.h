//=============================================================================
//
// FADE���� [fade.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

// �}�N����`
#define NUM_FADE		(2)	// �|���S����

#define TEXTURE_GAME_FADE	_T("data/TEXTURE/fade.jpg")	// FADE�p�摜
#define TEXTURE_FADE_SIZE_X	(1280 * SCREEN_SCALING/2) // �e�N�X�`���T�C�Y
#define TEXTURE_FADE_SIZE_Y	(960 * SCREEN_SCALING/2) // ����

#define TEXTURE_PATTERN_DIVIDE_X_FADE	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_FADE	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_FADE			(TEXTURE_PATTERN_DIVIDE_X_FADE*TEXTURE_PATTERN_DIVIDE_Y_FADE)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_FADE				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define FADE_MAX					(1)		// FADE�̍ő吔
#define FADE_ALPHA_MAX				(255)	// �t�F�[�h�ő�A���t�@�l
#define FADE_ALPHA_MID				(150)	// �t�F�[�h�A���t�@�l
#define FADE_SPEED					(7)		// �t�F�[�h�X�s�[�h
#define FADE_COMPLETE				(FADE_ALPHA_MAX/FADE_SPEED)

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// FADE�̈ړ���
	D3DXVECTOR3				rot;					// FADE�̉�]��
	D3DXVECTOR2				size;					// FADE�̃e�N�X�`���T�C�Y(x,y)
	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	int						nAlphaCount;			// �A���t�@�l�̃J�E���g
	int						nFadeFlag;				// �t�F�[�h�t���O
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a

	bool					bUse;					// true:�g�p  false:���g�p
}FADE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFade(int type);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(int nFade, int nFadeFlag);
FADE *GetFade(int no);


#endif
