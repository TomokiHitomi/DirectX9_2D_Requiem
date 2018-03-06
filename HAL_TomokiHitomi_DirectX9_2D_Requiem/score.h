//=============================================================================
//
// SCORE���� [score.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

// �}�N����`
#define NUM_SCORE		(2)	// �|���S����

#define TEXTURE_GAME_SCORE00	_T("data/TEXTURE/number.png")	// �T���v���p�摜
#define TEXTURE_SCORE00_SIZE_X	(37 * SCREEN_SCALING)	// �e�N�X�`���T�C�Y
#define TEXTURE_SCORE00_SIZE_Y	(74 * SCREEN_SCALING)	// ����
#define SCORE_POS_X			(220 * SCREEN_SCALING)		// �|���S���̏����ʒuX
#define SCORE_POS_Y			(-37 * SCREEN_SCALING)		// ����
#define SCORE_MAX			(999999999)		// �X�R�A�̍ő�l
#define SCORE_DIGIT			(9)			// ����

#define ADD_SCORE_BULLETHIT			(11111)
#define ADD_SCORE_ENEMYKNOCKDOWN	(5000000)

/*******************************************************************************
* �\���̒�`
*******************************************************************************/


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int add);

#endif
