//=============================================================================
//
// �p�����[�^���� [parameter.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include "main.h"

// �}�N����`
#define NUM_PARAMETER		(2)	// �|���S����

#define TEXTURE_GAME_PARAMETER00	_T("data/TEXTURE/parameter.png")	// hp�p�摜
#define TEXTURE_PARAMETER00_SIZE_X	(70 * SCREEN_SCALING) // �e�N�X�`���T�C�Y
#define TEXTURE_PARAMETER00_SIZE_Y	(9 * SCREEN_SCALING/2) // ����

#define TEXTURE_CHANGE_PARAMETER_X		(1.0f)
#define TEXTURE_CHANGE_PARAMETER_Y		(1.0f)

#define TEXTURE_CHANGE_BOSS_PARAMETER_X	(15.0f)
#define TEXTURE_CHANGE_BOSS_PARAMETER_Y	(1.5f)

#define BOSS_PARAMETER_POS_X			(642 * SCREEN_SCALING)
#define BOSS_PARAMETER_POS_Y			(110 * SCREEN_SCALING)

#define TEXTURE_PATTERN_DIVIDE_X_PARAMETER	(3)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_PARAMETER	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_PARAMETER			(TEXTURE_PATTERN_DIVIDE_X_PARAMETER*TEXTURE_PATTERN_DIVIDE_Y_PARAMETER)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_PARAMETER				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define PARAMETER_MAX					(30)// �p�����[�^�̍ő吔
#define PARAMETER_SPEED					(8)	// �p�����[�^�̈ړ����x

#define PARAMETER_DRAW_HP				(25 * SCREEN_SCALING)	// HP�Q�[�W�̕\���ʒu
#define PARAMETER_DRAW_MP				(35 * SCREEN_SCALING)	// MP�Q�[�W�̕\���ʒu

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// �e�N�X�`�����
	VERTEX_2D				vertexWk[NUM_VERTEX];	// ���_���i�[���[�N
	D3DXVECTOR3				pos;					// �p�����[�^�̈ړ���
	D3DXVECTOR3				rot;					// �p�����[�^�̉�]��
	D3DXVECTOR2				size;					// �p�����[�^�̃e�N�X�`���T�C�Y(x,y)
	D3DXVECTOR3				vecTargetPos;			// �^�[�Q�b�g���W
	D3DXVECTOR3				vecChangeSize;			// �e�N�X�`���T�C�Y�ύX(x,y)

	int						nCountAnim;				// �A�j���[�V�����J�E���g
	int						nPatternAnim;			// �A�j���[�V�����p�^�[���i���o�[
	float					nPointGauge;			// ���݂̃|�C���g
	int						nTarget;				// �^�[�Q�b�g
	int						nType;					// �p�����[�^�^�C�v
	float					fBaseAngle;				// �p�x�i�Ɓj
	float					fRadius;				// ���a
	bool					bUse;					// true:�g�p  false:���g�p
}PARAMETER;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitParameter(int type);
void UninitParameter(void);
void UpdateParameter(void);
void DrawParameter(void);
void SetParameter(int nType, D3DXVECTOR3 vecTargetPos, int nTarget);
void InitStatusParameter(int nParameter);
PARAMETER *GetParameter(int no);


#endif
