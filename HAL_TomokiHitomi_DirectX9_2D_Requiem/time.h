//=============================================================================
//
// TIME���� [time.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

// �}�N����`
#define NUM_TIME		(2)	// �|���S����

#define TEXTURE_GAME_TIME00	_T("data/TEXTURE/number.png")	// �T���v���p�摜
#define TEXTURE_TIME00_SIZE_X	(37 * SCREEN_SCALING)	// �e�N�X�`���T�C�Y
#define TEXTURE_TIME00_SIZE_Y	(74 * SCREEN_SCALING)	// ����

#define TIME_POS_X			(110 * SCREEN_SCALING)		// �|���S���̏����ʒuX
#define TIME_POS_Y			(-37 * SCREEN_SCALING)		// ����

#define TIME_MAX			(999)		// �X�R�A�̍ő�l
#define TIME_SECOND			(60)		// 60�b
#define TIME_DIGIT			(3)			// ����


/*******************************************************************************
* �\���̒�`
*******************************************************************************/


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTime(int type);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void SetTime(int add);

#endif
