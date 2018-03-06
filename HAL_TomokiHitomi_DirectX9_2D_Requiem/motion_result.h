//=============================================================================
//
// �q�b�g�T�[�N������ [motion_result.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _MOTION_RESULT_H_
#define _MOTION_RESULT_H_

#include "main.h"

// �}�N����`
#define NUM_MOTION_RESULT						(2)		// �|���S����
#define TEXTURE_GAME_MOTION_RESULT		_T("data/TEXTURE/motion_result.png")	// �q�b�g�T�[�N��00�p�摜
#define TEXTURE_MOTION_RESULT00_SIZE_X			(350 * SCREEN_SCALING/2)	// �e�N�X�`���T�C�Y
#define TEXTURE_MOTION_RESULT00_SIZE_Y			(350 * SCREEN_SCALING/2)	// ����
#define TEXTURE_PATTERN_DIVIDE_X_MOTION_RESULT	(10)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_MOTION_RESULT	(9)		// �A�j���p�^�[���̃e�N�X�`�����������iY)

#define MOTION_RESULT_POS_X			(810 * SCREEN_SCALING)		// �|���S���̏����ʒuX
#define MOTION_RESULT_POS_Y			(450 * SCREEN_SCALING)		// ����

#define ANIM_PATTERN_NUM_MOTION_RESULT		(84)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_MOTION_RESULT			(6)	// �A�j���[�V�����̐؂�ւ��J�E���g
#define MOTION_RESULT_MAX						(1)		// �ő吔�o����

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
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bUse;					// �g�p�t���O
}MOTION_RESULT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitMotion_result(int type);
void UninitMotion_result(void);
void UpdateMotion_result(void);
void DrawMotion_result(void);
void SetMotion_result(void);
MOTION_RESULT *GetMotion_result(int no);


#endif
