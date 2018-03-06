//=============================================================================
//
// ���͏��� [sound.h]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#ifndef ___SOUND_H___
#define ___SOUND_H___

#include <windows.h>
#include <tchar.h>
#include <dsound.h>
#include <mmsystem.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
enum
{	// �T�E���h�ʂ��i���o�[(sound.cpp�̏��Ԃƍ��킹�鎖)
	BGM_00,
	BGM_01,
	BGM_02,
	BGM_03,
	BGM_04,
	SE_00,
	SE_01,
	SE_02,
	SE_03,
	SE_04,
	SE_05,
	SE_06,
	SE_07,
	SE_08,
	SE_09,
	SE_10,
	SE_11,
	SE_12,
	SE_13,
	VOICE_00,
	VOICE_01,
	VOICE_02,
	VOICE_03,
	VOICE_04,
	SOUND_MAX
};

enum
{	// �Đ��p�t���O
	E_DS8_FLAG_NONE,
	E_DS8_FLAG_LOOP,	// DSBPLAY_LOOPING=1
	E_DS8_FLAG_MAX
};

enum
{	// �A���Đ��t���O
	CONTINUITY_OFF,
	CONTINUITY_ON
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT					InitSound( HWND hWnd );	// ������
void					UninitSound();			// ��Еt��
LPDIRECTSOUNDBUFFER8	LoadSound( int no );	// �T�E���h�̃��[�h
void					PlaySound( LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0 );	// �����ƂɍĐ�
void					PlayContinuitySound(LPDIRECTSOUNDBUFFER8 pBuffer, int flag = 0 );
bool					IsPlaying( LPDIRECTSOUNDBUFFER8 pBuffer );					// �Đ������ǂ���
HRESULT					SetVol(LPDIRECTSOUNDBUFFER8 pBuffer, long nVol);

#endif