//=============================================================================
//
// TOTAL処理 [total.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _TOTAL_H_
#define _TOTAL_H_

// マクロ定義
#define NUM_TOTAL		(2)	// ポリゴン数

#define TEXTURE_GAME_TOTAL00	_T("data/TEXTURE/number.png")	// サンプル用画像
#define TEXTURE_TOTAL00_SIZE_X	(37 * SCREEN_SCALING)	// テクスチャサイズ
#define TEXTURE_TOTAL00_SIZE_Y	(74 * SCREEN_SCALING)	// 同上
#define TOTAL_POS_X			(295 * SCREEN_SCALING)		// ポリゴンの初期位置X
#define TOTAL_POS_Y			(-37 * SCREEN_SCALING)		// 同上

#define TOTAL_MAX			(999999999)		// スコアの最大値
#define TOTAL_DIGIT			(9)				// 桁数
#define TOTAL_HP_BONUS		(5000000)		// 残りHPボーナス値
#define TOTAL_TIME_BONUS	(5000000)		// タイムボーナス値
#define TOTAL_TIME_MAX		(200)			// タイムボーナス対象の最大値
#define TOTAL_COUNT_UP		(11111111)		// カウントアップ値


/*******************************************************************************
* 構造体定義
*******************************************************************************/


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTotal(int type);
void UninitTotal(void);
void UpdateTotal(void);
void DrawTotal(void);
void SetTotal(int nType, int nAdd);
int *GetTotal(void);

#endif
