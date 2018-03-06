//=============================================================================
//
// �^�C�g������ [scoreboard.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

#include "main.h"

// �}�N����`
#define NUM_SCOREBOARD		(2)	// �|���S����

#define TEXTURE_GAME_SCOREBOARD00	_T("data/TEXTURE/scoreboard.png")	// �^�C�g��00�p�摜
#define TEXTURE_SCOREBOARD00_SIZE_X	(612 * SCREEN_SCALING/2) // �e�N�X�`���T�C�Y
#define TEXTURE_SCOREBOARD00_SIZE_Y	(90 * SCREEN_SCALING/2) // ����
#define SCOREBOARD_POS_X			(865 * SCREEN_SCALING)	// �������WX
#define SCOREBOARD_POS_Y			(53 * SCREEN_SCALING)	// �������WY

#define TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y_SCOREBOARD	(1)	// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM_SCOREBOARD			(TEXTURE_PATTERN_DIVIDE_X_SCOREBOARD*TEXTURE_PATTERN_DIVIDE_Y_SCOREBOARD)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_SCOREBOARD				(4)	// �A�j���[�V�����̐؂�ւ��J�E���g

#define SCOREBOARD_MAX					(1)	// �X�R�A�{�[�h�̍ő吔


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
}SCOREBOARD;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitScoreboard(int type);
void UninitScoreboard(void);
void UpdateScoreboard(void);
void DrawScoreboard(void);
SCOREBOARD *GetScoreboard(int no);


#endif
