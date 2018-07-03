//=============================================================================
//
// �v���C���[�\��Main�w�b�_�[ [main.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~

#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>
#include <stdio.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_SCALING	(1.5f)

#define SCREEN_MODE	(false)			// true:�E�C���h�E false:�t���X�N���[��

#define SCREEN_WIDTH	(1280 * SCREEN_SCALING)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720 * SCREEN_SCALING)				// �E�C���h�E�̍���
#define SCREEN_MARGIN	(200 * SCREEN_SCALING)				// �E�C���h�E�O�̗]��
#define SCREEN_MARGIN_BULLET	(600 * SCREEN_SCALING)		// �E�C���h�E�O�̗]���i�o���b�g�p�j


#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W

#define	NUM_VERTEX		(4)					// ���_��
#define VOLUME_CONTROL_UP	(100)			// ���ʏ㏸��
#define VOLUME_CONTROL_DOWN	(10)			// ���ʉ��~��
#define VOLUME_MAX	(0)						// �ő剹��
#define VOLUME_MIN	(-7000)					// �ŏ�����

#define VOLUME_SE		(-800)				// SE�{�����[��
#define VOLUME_VOICE	(-500)				// �{�C�X�{�����[��

#define SE_11_CONTINUITY	(5)				// �q�b�gSE�̍Đ��Ԋu
#define SE_11_VOLUME_SE		(-1200)				// SE11�̃{�����[���ݒ�

// ���_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// �������̊J���}�N��http://www.87ctriga.asm/
#define SAFE_RELEASE(ptr)	{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }

enum eStage
{
	STAGE_TITLE,
	STAGE_TUTORIAL,
	STAGE_CREDIT,
	STAGE_GAME,
	STAGE_RESULT
};


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W(*33)
} VERTEX_2D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);		// �f�o�C�X�擾�֐�
void SetStage(eStage stage);
void InitGame(int no);
void SetBgmVol(int no, bool type);
eStage CheckStage(void);
void SetEndFlag(void);
void SetSe(int nVoice, int nFlag, bool bContinuity);
int *GetCount(void);

#endif