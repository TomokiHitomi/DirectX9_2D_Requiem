//=============================================================================
//
// TIME処理 [time.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

// マクロ定義
#define NUM_TIME		(2)	// ポリゴン数

#define TEXTURE_GAME_TIME00	_T("data/TEXTURE/number.png")	// サンプル用画像
#define TEXTURE_TIME00_SIZE_X	(37 * SCREEN_SCALING)	// テクスチャサイズ
#define TEXTURE_TIME00_SIZE_Y	(74 * SCREEN_SCALING)	// 同上

#define TIME_POS_X			(110 * SCREEN_SCALING)		// ポリゴンの初期位置X
#define TIME_POS_Y			(-37 * SCREEN_SCALING)		// 同上

#define TIME_MAX			(999)		// スコアの最大値
#define TIME_SECOND			(60)		// 60秒
#define TIME_DIGIT			(3)			// 桁数


/*******************************************************************************
* 構造体定義
*******************************************************************************/


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTime(int type);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
void SetTime(int add);

#endif
