//=============================================================================
//
// TOTAL���� [total.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _TOTAL_H_
#define _TOTAL_H_

// �}�N����`
#define NUM_TOTAL		(2)	// �|���S����

#define TEXTURE_GAME_TOTAL00	_T("data/TEXTURE/number.png")	// �T���v���p�摜
#define TEXTURE_TOTAL00_SIZE_X	(37 * SCREEN_SCALING)	// �e�N�X�`���T�C�Y
#define TEXTURE_TOTAL00_SIZE_Y	(74 * SCREEN_SCALING)	// ����
#define TOTAL_POS_X			(295 * SCREEN_SCALING)		// �|���S���̏����ʒuX
#define TOTAL_POS_Y			(-37 * SCREEN_SCALING)		// ����

#define TOTAL_MAX			(999999999)		// �X�R�A�̍ő�l
#define TOTAL_DIGIT			(9)				// ����
#define TOTAL_HP_BONUS		(5000000)		// �c��HP�{�[�i�X�l
#define TOTAL_TIME_BONUS	(5000000)		// �^�C���{�[�i�X�l
#define TOTAL_TIME_MAX		(200)			// �^�C���{�[�i�X�Ώۂ̍ő�l
#define TOTAL_COUNT_UP		(11111111)		// �J�E���g�A�b�v�l


/*******************************************************************************
* �\���̒�`
*******************************************************************************/


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTotal(int type);
void UninitTotal(void);
void UpdateTotal(void);
void DrawTotal(void);
void SetTotal(int nType, int nAdd);
int *GetTotal(void);

#endif
