//=============================================================================
//
// �q�b�g�T�[�N������ [nogravity.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _NOGRAVITY_H_
#define _NOGRAVITY_H_

#include "main.h"

// �}�N����`
#define NUM_NOGRAVITY						(2)		// �|���S����
#define TEXTURE_GAME_NOGRAVITY00		_T("data/TEXTURE/nogravity.png")	// �q�b�g�T�[�N��00�p�摜
#define TEXTURE_NOGRAVITY00_SIZE_X			(20 * SCREEN_SCALING/2)	// �e�N�X�`���T�C�Y
#define TEXTURE_NOGRAVITY00_SIZE_Y			(20 * SCREEN_SCALING/2)	// ����
#define TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY	(1)		// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_NOGRAVITY	(1)		// �A�j���p�^�[���̃e�N�X�`�����������iY)

#define TEXTURE_NOGRAVITY00_SCALING_SPEED	(25)		// �g��k���X�s�[�h
#define TEXTURE_NOGRAVITY00_SCALING_MAX		(1800 * SCREEN_SCALING)		// �ő�g��l


#define ANIM_PATTERN_NUM_NOGRAVITY			(TEXTURE_PATTERN_DIVIDE_X_NOGRAVITY*TEXTURE_PATTERN_DIVIDE_Y_NOGRAVITY)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_NOGRAVITY			(4)		// �A�j���[�V�����̐؂�ւ��J�E���g
#define NOGRAVITY_MAX						(1)		// �q�b�g�T�[�N���̍ő吔

#define NOGRAVITY_ALPHA						(100)	// ���d�̓T�[�N���̃��l

// �q�b�g�T�[�N���̃Z�b�g���W����
#define NOGRAVITY_ADJUSTMENT_X				(0)
#define NOGRAVITY_ADJUSTMENT_Y				(-5)

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
	int						nScaling;				// �g��E�k��
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bUse;					// �q�b�g�T�[�N���t���O
}NOGRAVITY;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitNogravity(int type);
void UninitNogravity(void);
void UpdateNogravity(void);
void DrawNogravity(void);
NOGRAVITY *GetNogravity(int no);


#endif
