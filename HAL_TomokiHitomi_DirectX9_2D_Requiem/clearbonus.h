//=============================================================================
//
// タイトル処理 [clearbonus.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _CLEARBONUS_H_
#define _CLEARBONUS_H_

#include "main.h"

// マクロ定義
#define NUM_CLEARBONUS		(2)	// ポリゴン数

#define TEXTURE_GAME_CLEARBONUS00	_T("data/TEXTURE/clearbonus.png")	// タイトル00用画像
#define TEXTURE_CLEARBONUS00_SIZE_X	(390 * SCREEN_SCALING/2)	// テクスチャサイズ
#define TEXTURE_CLEARBONUS00_SIZE_Y	(130 * SCREEN_SCALING/2)	// 同上

#define CLEARBONUS_POS_X			(500 * SCREEN_SCALING)	// 初期座標X
#define CLEARBONUS_POS_Y			(445 * SCREEN_SCALING)	// 初期座標Y

#define TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS	(1)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_CLEARBONUS	(2)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_CLEARBONUS			(TEXTURE_PATTERN_DIVIDE_X_CLEARBONUS*TEXTURE_PATTERN_DIVIDE_Y_CLEARBONUS)	// アニメーションパターン数
#define TIME_ANIMATION_CLEARBONUS				(4)	// アニメーションの切り替わるカウント

#define CLEARBONUS_MAX					(1)	// トータルスコアボードの最大数
#define CLEARBONUS_MAX					(1)	// トータルスコアボードの最大数


/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// タイトルの移動量
	D3DXVECTOR3				rot;					// タイトルの回転量
	D3DXVECTOR2				size;					// タイトルのテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// true:使用  false:未使用
}CLEARBONUS;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitClearbonus(int type);
void UninitClearbonus(void);
void UpdateClearbonus(void);
void DrawClearbonus(void);
CLEARBONUS *GetClearbonus(int no);


#endif
