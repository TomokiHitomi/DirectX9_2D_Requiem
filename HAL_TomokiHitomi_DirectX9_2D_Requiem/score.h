//=============================================================================
//
// SCORE処理 [score.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

// マクロ定義
#define NUM_SCORE		(2)	// ポリゴン数

#define TEXTURE_GAME_SCORE00	_T("data/TEXTURE/number.png")	// サンプル用画像
#define TEXTURE_SCORE00_SIZE_X	(37 * SCREEN_SCALING)	// テクスチャサイズ
#define TEXTURE_SCORE00_SIZE_Y	(74 * SCREEN_SCALING)	// 同上
#define SCORE_POS_X			(220 * SCREEN_SCALING)		// ポリゴンの初期位置X
#define SCORE_POS_Y			(-37 * SCREEN_SCALING)		// 同上
#define SCORE_MAX			(999999999)		// スコアの最大値
#define SCORE_DIGIT			(9)			// 桁数

#define ADD_SCORE_BULLETHIT			(11111)
#define ADD_SCORE_ENEMYKNOCKDOWN	(5000000)

/*******************************************************************************
* 構造体定義
*******************************************************************************/


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitScore(int type);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void AddScore(int add);

#endif
