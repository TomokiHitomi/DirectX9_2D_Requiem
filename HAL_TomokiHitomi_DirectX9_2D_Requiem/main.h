//=============================================================================
//
// プレイヤー表示Mainヘッダー [main.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止

#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>
#include <stdio.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_SCALING	(1.5f)

#define SCREEN_MODE	(false)			// true:ウインドウ false:フルスクリーン

#define SCREEN_WIDTH	(1280 * SCREEN_SCALING)				// ウインドウの幅
#define SCREEN_HEIGHT	(720 * SCREEN_SCALING)				// ウインドウの高さ
#define SCREEN_MARGIN	(200 * SCREEN_SCALING)				// ウインドウ外の余白
#define SCREEN_MARGIN_BULLET	(600 * SCREEN_SCALING)		// ウインドウ外の余白（バレット用）


#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// ウインドウの中心Ｘ座標
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// ウインドウの中心Ｙ座標

#define	NUM_VERTEX		(4)					// 頂点数
#define VOLUME_CONTROL_UP	(100)			// 音量上昇幅
#define VOLUME_CONTROL_DOWN	(10)			// 音量下降幅
#define VOLUME_MAX	(0)						// 最大音量
#define VOLUME_MIN	(-7000)					// 最小音量

#define VOLUME_SE		(-800)				// SEボリューム
#define VOLUME_VOICE	(-500)				// ボイスボリューム

#define SE_11_CONTINUITY	(5)				// ヒットSEの再生間隔
#define SE_11_VOLUME_SE		(-1200)				// SE11のボリューム設定

// 頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// メモリの開放マクロhttp://www.87ctriga.asm/
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
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 vtx;		// 頂点座標
	float rhw;				// テクスチャのパースペクティブコレクト用
	D3DCOLOR diffuse;		// 反射光
	D3DXVECTOR2 tex;		// テクスチャ座標(*33)
} VERTEX_2D;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);		// デバイス取得関数
void SetStage(eStage stage);
void InitGame(int no);
void SetBgmVol(int no, bool type);
eStage CheckStage(void);
void SetEndFlag(void);
void SetSe(int nVoice, int nFlag, bool bContinuity);
int *GetCount(void);

#endif