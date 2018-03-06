//=============================================================================
//
// �p�����[�^���� [parameterbar.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _PARAMETERBAR_H_
#define _PARAMETERBAR_H_

#include "main.h"

// �}�N����`
#define NUM_PARAMETERBAR		(2)	// �|���S����

#define TEXTURE_GAME_PARAMETERBAR00	_T("data/TEXTURE/parameterframe.png")	// hp�p�摜
#define TEXTURE_PARAMETERBAR00_SIZE_X	(70 * SCREEN_SCALING/2) // �e�N�X�`���T�C�Y
#define TEXTURE_PARAMETERBAR00_SIZE_Y	(9 * SCREEN_SCALING/2) // ����

#define TEXTURE_CHANGE_PARAMETERBAR_X		(1.0f)
#define TEXTURE_CHANGE_PARAMETERBAR_Y		(1.0f)

#define TEXTURE_CHANGE_BOSS_PARAMETERBAR_X	(15.0f)
#define TEXTURE_CHANGE_BOSS_PARAMETERBAR_Y	(1.5f)

#define BOSS_PARAMETERBAR_POS_X			(642 * SCREEN_SCALING)
#define BOSS_PARAMETERBAR_POS_Y			(110 * SCREEN_SCALING)

#define TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR	(3)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_PARAMETERBAR	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_PARAMETERBAR			(TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR*TEXTURE_PATTERN_DIVIDE_Y_PARAMETERBAR)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_PARAMETERBAR				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define PARAMETERBAR_MAX					(30)// �p�����[�^�̍ő吔
#define PARAMETERBAR_SPEED					(8)	// �p�����[�^�̈ړ����x

#define PARAMETERBAR_DRAW_HP				(25 * SCREEN_SCALING)	// HP�Q�[�W�̕\���ʒu
#define PARAMETERBAR_DRAW_MP				(35 * SCREEN_SCALING)	// MP�Q�[�W�̕\���ʒu

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
}PARAMETERBAR;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitParameterbar(int type);
void UninitParameterbar(void);
void UpdateParameterbar(void);
void DrawParameterbar(void);
void SetParameterbar(int nType, D3DXVECTOR3 vecTargetPos, int nTarget);
void InitStatusParameterbar(int nParameterbar);
PARAMETERBAR *GetParameterbar(int no);


#endif
